/**
* Classe VilainHeros
* \file   VilainHeros.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 24 novembre 2024
*/

#include "VilainHeros.hpp"
VilainHeros::VilainHeros(const Vilain& vilain, const Heros& heros) : Vilain(vilain), Heros(heros), missionSpeciale_(vilain.getObjectif() + " dans le monde de " + heros.getJeuParution()) {
	Personnage::setNom(vilain.getNom() + "-" + heros.getNom());
	Personnage::setJeuParution(vilain.getJeuParution() + "-" + heros.getJeuParution());
	// TODO : Changer couleur 
}

ostream& VilainHeros::afficher(ostream& os) {
	Personnage::afficher(os);
	return afficherSupplement(os);
}

ostream& VilainHeros::afficherSupplement(ostream& os) {
	Vilain::afficherSupplement(os);
	Heros::afficherSupplement(os);
	return os << "Mission speciale : " << missionSpeciale_ << "\n";
}

ostream& VilainHeros::changerCouleur(ostream& os, int theme) {
	switch (theme) {
	case 0:
		os << "\033[15m";
		break;
	case 1:
		os << "\033[214m";
		break;
	}
	return os;
}
