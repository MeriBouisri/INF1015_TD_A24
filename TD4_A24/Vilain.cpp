/**
* Implémentation de la classe Vilain
* \file   Vilain.cpp
* \author Bouisri et Xa
* \date   5 novembre 2024
* Créé le 22 octobre 2024
*/

#include "Vilain.hpp"


string Vilain::getInformationsSupplementaires() const {
	string chaine = "Objectif : " + objectif_;
	return chaine;
}


ostream& Vilain::changerCouleur(ostream& os, int theme) const {
	switch (theme) {
	case 0:
		os << "\033[38;5;209m"; // Ce cas n'est pas couvert, car nous avons choisi le thème par défaut pour l'affichage.
		break;
	default:
		os << "\033[38;5;214m";
		break;
	}
	return os;
}