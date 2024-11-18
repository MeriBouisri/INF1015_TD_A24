/**
* Implémentation de la classe Personnage
* \file   Personnage.cpp
* \author Bouisri et Xa
* \date   5 novembre 2024
* Créé le 22 octobre 2024
*/

#include "Personnage.hpp"

ostream& Personnage::afficher(ostream& os) const {
	changerCouleur(os, 1);
	return os << "Nom : " << nom_ << "\n" << "Parution : " << jeuParution_ << "\n" << getInformationsSupplementaires() << "\033[0m" << "\n\n";
}