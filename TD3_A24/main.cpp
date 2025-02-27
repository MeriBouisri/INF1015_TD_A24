﻿/**
* TD3 - Automne 2024
* Implementation du TD precedent avec pointeurs intelligents.
* \file   main.cpp
* \author Bouisri et Xa
* \date   21 octobre 2024
* Cree le 8 octobre 2024
*/


#include "bibliotheque_cours.hpp"
#include "cppitertools/range.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
#include "gsl/span"
#include "Jeu.hpp"
#include "Liste.hpp"
#include "verification_allocation.hpp"
#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <typeinfo>


using namespace std;
using namespace iter;
using namespace gsl;
using std::function;

#pragma region "Fonctions de base pour vous aider"
template <typename T>
T lireType(istream& fichier)
{
	T valeur{};
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}
#define erreurFataleAssert(message) assert(false&&(message)),terminate()
static const uint8_t enteteTailleVariableDeBase = 0xA0;
size_t lireUintTailleVariable(istream& fichier)
{
	uint8_t entete = lireType<uint8_t>(fichier);
	switch (entete) {
	case enteteTailleVariableDeBase + 0: return lireType<uint8_t>(fichier);
	case enteteTailleVariableDeBase + 1: return lireType<uint16_t>(fichier);
	case enteteTailleVariableDeBase + 2: return lireType<uint32_t>(fichier);
	default:
		erreurFataleAssert("Tentative de lire un entier de taille variable alors que le fichier contient autre chose à cet emplacement.");
	}
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUintTailleVariable(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}


#pragma endregion


// Fonction qui cherche un concepteur par son nom dans une ListeJeux.
// Cette fonction renvoie le pointeur vers le concepteur si elle le trouve dans
// un des jeux de la ListeJeux. En cas contraire, elle renvoie un pointeur nul.
shared_ptr<Concepteur> trouverConcepteur(const Liste<Jeu>& listeJeux, const string& nomConcepteurCherche) {
	for (const auto& jeu : listeJeux.enSpan()) {
		// Normalement on voudrait retourner un pointeur const, mais cela nous
		// empêcherait d'affecter le pointeur retourné lors de l'appel de cette
		// fonction.
		auto concepteur = jeu->concepteurs.trouver([&nomConcepteurCherche](auto concepteur) {return concepteur->nom == nomConcepteurCherche; });
		if (concepteur)
			return concepteur;
	}
	return nullptr;
}


shared_ptr<Concepteur> lireConcepteur(istream& fichier, const Liste<Jeu>& listeJeux)
{
	Concepteur concepteur = {}; // On initialise une structure vide de type Concepteur.
	concepteur.nom = lireString(fichier);
	concepteur.anneeNaissance = int(lireUintTailleVariable(fichier));
	concepteur.pays = lireString(fichier);
	// Rendu ici, les champs précédents de la structure concepteur sont remplis
	// avec la bonne information.

	// Ajouter en mémoire le concepteur lu. Il faut revoyer le pointeur créé.
	// Attention, valider si le concepteur existe déjà avant de le créer, sinon
	// on va avoir des doublons car plusieurs jeux ont des concepteurs en commun
	// dans le fichier binaire. Pour ce faire, cette fonction aura besoin de
	// la liste de jeux principale en paramètre.
	// Afficher un message lorsque l'allocation du concepteur est réussie.
	shared_ptr<Concepteur> concepteurExistant = trouverConcepteur(listeJeux, concepteur.nom);
	if (concepteurExistant != nullptr)
		return concepteurExistant;

	//cout << concepteur.nom << endl;  // Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	std::cout << "\033[92m" << "Allocation en mémoire du concepteur " << concepteur.nom
		<< "\033[0m" << endl;
	return make_shared<Concepteur>(concepteur); // Retourner le pointeur vers le concepteur crée.
}


shared_ptr<Jeu> lireJeu(istream& fichier, Liste<Jeu>& listeJeux)
{
	// Rendu ici, les champs précédents de la structure jeu sont remplis avec la
	// bonne information.

	//Ajouter en mémoire le jeu lu. Il faut revoyer le pointeur créé.
	// Attention, il faut aussi créer un tableau dynamique pour les concepteurs
	// que contient un jeu. Servez-vous de votre fonction d'ajout de jeu car la
	// liste de jeux participé est une ListeJeu. Afficher un message lorsque
	// l'allocation du jeu est réussie.
	shared_ptr<Jeu> jeuLu = make_shared<Jeu>();  // Ou allouer directement au début plutôt qu'en faire une copie ici.
	//Jeu jeu = {}; // On initialise une structure vide de type Jeu
	jeuLu->titre = lireString(fichier);
	jeuLu->anneeSortie = int(lireUintTailleVariable(fichier));
	jeuLu->developpeur = lireString(fichier);
	std::cout << "\033[96m" << "Allocation en mémoire du jeu " << jeuLu->titre
		<< "\033[0m" << endl;
	// cout << jeu.titre << endl;  // Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.


	for ([[maybe_unused]] size_t i : iter::range(lireUintTailleVariable(fichier))) {
		jeuLu->concepteurs.ajouter(lireConcepteur(fichier, listeJeux));  //: Mettre le concepteur dans la liste des concepteur du jeu.
	}

	return jeuLu; //Retourner le pointeur vers le nouveau jeu.
}

Liste<Jeu> creerListeJeux(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	size_t nElements = lireUintTailleVariable(fichier);
	Liste<Jeu> listeJeux = {};
	for ([[maybe_unused]] size_t n : iter::range(nElements))
	{
		listeJeux.ajouter(lireJeu(fichier, listeJeux)); //Ajouter le jeu à la ListeJeux.
	}

	return listeJeux; //Renvoyer la ListeJeux.
}


// void afficherConcepteur(const Concepteur& d)
// {
// 	cout << "\t" << d.nom << ", " << d.anneeNaissance << ", " << d.pays
// 		<< endl;
// }

// //Fonction pour afficher les infos d'un jeu ainsi que ses concepteurs.
// // Servez-vous de la fonction afficherConcepteur ci-dessus.
// void afficherJeu(const Jeu& j)
// {
// 	cout << "Titre : " << "\033[94m" << j.titre << "\033[0m" << endl;
// 	cout << "Parution : " << "\033[94m" << j.anneeSortie << "\033[0m"
// 		<< endl;
// 	cout << "Développeur :  " << "\033[94m" << j.developpeur << "\033[0m"
// 		<< endl;
// 	cout << "Concepteurs du jeu :" << "\033[94m" << endl;
// 	for (const shared_ptr<Concepteur> concepteur : j.concepteurs.enSpan())
// 		afficherConcepteur(*concepteur);
// 	cout << "\033[0m";
// }


ostream& operator<<(ostream& os, const Concepteur& c) {
	return os << "[c.nom=" << c.nom 
		<< ", c.anneeNaissance=" << c.anneeNaissance 
		<< ", c.pays=" << c.pays << "]";
}

ostream& operator<<(ostream& os, const Jeu& j) {

	os << "[j.titre=" << j.titre 
		<< ", j.anneeSortie=" << j.anneeSortie 
		<< ", j.developpeur=" << j.developpeur 
		<< ", j.concepteurs=[" << endl;

	for (const auto& c : j.concepteurs.enSpan())
		os << "\t" << *c << endl;

	os << "]" << endl;

	return os;
}

ostream& operator<<(ostream& os, const Liste<Jeu>& l) {
	os << "[listeJeux.elements=[";
	for (const auto& j : l.enSpan())
		os << *j;

	os << "]" << endl;

	return os;
}

//Fonction pour afficher tous les jeux de ListeJeux, séparés par un ligne.
// Servez-vous de la fonction d'affichage d'un jeu crée ci-dessus. Votre ligne
// de séparation doit être différent de celle utilisée dans le main.
void afficherListeJeux(const Liste<Jeu>& listeJeux)
{
	static const string ligneSeparation = "\n\033[95m"
		"══════════════════════════════════════════════════════════════════════════"
		"\033[0m\n";
	cout << ligneSeparation << listeJeux << ligneSeparation << endl;
	
}



/**
 * @brief Teste la surcharge de l'operateur []
 */
void test04(const Liste<Jeu>& lj) {
	assert(lj[2]->titre == "Secret of Mana");
	assert(lj[2]->concepteurs[1]->nom == "Hiromichi Tanaka");	
	cout << "[SUCCES] Test #4" << endl;
}

void test05(const Liste<Jeu>& lj) {
	auto test1 = lj[0]->trouverConcepteur([](const shared_ptr<Concepteur>& c) {return c->nom == "Yoshinori Kitase"; });
	auto test2 = lj[1]->trouverConcepteur([](const shared_ptr<Concepteur>& c) {return c->nom == "Yoshinori Kitase"; });

	cout << "Test 1 : " << (test1 ? "trouvé" : "non trouvé") << test1 << test1->anneeNaissance << endl;
	cout << "Test 2 : " << (test2 ? "trouvé" : "non trouvé") << test2 << test2->anneeNaissance << endl;

	cout << (test1 && test2 ? "[SUCCES] " : "[ECHEC] ") << "Test #5" << endl;
}

/**
 * @brief Teste les fonction de surcharge de l'opérateur <<
 */
void test06(const Liste<Jeu>& lj) {

	ofstream("sortie.txt") << lj;
	assert(ifstream("sortie.txt").good());

	cout << "[SUCCES] Test #6" << endl;
}

void test07(const Liste<Jeu>& lj) {
	
	Jeu copieJeu = *lj[2];

	// Verifier la copie
	assert(&copieJeu != &*lj[2]); 
	assert(&copieJeu.concepteurs != &lj[2]->concepteurs);
	assert(copieJeu.concepteurs[0] == lj[2]->concepteurs[0]); // comparer premier concepteur

	// Remplacer 2e concepteur
	copieJeu.concepteurs[1] = lj[0]->concepteurs[1]; 

	assert(copieJeu.concepteurs[1] != lj[2]->concepteurs[1]); 
	assert(copieJeu.concepteurs[1] == lj[0]->concepteurs[1]); 
	
	cout << "[INFO] Modification de la copie" << endl;
	cout << "[INFO] Original : " << *lj[2] << endl;
	cout << "[INFO] Copie : " << copieJeu << endl;

	cout << "[SUCCES] Test #7" << endl;
}



int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

	//int* fuite = new int;  // Pour vérifier que la détection de fuites fonctionne; un message devrait dire qu'il y a une fuite à cette ligne.

	Liste<Jeu> lj = creerListeJeux("jeux.bin"); 

	// Avec surcharge operateur <<
	afficherListeJeux(lj); 

	// TEST #5

	test04(lj);
    test05(lj);
	test06(lj);
	test07(lj);

}
