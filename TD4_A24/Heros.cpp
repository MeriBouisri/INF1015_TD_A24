/**
* Immplémentation de la classe Heros
* \file   Heros.cpp
* \author Bouisri et Xa
* \date   5 novembre 2024
* Créé le 22 octobre 2024
*/

#include "Heros.hpp"

string Heros::getInformationsSupplementaires() const {
	string chaine = "Ennemi : " + nomEnnemi_ + "\nAlliés : ";
	for (const auto& a : nomAllies_) {
		chaine += "\n\t" + a;
	}
	return chaine;
}

ostream& Heros::changerCouleur(ostream& os, int theme) const {
	switch (theme) {
	case 0:
		os << "\033[38;5;123m"; // Ce cas n'est pas couvert, car nous avons choisi le thème par défaut pour l'affichage.
		break;
	default:
		os << "\033[38;5;117m";
		break;
	}
	return os;
}