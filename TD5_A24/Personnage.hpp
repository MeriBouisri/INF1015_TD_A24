/**
* Classe représentant un personnage
* \file   Personnage.hpp
* \author Bouisri, Département de génie informatique et génie logiciel et Xa
* \date   19 novembre 2024
* Créé le 5 novembre 2024
*/

#pragma once
#include "Affichable.hpp"
#include "lectureBinaire.hpp"
#include <iostream>
#include <string>
using namespace std;

class Personnage : public Affichable
{
public:
	Personnage() = default;  // Non nécessaire dans le TD4, pourrait servir dans le TD5.

	Personnage(string nom) : nom_(nom), parutionJeu_("") {}

	Personnage(string nom, string jeu) : nom_(nom), parutionJeu_(jeu) {}  // Nécessaire pour la construction du VilainHeros.

	Personnage(istream& fichier) : nom_(lireString(fichier)), parutionJeu_(lireString(fichier)) {}

	void afficher(ostream& os) const override {
		os << "Nom : " << nom_ << "\n";
		os << "Jeu de parution : " << parutionJeu_ << endl;
	}



	//void changerCouleur(ostream& os, Theme theme) const override {  // On n'a aucun Personnage directement dans le TD4.
	//	switch (theme) {
	//	case Theme::clair : changerCouleurTexteFond(os, Couleur::noir, Couleur::blancIntense); break;
	//	default :           changerCouleurTexteFond(os, Couleur::blancGris, Couleur::noir); break;
	//	}
	//}

	friend bool operator<(const Personnage& l, const Personnage& r) {
		return l.nom_ < r.nom_;
	}

	bool operator<(const Personnage& p) {
		return nom_ < p.nom_;
	}

	// Les getters sont nécessaires pour la construction du VilainHero (puisque généralement les attributs sont private et non protected):
	const string& getNom() const { return nom_; }
	const string& getParutionJeu() const { return parutionJeu_; }

private:
	string nom_;
	string parutionJeu_;
};
