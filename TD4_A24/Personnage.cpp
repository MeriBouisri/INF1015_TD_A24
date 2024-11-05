/**
* Classe Personnage
* \file   Personnage.cpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 24 novembre 2024
*/

#include "Personnage.hpp"

ostream& Personnage::afficher(ostream& os) {
	return os << "Nom : " << nom_ << "\n" << "Parution : " << jeuParution_ << "\n";
}

ostream& Personnage::changerCouleur(ostream& os, int theme) {
	switch (theme) {
	case 0:
		os << "\033[38;5;196m";
		break;
	default:
		os << "\033[38;5;34m";
		break;
	}
	return os;
}