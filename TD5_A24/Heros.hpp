#pragma once
#include "cppitertools/range.hpp"
#include "lireVectorDuFichier.hpp"
#include "Personnage.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace iter;

class Heros : public virtual Personnage
{
public:
	Heros() = default;  // Non nécessaire dans le TD4, pourrait servir dans le TD5.

	Heros(const string& nom, const string& jeu, const string& ennemi)  // Non nécessaire si on construit toujours en lisant du istream (TD4).
		: Personnage(nom, jeu), ennemi_(ennemi) {}

	Heros(istream& fichier) : Personnage(fichier), ennemi_(lireString(fichier)), allies_(lireVectorDuFichier<string>(fichier)) {}

	void afficher(ostream& os) const override {
		Personnage::afficher(os);
		afficherSpecificites(os);
	}
	void afficherSpecificites(ostream& os) const {  // Pourrait être protected.
		os << "Ennemi : " << ennemi_ << "\n";
		os << "Alliés :\n";
		for (auto&& allie : allies_)
			os << "\t" << allie << "\n";
	}
	void changerCouleur(ostream& os, Theme theme) const override { // L'énoncé demande d'avoir des couleurs différentes pour les différentes classes, donc on override dans les classes...
		switch (theme) {
		case Theme::clair: changerCouleurTexteFond(os, Couleur::bleu, Couleur::blancIntense); break;
		default:           changerCouleurTexteFond(os, Couleur::vertIntense, Couleur::noir); break;
		}
	}



	// Les getters sont non nécessaires:
	//const string& getEnnemi() const { return ennemi_; }
	//const vector<string>& getAllies() const { return allies_; }

private:
	string ennemi_;
	vector<string> allies_;
};
