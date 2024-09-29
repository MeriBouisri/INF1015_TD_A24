/**
* Implémentation de la classe ListeDeveloppeurs, représentant une liste de développeurs de jeu vidéo
* \file   ListeDeveloppeurs.cpp
* \author Bouisri et Xa
* \date   29 septembre 2024
* Créé le 17 septembre 2024
*/

#include "ListeDeveloppeurs.hpp"
#include "gsl/span"
#include <iostream>
#include <cassert>

ListeDeveloppeurs::ListeDeveloppeurs() {
	nElements_ = 0;
	capacite_ = 0;
	developpeurs_ = new Developpeur * [0];
}


ListeDeveloppeurs::~ListeDeveloppeurs() {
	for (Developpeur* developpeur : span()) {
		detruireDeveloppeur(developpeur);
	}

	delete[] developpeurs_;
	developpeurs_ = nullptr;
	std::cout << "[SUCCES][~ListeDeveloppeurs()] Liberation de memoire : [developpeurs_ = " << developpeurs_ << std::endl;
}


void ListeDeveloppeurs::detruireDeveloppeur(Developpeur* developpeurADetruire) {
	std::cout << "[INFO][detruireDeveloppeur] Destruction en cours : [developpeurADetruire->nom = " << developpeurADetruire->obtenirNom() << "]" << std::endl;
	developpeurADetruire->~Developpeur();
}


gsl::span<Developpeur*> ListeDeveloppeurs::span() {
	return gsl::span<Developpeur*>(developpeurs_, nElements_);
}


void ListeDeveloppeurs::afficher() {
	for (Developpeur* developpeur : span()) {
		developpeur->afficherJeux();
	}
}


void ListeDeveloppeurs::augmenterCapacite(size_t nouvelleCapacite) {
	Developpeur** newDevelopers = new Developpeur * [nouvelleCapacite];
	int i = 0;

	for (Developpeur* developpeur : span()) {
		newDevelopers[i++] = developpeur;
	}

	delete[] developpeurs_;
	developpeurs_ = newDevelopers;
	capacite_ = nouvelleCapacite;
}


void ListeDeveloppeurs::ajouterDeveloppeur(Developpeur& developpeurAAjouter) {
	if (nElements_ >= capacite_) {
		if (capacite_ <= 0) {
			augmenterCapacite(1);
		}
		else {
			augmenterCapacite(capacite_ * 2);
		}
	}
	developpeurs_[nElements_++] = &developpeurAAjouter;
}


void ListeDeveloppeurs::retirerDeveloppeur(const Developpeur* developpeurARetirer) {
	gsl::span<Developpeur*> spanDeveloperList = span();
	for (Developpeur*& developpeur : spanDeveloperList) {
		if (developpeur == developpeurARetirer) {
			if (nElements_ > 1) {
				developpeur = spanDeveloperList[nElements_ - 1];
			}
			nElements_--;
		}
	}
}


void ListeDeveloppeurs::testListeDeveloppeurs() {
	std::cout << "[TEST] Début du testListeDeveloppeurs()" << std::endl;

	ListeDeveloppeurs liste;
	std::cout << "[INFO] ListeDeveloppeurs vide créée." << std::endl;

	Developpeur dev1("Alice");
	Developpeur dev2("Bob");
	Developpeur dev3("Charlie");

	liste.ajouterDeveloppeur(dev1);
	liste.ajouterDeveloppeur(dev2);
	liste.ajouterDeveloppeur(dev3);
	std::cout << "[INFO] Développeurs ajoutés à la ListeDeveloppeurs." << std::endl;

	liste.afficher();
	std::cout << "[INFO] Affichage de ListeDeveloppeurs" << std::endl;

	liste.retirerDeveloppeur(&dev2);
	std::cout << "[INFO] Bob retiré de la ListeDeveloppeurs" << std::endl;

	liste.afficher();
	std::cout << "[INFO] Affichage de la ListeDeveloppeurs" << std::endl;

	Developpeur dev4("Diana");
	Developpeur dev5("Eve");

	liste.ajouterDeveloppeur(dev4);
	liste.ajouterDeveloppeur(dev5);
	std::cout << "[INFO] 2 Développeurs ajoutés à la ListeDeveloppeurs." << std::endl;

	liste.afficher();
	std::cout << "[INFO] Affichage de la ListeDeveloppeurs" << std::endl;

	std::cout << "[TEST] Fin du testListeDeveloppeurs()" << std::endl;
}