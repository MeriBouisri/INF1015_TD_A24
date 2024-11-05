﻿#include "bibliotheque_cours.hpp"
#include "lectureBinaire.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>


#include "Heros.hpp"
#include "Personnage.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"
#include <vector>

using namespace std;

ifstream ouvrirFichierBinaire(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	return fichier;
}

void testsPourCouvertureLectureBinaire()
{
	istringstream iss("\xA0\x12\xA1\x21\x43\xA2\x98\xBA\xDC\xFE");
	assert(lireUintTailleVariable(iss) == 0x12);
	assert(lireUintTailleVariable(iss) == 0x4321);
	assert(lireUintTailleVariable(iss) == 0xFEDCBA98);
}


int main()
{
#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

	testsPourCouvertureLectureBinaire();

	// Trait de separation
	static const string trait =
		"═════════════════════════════════════════════════════════════════════════";

	// Ouverture des fichiers binaires
	ifstream fichierHeros = ouvrirFichierBinaire("heros.bin");
	ifstream fichierVilains = ouvrirFichierBinaire("vilains.bin");



	//TODO: Votre code pour le main commence ici (mais vous pouvez aussi ajouter/modifier du code avant si nécessaire)
	vector<Heros> listeHeros;
	vector<Vilain> vilains;
	vector<unique_ptr<Personnage>> personnages;

	// Lecture du nombre de héros
	size_t nHeros = lireUintTailleVariable(fichierHeros);

	// Lecture et création des héros
	for (auto i = 0; i < nHeros; i++) {
		string nom = lireString(fichierHeros);
		string jeuParution = lireString(fichierHeros);
		string ennemi = lireString(fichierHeros);
		Heros herosLu(nom, jeuParution, ennemi);

		size_t nAllies = lireUintTailleVariable(fichierHeros);
		for (auto j = 0; j < nAllies; j++) {
			herosLu.ajouterAllie(lireString(fichierHeros));
		}
		listeHeros.push_back(herosLu);
		personnages.push_back(move(make_unique<Heros>(herosLu)));
	}

	// Lecture du nombre de vilains
	size_t nVilains = lireUintTailleVariable(fichierVilains);

	// Lecture et création des vilains
	for (auto i = 0; i < nVilains; i++) {
		string nom = lireString(fichierVilains);
		string jeuParution = lireString(fichierVilains);
		string objectif = lireString(fichierVilains);

		Vilain vilainLu(nom, jeuParution, objectif);
		vilains.push_back(vilainLu);
		personnages.push_back(move(make_unique<Vilain>(vilainLu)));
	}

	// Affichage des héros
	for (auto&& elem : listeHeros) {
		elem.afficher(cout);
	}

	// Affichage des vilains
	for (auto&& elem : vilains) {
		elem.afficher(cout);
	}

	// Affichage des personnages
	for (auto&& elem : personnages) {
		elem->afficher(cout);
	}

	// Création d'un VilainHéros
	VilainHeros vilainHeros(vilains[4], listeHeros[2]);
	vilainHeros.afficher(cout);

	// Vérification de l'affichage adapté
	personnages.push_back(move(make_unique<VilainHeros>(vilainHeros)));

	// Affichage des personnages
	for (auto&& elem : personnages) {
		elem->afficher(cout);
	}

}
