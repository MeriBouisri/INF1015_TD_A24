/**
* Classe Personnage
* \file   Personnage.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 24 novembre 2024
*/

#pragma once

#include "Affichable.hpp"
#include <string>

using namespace std;

class Personnage : public Affichable {

public:
	Personnage() = default;
	Personnage(const string& nom, const string& jeuParution) : nom_(nom), jeuParution_(jeuParution) {}

	virtual ostream& afficher(ostream& fluxSortie) override {
		return fluxSortie << *this;
	}

	virtual ostream& changerCouleur(ostream& fluxSortie, int theme) override {
	}

	string getNom() const {
		return nom_;
	}
	string getJeuParution() const {
		return jeuParution_;
	}

	friend ostream& operator<<(ostream& os, const Personnage& p) {
		return os << "Nom : " << p.nom_
			<< "\nParution : " << p.jeuParution_ << endl;
	}

private:
	string nom_;
	string jeuParution_;
};
