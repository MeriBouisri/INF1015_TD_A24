/**
* Classe Personnage
* \file   Personnage.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 24 novembre 2024
*/

#pragma once

#include "Affichable.hpp"
#include <iostream>
#include <string>

using namespace std;



class Personnage : public Affichable {

public:
	Personnage() = default;
	Personnage(const string& nom, const string& jeuParution) : nom_(nom), jeuParution_(jeuParution) {}
	virtual ~Personnage() = default;


	string getJeuParution() const {
		return jeuParution_;
	}

	ostream& afficher(ostream& os) override;

	string getNom() const {
		return nom_;
	}

private:
	string nom_;
	string jeuParution_;
};
