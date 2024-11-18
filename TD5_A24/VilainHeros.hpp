#pragma once
#include "Heros.hpp"
#include "Vilain.hpp"
#include <iostream>
using namespace std;

class VilainHeros : public Vilain, public Heros
{
public:
	VilainHeros(const Vilain& v, const Heros& h) :
		Personnage(v.getNom() + "-" + h.getNom(), v.getParutionJeu() + "-" + h.getParutionJeu()),
		Vilain(v),
		Heros(h),
		mission_(v.getObjectif() + " dans le monde de " + h.getParutionJeu())
	{}

	void afficher(ostream& os) const override {
		Personnage::afficher(os);
		Vilain::afficherSpecificites(os);
		Heros::afficherSpecificites(os);
		os << "Mission spéciale: " << mission_ << endl;
	}

	void changerCouleur(ostream& os, Theme theme) const override {
		switch (theme) {
		case Theme::clair : changerCouleurTexteFond(os, Couleur::magenta, Couleur::blancIntense); break;
		default :           changerCouleurTexteFond(os, Couleur::bleuIntense, Couleur::noir); break;
		}
	}

private:
	string mission_;
};
