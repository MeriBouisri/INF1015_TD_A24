/**
* Classe Vilain
* \file   Vilain.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 04 novembre 2024
*/

#pragma once

#include "Personnage.hpp"
#include <string>

using namespace std;



class Vilain : virtual public Personnage {

public:
	Vilain() = default;
	Vilain(const string& nom, const string& jeuParution, const string& objectif) : Personnage(nom, jeuParution), objectif_(objectif) {}

	string getObjectif() const {
		return objectif_;
	}

	ostream& afficher(ostream& os) override;

	// TODO : theme in constant
	ostream& changerCouleur(ostream& os, int theme) override;

protected:
	ostream& afficherSupplement(ostream& os);



private:
	string objectif_;
};
