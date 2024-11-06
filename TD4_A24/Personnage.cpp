/**
* Classe Personnage
* \file   Personnage.cpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 24 novembre 2024
*/

#include "Personnage.hpp"

ostream& Personnage::afficher(ostream& os) const {
	return os << "Nom : " << nom_ << "\n" << "Parution : " << jeuParution_ << "\n";
}