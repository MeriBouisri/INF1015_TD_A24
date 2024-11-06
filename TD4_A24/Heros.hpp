/**
* Classe Heros
* \file   Heros.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 24 novembre 2024
*/

#pragma once

#include "Personnage.hpp"
#include <string>
#include <vector>

using namespace std;



class Heros : virtual public Personnage {

public:
	Heros() = default;
	Heros(const string& nom, const string& jeuParution, const string& nomEnnemi) : Personnage(nom, jeuParution), nomEnnemi_(nomEnnemi), nomsAllies_({}) {
	}

	ostream& afficher(ostream& os) override;

	ostream& changerCouleur(ostream& os, int theme) override;

	void ajouterAllie(const string& nomAllie) {
		nomsAllies_.push_back(nomAllie);
	}

protected:
	ostream& afficherSupplement(ostream& os);

private:
	vector<string> nomsAllies_; // TODO : maybe not right type
	string nomEnnemi_;
};
