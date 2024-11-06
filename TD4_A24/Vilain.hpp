/**
* Classe représentant un vilain
* \file   Vilain.hpp
* \author Bouisri et Xa
* \date   5 novembre 2024
* Créé le 22 octobre 2024
*/

#pragma once

#include "Personnage.hpp"
#include "verification_allocation.hpp"
#include <string>

using namespace std;

class Vilain : virtual public Personnage {
public:
	Vilain(const string& nom, const string& jeuParution, const string& objectif) : Personnage(nom, jeuParution), objectif_(objectif) {}


	string getObjectif() const {
		return objectif_;
	}


	ostream& changerCouleur(ostream& os, int theme) const override;


protected:
	string getInformationsSupplementaires() const override;


private:
	string objectif_;
};
