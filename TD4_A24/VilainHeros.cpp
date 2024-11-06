/**
* Classe VilainHeros
* \file   VilainHeros.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 24 novembre 2024
*/

#include "VilainHeros.hpp"
VilainHeros::VilainHeros(const Vilain& vilain, const Heros& heros) : Personnage(vilain.getNom() + "-" + heros.getNom(), vilain.getJeuParution() + "-" + heros.getJeuParution()), Vilain(vilain), Heros(heros), missionSpeciale_(vilain.getObjectif() + " dans le monde de " + heros.getJeuParution()) {
}

ostream& VilainHeros::afficher(ostream& os) const {
	Personnage::afficher(os);
	return afficherSupplement(os) << "\n\n";
}

ostream& VilainHeros::afficherSupplement(ostream& os) const {
	Vilain::afficherSupplement(os);
	Heros::afficherSupplement(os);
	return os << "Mission speciale : " << missionSpeciale_;
}

ostream& VilainHeros::changerCouleur(ostream& os, int theme) const {
	switch (theme) {
	case 0:
		os << "\033[38;5;201m";
		break;
	default:
		os << "\033[38;5;93m";
		break;
	}
	return os;
}
