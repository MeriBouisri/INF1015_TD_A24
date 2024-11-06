/**
* Classe Heros
* \file   Heros.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 24 novembre 2024
*/

#include "Heros.hpp"

ostream& Heros::afficher(ostream& os) const {
	Personnage::afficher(os);
	return afficherSupplement(os) << "\n";
}

ostream& Heros::afficherSupplement(ostream& os) const {
	os << "Ennemi : " << nomEnnemi_ << "\nAlli�s :" << "\n";
	for (const auto& a : nomsAllies_) {
		os << "\t" << a << "\n";
	}
	return os;
}

ostream& Heros::changerCouleur(ostream& os, int theme) const {
	switch (theme) {
	case 0:
		os << "\033[38;5;214m";
		break;
	default:
		os << "\033[38;5;37m";
		break;
	}
	return os;
}