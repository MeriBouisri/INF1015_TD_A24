/**
* Classe Vilain
* \file   Vilain.cpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 04 novembre 2024
*/

#include "Vilain.hpp"

ostream& Vilain::afficher(ostream& os) {
	Personnage::afficher(os);
	return afficherSupplement(os) << "\n";
}

ostream& Vilain::afficherSupplement(ostream& os) {
	return os << "Objectif : " << objectif_ << "\n";
}


ostream& Vilain::changerCouleur(ostream& os, int theme) {
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