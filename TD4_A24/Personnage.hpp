/**
* Classe repr�sentant un personnage
* \file   Personnage.hpp
* \author Bouisri et Xa
* \date   5 novembre 2024
* Cr�� le 22 octobre 2024
*/

#pragma once

#include "Affichable.hpp"
#include "verification_allocation.hpp"
#include <iostream>
#include <string>

using namespace std;

class Personnage : public Affichable {

public:
	Personnage(const string& nom, const string& jeuParution) : nom_(nom), jeuParution_(jeuParution) {}
	virtual ~Personnage() = default;


	string getJeuParution() const {
		return jeuParution_;
	}


	ostream& afficher(ostream& os) const override;


	string getNom() const {
		return nom_;
	}


protected:
	virtual string getInformationsSupplementaires() const = 0;


private:
	string nom_;
	string jeuParution_;
};