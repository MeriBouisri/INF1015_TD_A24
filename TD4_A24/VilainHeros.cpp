/**
* Implémentaion de la classe VilainHeros
* \file   VilainHeros.cpp
* \author Bouisri et Xa
* \date   5 novembre 2024
* Créé le 22 octobre 2024
*/

#include "VilainHeros.hpp"
VilainHeros::VilainHeros(const Vilain& vilain, const Heros& heros) : Personnage(vilain.getNom() + "-" + heros.getNom(), vilain.getJeuParution() + "-" + heros.getJeuParution()), Vilain(vilain), Heros(heros), missionSpeciale_(vilain.getObjectif() + " dans le monde de " + heros.getJeuParution()) {
}

string VilainHeros::getInformationsSupplementaires() const {
	string chaine = Vilain::getInformationsSupplementaires() + "\n" + Heros::getInformationsSupplementaires() + "\n" + "Mission spéciale : " + missionSpeciale_;
	return chaine;
}

ostream& VilainHeros::changerCouleur(ostream& os, int theme) const {
	switch (theme) {
	case 0:
		os << "\033[38;5;228m"; // Ce cas n'est pas couvert, car nous avons choisi le thème par défaut pour l'affichage.
		break;
	default:
		os << "\033[38;5;118m";
		break;
	}
	return os;
}
