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
	return afficherSupplement(os);
}

ostream& Vilain::afficherSupplement(ostream& os) {
	return os << "Objectif : " << objectif_ << "\n";
}


ostream& Vilain::changerCouleur(ostream& os, int theme) {
	switch (theme) {
	case 0:
		os << "\033[196m";
		break;
	case 1:
		os << "\033[11m";
		break;
	}
	return os;
}