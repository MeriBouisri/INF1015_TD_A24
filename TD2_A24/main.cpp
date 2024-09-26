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
size_t lireUintTailleVariable(istream& fichier) {
	uint8_t entete = lireType<uint8_t>(fichier);
	switch (entete) {
	case enteteTailleVariableDeBase + 0: return lireType<uint8_t>(fichier);
	case enteteTailleVariableDeBase + 1: return lireType<uint16_t>(fichier);
	case enteteTailleVariableDeBase + 2: return lireType<uint32_t>(fichier);
	default:
		erreurFataleAssert("Tentative de lire un entier de taille variable alors que le fichier contient autre chose à cet emplacement.");
	}
}


string lireString(istream& fichier) {
	string texte;
	texte.resize(lireUintTailleVariable(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}


gsl::span<Jeu*> spanListeJeux(const ListeJeux& liste) {
	return gsl::span(liste.elements, liste.nElements);
}


gsl::span<Concepteur*> spanListeConcepteurs(const ListeConcepteurs& liste) {
	return gsl::span(liste.elements, liste.nElements);
}
#pragma endregion


Concepteur* trouverConcepteur(string nom, const ListeJeux& jeux) {
	gsl::span<Jeu*> spanJeux = spanListeJeux(jeux);
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


Concepteur* lireConcepteur(istream& fichier, const ListeJeux& jeux) {
	Concepteur concepteur = {}; // On initialise une structure vide de type Concepteur.
	concepteur.nom = lireString(fichier);
	concepteur.anneeNaissance = int(lireUintTailleVariable(fichier));
	concepteur.pays = lireString(fichier);
	// Rendu ici, les champs précédents de la structure concepteur sont remplis
	// avec la bonne information.

	//TODO (done): Ajouter en mémoire le concepteur lu. Il faut revoyer le pointeur créé.
	// Attention, valider si le concepteur existe déjà avant de le créer, sinon
	// on va avoir des doublons car plusieurs jeux ont des concepteurs en commun
	// dans le fichier binaire. Pour ce faire, cette fonction aura besoin de
	// la liste de jeux principale en paramètre.
	// Afficher un message lorsque l'allocation du concepteur est réussie.

	Concepteur* concepteurTrouve = trouverConcepteur(concepteur.nom, jeux);

	if (concepteurTrouve != nullptr) {
		cout << "Concepteur trouve : [Concepteur, " << concepteurTrouve->nom << ", " << concepteurTrouve << "]" << endl;
		return concepteurTrouve;
	}

	concepteurTrouve = new Concepteur(concepteur);

	// TODO (personnel) : Ajout methodes struct Concepteur
	concepteurTrouve->jeuxConcus = {};
	concepteurTrouve->jeuxConcus.capacite = 0;
	concepteurTrouve->jeuxConcus.nElements = 0;

	// TODO (personnel) : Memory leak here ?
	concepteurTrouve->jeuxConcus.elements = new Jeu * [concepteurTrouve->jeuxConcus.capacite];

	cout << "Memoire allouee : [Concepteur, " << concepteurTrouve->nom << ", " << concepteurTrouve << "]" << endl;

	return concepteurTrouve; //TODO (done): Retourner le pointeur vers le concepteur crée.
}


Jeu* lireJeu(istream& fichier, ListeJeux& jeux) {
	Jeu jeu = {}; // On initialise une structure vide de type Jeu
	jeu.titre = lireString(fichier);
	jeu.anneeSortie = int(lireUintTailleVariable(fichier));
	jeu.developpeur = lireString(fichier);
	jeu.concepteurs.nElements = lireUintTailleVariable(fichier);
	// Rendu ici, les champs précédents de la structure jeu sont remplis avec la
	// bonne information.

	//TODO (done): Ajouter en mémoire le jeu lu. Il faut revoyer le pointeur créé.
	// Attention, il faut aussi créer un tableau dynamique pour les concepteurs
	// que contient un jeu. Servez-vous de votre fonction d'ajout de jeu car la
	// liste de jeux participé est une ListeJeu. Afficher un message lorsque
	// l'allocation du jeu est réussie.

	Jeu* jeuLu = new Jeu(jeu);
	jeuLu->concepteurs.elements = new Concepteur * [jeu.concepteurs.nElements];

	for ([[maybe_unused]] size_t i : iter::range(jeu.concepteurs.nElements)) {
		//TODO (done): Mettre le concepteur dans la liste des concepteur du jeu.
		Concepteur* concepteur = lireConcepteur(fichier, jeux);
		jeuLu->concepteurs.elements[i] = concepteur;

		//TODO (done): Ajouter le jeu à la liste des jeux auquel a participé le concepteur.
		ListeJeux::ajouterJeu(*jeuLu, concepteur->jeuxConcus);
	}

	cout << "Memoire allouee : [Jeu, " << jeuLu->titre << ", " << jeuLu << "]" << endl;

	return jeuLu; // TODO (done): Retourner le pointeur vers le nouveau jeu.
}


ListeJeux creerListeJeux(const string& nomFichier) {
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);

	ListeJeux listeJeux = {};

	listeJeux.nElements = 0;
	listeJeux.capacite = lireUintTailleVariable(fichier);
	listeJeux.elements = new Jeu * [listeJeux.capacite];

	for ([[maybe_unused]] size_t n : iter::range(listeJeux.capacite))
	{
		Jeu* jeu = lireJeu(fichier, listeJeux); // (done) TODO: Ajouter le jeu à la ListeJeux.
		ListeJeux::ajouterJeu(*jeu, listeJeux);
	}

	return listeJeux; // (done) TODO: Renvoyer la ListeJeux.
}


//TODO: Fonction pour détruire un concepteur (libération de mémoire allouée).
// Lorsqu'on détruit un concepteur, on affiche son nom pour fins de débogage.
void detruireConcepteur(Concepteur* concepteur) {
	ListeJeux jeuxConcus = concepteur->jeuxConcus;
	cout << "Concepteur en cours de destruction : [Concepteur, " << concepteur->nom << ", " << concepteur << ", " << *concepteur->jeuxConcus.elements << "]" << endl;

	for (Jeu* jeu : spanListeJeux(concepteur->jeuxConcus))
		ListeJeux::enleverJeu(jeu, concepteur->jeuxConcus);

	delete[] concepteur->jeuxConcus.elements;
	concepteur->jeuxConcus.elements = nullptr;

	delete concepteur;
	concepteur = nullptr;

	cout << "Concepteur detruit : [concepteurTrouve=" << concepteur << "]" << endl; //", " << *concepteur->jeuxConcus.elements << "]" << endl;
}


//TODO: Fonction qui détermine si un concepteur participe encore à un jeu.
bool concepteurParticipeJeu(const Concepteur& concepteur) {
	return concepteur.jeuxConcus.nElements > 0;
}


//TODO: Fonction pour détruire un jeu (libération de mémoire allouée).
// Attention, ici il faut relâcher toute les cases mémoires occupées par un jeu.
// Par conséquent, il va falloir gérer le cas des concepteurs (un jeu contenant
// une ListeConcepteurs). On doit commencer par enlever le jeu à détruire des jeux
// qu'un concepteur a participé (jeuxConcus). Si le concepteur n'a plus de
// jeux présents dans sa liste de jeux participés, il faut le supprimer.  Pour
// fins de débogage, affichez le nom du jeu lors de sa destruction.
void detruireJeu(Jeu* jeu) {
	cout << "Jeu en cours de destruction : [Jeu, " << jeu->titre << ", " << jeu << "]" << endl;

	for (Concepteur* concepteur : spanListeConcepteurs(jeu->concepteurs)) {
		ListeJeux::enleverJeu(jeu, concepteur->jeuxConcus);

		if (!concepteurParticipeJeu(*concepteur))
			detruireConcepteur(concepteur);
	}

	delete[] jeu->concepteurs.elements;
	jeu->concepteurs.elements = nullptr;

	delete jeu;
	jeu = nullptr;

	cout << "Jeu detruit : [jeuLu=" << jeu << "]" << endl;
}


//TODO: Fonction pour détruire une ListeJeux et tous ses jeux.
void detruireListeJeux(ListeJeux listeJeux) {
	for (Jeu* jeu : spanListeJeux(listeJeux))
		detruireJeu(jeu);

	delete[] listeJeux.elements;
	listeJeux.elements = nullptr;

	cout << "Liste de jeux détruite" << endl;
}


void afficherConcepteur(const Concepteur& concepteurAAfficher) {
	cout << "\t" << concepteurAAfficher.nom << ", " << concepteurAAfficher.anneeNaissance << ", " << concepteurAAfficher.pays << endl;
}


//TODO: Fonction pour afficher les infos d'un jeu ainsi que ses concepteurs.
// Servez-vous de la fonction afficherConcepteur ci-dessus.
void afficherJeu(const Jeu& jeu) {
	cout << jeu.titre << ", " << jeu.anneeSortie << ", " << jeu.developpeur << endl;
	cout << "Concepteurs:" << endl;

	for (Concepteur* concepteur : spanListeConcepteurs(jeu.concepteurs))
		afficherConcepteur(*concepteur);
}


//TODO: Fonction pour afficher tous les jeux de ListeJeux, séparés par un ligne.
// Servez-vous de la fonction d'affichage d'un jeu crée ci-dessus. Votre ligne
// de séparation doit être différent de celle utilisée dans le main.
void afficherListeJeux(const ListeJeux& listeJeux) {
	for (Jeu* jeu : spanListeJeux(listeJeux)) {
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

	ListeJeux jeux = creerListeJeux("jeux.bin"); //TODO (done): Appeler correctement votre fonction de création de la liste de jeux.

	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	cout << ligneSeparation << endl;
	cout << "Premier jeu de la liste :" << endl;

	//TODO (done): Afficher le premier jeu de la liste (en utilisant la fonction).  Devrait être Chrono Trigger.

	cout << jeux.elements[0]->titre << endl;

	cout << ligneSeparation << endl;

	//TODO (done): Appel à votre fonction d'affichage de votre liste de jeux.

	afficherListeJeux(jeux);
	cout << ligneSeparation << endl;



	cout << ligneSeparation << endl;

	//TODO: Faire les appels à toutes vos fonctions/méthodes pour voir qu'elles fonctionnent et avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.

	ListeJeux::test();
	Developpeur::test();


	//TODO: Détruire tout avant de terminer le programme.  Devrait afficher "Aucune fuite detectee." a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.

	detruireListeJeux(jeux);
}
