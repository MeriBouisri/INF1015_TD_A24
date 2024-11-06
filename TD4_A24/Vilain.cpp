/**
* Classe Vilain
* \file   Vilain.cpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 04 novembre 2024
*/

#include "Vilain.hpp"

ostream& Vilain::afficher(ostream& os) const {
	Personnage::afficher(os);
	return afficherSupplement(os) << "\n\n";
}

ostream& Vilain::afficherSupplement(ostream& os) const {
	return os << "Objectif : " << objectif_;
}


ostream& Vilain::changerCouleur(ostream& os, int theme) const {
	switch (theme) {
	case 0:
		os << "\033[38;5;226m";
		break;
	default:
		os << "\033[38;5;33m";
		break;
	}
	return os;
}