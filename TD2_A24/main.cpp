/**
* Implémentation de l'allocation dynamique et des classes pour la gestion des listes de jeux vidéo et de développeurs à partir du fichier jeux.bin
* \file   main.cpp
* \author Bouisri et Xa
* \date   29 septembre 2024
* Créé le 17 septembre 2024
*/

#include "Jeu.hpp"
#include <iostream>
#include <fstream>
#include <cstdint>
#include "cppitertools/range.hpp"
#include "gsl/span"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#include "Developpeur.hpp"
#include "ListeDeveloppeurs.hpp"

using namespace std;
using namespace iter;
using namespace gsl;

#pragma region "Fonctions de base pour vous aider"
template <typename T>
T lireType(istream& fichier) {
	T valeur{};
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}


#define erreurFataleAssert(message) assert(false&&(message)),terminate()
static const uint8_t enteteTailleVariableDeBase = 0xA0;
static size_t lireUintTailleVariable(istream& fichier) {
	uint8_t entete = lireType<uint8_t>(fichier);
	switch (entete) {
	case enteteTailleVariableDeBase + 0: return lireType<uint8_t>(fichier);
	case enteteTailleVariableDeBase + 1: return lireType<uint16_t>(fichier);
	case enteteTailleVariableDeBase + 2: return lireType<uint32_t>(fichier);
	default:
		erreurFataleAssert("Tentative de lire un entier de taille variable alors que le fichier contient autre chose à cet emplacement."); // NOTE : Non couvert par la couverture de code
	}
}


static string lireString(istream& fichier) {
	string texte;
	texte.resize(lireUintTailleVariable(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}


static gsl::span<Concepteur*> spanListeConcepteurs(const ListeConcepteurs& liste) {
	return gsl::span(liste.elements, liste.nElements);
}
#pragma endregion


static Concepteur* trouverConcepteur(const string& nom, const ListeJeux& jeux) {
	gsl::span<Jeu*> spanJeux = ListeJeux::span(jeux);
	for (Jeu* jeu : spanJeux) {
		gsl::span<Concepteur*> spanConcepteurs = spanListeConcepteurs(jeu->concepteurs);
		for (Concepteur* concepteur : spanConcepteurs) {
			if (concepteur->nom == nom) {
				return concepteur;
			}
		}
	}
	return nullptr;
}


static Concepteur* lireConcepteur(istream& fichier, const ListeJeux& jeux) {
	Concepteur concepteur = {}; // On initialise une structure vide de type Concepteur.
	concepteur.nom = lireString(fichier);
	concepteur.anneeNaissance = int(lireUintTailleVariable(fichier));
	concepteur.pays = lireString(fichier);
	// Rendu ici, les champs précédents de la structure concepteur sont remplis
	// avec la bonne information.

	Concepteur* concepteurOptionnel = trouverConcepteur(concepteur.nom, jeux);

	if (concepteurOptionnel != nullptr) {
		cout << "[ABORT][lireConcepteur] Deja en memoire : [concepteurOptionnel->nom=" << concepteurOptionnel->nom << "]" << endl;
		return concepteurOptionnel;
	}

	concepteurOptionnel = new Concepteur(concepteur);

	concepteurOptionnel->jeuxConcus = {};
	concepteurOptionnel->jeuxConcus.capacite = 0;
	concepteurOptionnel->jeuxConcus.nElements = 0;

	concepteurOptionnel->jeuxConcus.elements = new Jeu * [concepteurOptionnel->jeuxConcus.capacite];

	cout << "[SUCCES][lireConcepteur] Allocation de memoire : [concepteurOptionnel->nom=" << concepteurOptionnel->nom << "]" << endl;

	return concepteurOptionnel;
}


static Jeu* lireJeu(istream& fichier, ListeJeux& jeux) {
	Jeu jeu = {}; // On initialise une structure vide de type Jeu
	jeu.titre = lireString(fichier);
	jeu.anneeSortie = int(lireUintTailleVariable(fichier));
	jeu.developpeur = lireString(fichier);
	jeu.concepteurs.nElements = lireUintTailleVariable(fichier);
	// Rendu ici, les champs précédents de la structure jeu sont remplis avec la
	// bonne information.


	Jeu* jeuLu = new Jeu(jeu);
	jeuLu->concepteurs.elements = new Concepteur * [jeu.concepteurs.nElements];

	for ([[maybe_unused]] size_t i : iter::range(jeu.concepteurs.nElements)) {
		Concepteur* concepteur = lireConcepteur(fichier, jeux);
		jeuLu->concepteurs.elements[i] = concepteur;

		ListeJeux::ajouterJeu(*jeuLu, concepteur->jeuxConcus);
	}

	cout << "[SUCCES][lireJeu] Allocation de memoire : [jeuLu->titre=" << jeuLu->titre << "]" << endl;

	return jeuLu;
}


static ListeJeux creerListeJeux(const string& nomFichier) {
	cout << "[INFO][creerListeJeux] Lecture du fichier : [nomFichier=" << nomFichier << "]" << endl;

	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);

	ListeJeux listeJeux = {};

	listeJeux.nElements = 0;
	listeJeux.capacite = lireUintTailleVariable(fichier);
	listeJeux.elements = new Jeu * [listeJeux.capacite];

	for ([[maybe_unused]] size_t i : iter::range(listeJeux.capacite))
	{
		Jeu* jeu = lireJeu(fichier, listeJeux);
		ListeJeux::ajouterJeu(*jeu, listeJeux);
	}

	cout << "[SUCCES][creerListeJeux] Allocation de memoire : [listeJeu.nElements=" << listeJeux.nElements
		<< ", listeJeux.capacite=" << listeJeux.capacite << "]" << endl;

	return listeJeux;
}


static void detruireConcepteur(Concepteur* concepteur) {

	for (Jeu* jeu : concepteur->jeuxConcus.span())
		ListeJeux::enleverJeu(jeu, concepteur->jeuxConcus);

	delete[] concepteur->jeuxConcus.elements;
	concepteur->jeuxConcus.elements = nullptr;

	delete concepteur;
	concepteur = nullptr;

	cout << "[SUCCES][detruireConcepteur] Liberation de memoire : [concepteur=" << concepteur << "]" << endl;
	cout << endl;
}


static bool concepteurParticipeJeu(const Concepteur& concepteur) {
	return concepteur.jeuxConcus.nElements > 0;
}


static void detruireJeu(Jeu* jeu) {

	for (Concepteur* concepteur : spanListeConcepteurs(jeu->concepteurs)) {
		ListeJeux::enleverJeu(jeu, concepteur->jeuxConcus);

		if (!concepteurParticipeJeu(*concepteur)) {
			cout << "[DEBUG][detruireJeu] Concepteur non-participant : [concepteur->nom=" << concepteur->nom << "]" << endl;
			detruireConcepteur(concepteur);
		}
	}

	delete[] jeu->concepteurs.elements;
	jeu->concepteurs.elements = nullptr;

	delete jeu;
	jeu = nullptr;

	cout << "[SUCCES][detruireJeu] Liberation de memoire : [jeu=" << jeu << "]" << endl;
	cout << endl;
}


static void detruireListeJeux(ListeJeux listeJeux) {

	for (Jeu* jeu : listeJeux.span())
		detruireJeu(jeu);

	delete[] listeJeux.elements;
	listeJeux.elements = nullptr;

	cout << "[SUCCES][detruireListeJeux] Liberation de memoire : [listeJeux=" << listeJeux.elements << "]" << endl;
	cout << endl;

}


static void afficherConcepteur(const Concepteur& concepteur) {
	cout << "\t[concepteur.nom=" << concepteur.nom << ", concepteur.anneeNaissance=" << concepteur.anneeNaissance << ", conceptreur.pays=" << concepteur.pays << "]" << endl;
}


static void afficherJeu(const Jeu& jeu) {
	cout << "[jeu.titre=" << jeu.titre << ", jeu.anneeSortie=" << jeu.anneeSortie << ", jeu.developpeur=" << jeu.developpeur << endl;
	cout << "[jeu.concepteurs= ...]`" << endl;


	for (Concepteur* concepteur : spanListeConcepteurs(jeu.concepteurs))
		afficherConcepteur(*concepteur);
}


static void afficherListeJeux(const ListeJeux& listeJeux) {
	for (Jeu* jeu : ListeJeux::span(listeJeux)) {
		afficherJeu(*jeu);
		cout << "\n";
	}
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion


	//int* fuite = new int;  // Pour vérifier que la détection de fuites fonctionne; un message devrait dire qu'il y a une fuite à cette ligne.

	ListeJeux jeux = creerListeJeux("jeux.bin");

	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	cout << ligneSeparation << endl;

	cout << "Premier jeu de la liste :" << endl;
	cout << jeux.elements[0]->titre << endl;

	cout << ligneSeparation << endl;
	afficherListeJeux(jeux);
	cout << ligneSeparation << endl;


	cout << ligneSeparation << endl;

	cout << "TESTS" << endl;

	cout << ligneSeparation << endl;

	Developpeur::testDeveloppeur();
	ListeDeveloppeurs::testListeDeveloppeurs();


	cout << ligneSeparation << endl;
	detruireListeJeux(jeux);
}