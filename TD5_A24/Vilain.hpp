/**
* Classe représentant un vilain
* \file   Vilain.hpp
* \author Département de génie informatique et génie logiciel
* \date   19 novembre 2024
* Créé le 5 novembre 2024
*/

#pragma once
#include "Personnage.hpp"
#include <iostream>
#include <string>
using namespace std;

class Vilain : public virtual Personnage
{
public:
	// Vilain() = default;  // Non nécessaire.

	//Vilain(const string& nom, const string& jeu, const string& objectif)  // Non nécessaire si on construit toujour en lisant du istream.
	//	: Personnage(nom, jeu), objectif_(objectif) {}

	Vilain(istream& fichier) : Personnage(fichier), objectif_(lireString(fichier)) {}

	void afficher(ostream& os) const override {
		Personnage::afficher(os);
		afficherSpecificites(os);
	}
	void afficherSpecificites(ostream& os) const {  // Pourrait être protected.
		os << "Objectif : " << objectif_ << "\n";
	}
	void changerCouleur(ostream& os, Theme theme) const override {
		switch (theme) {
		case Theme::clair: changerCouleurTexteFond(os, Couleur::rouge, Couleur::blancIntense); break;
		default:           changerCouleurTexteFond(os, Couleur::rougeIntense, Couleur::noir); break;
		}
	}

	// Getter nécessaire pour la construction du VilainHeros (puisque généralement les attributs sont private et non protected):
	const string& getObjectif() const { return objectif_; }

private:
	string objectif_;
};
