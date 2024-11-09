/**
* Classe représentant un héros
* \file   Heros.hpp
* \author Bouisri et Xa
* \date   5 novembre 2024
* Créé le 22 octobre 2024
*/

#pragma once

#include "Personnage.hpp"
#include <string>
#include <vector>

using namespace std;

class Heros : virtual public Personnage {
public:
	Heros(const string& nom, const string& jeuParution, const string& nomEnnemi) : Personnage(nom, jeuParution), nomEnnemi_(nomEnnemi), nomAllies_({}) {
	}


	ostream& changerCouleur(ostream& os, int theme) const override;


	void ajouterAllie(const string& nomAllie) {
		nomAllies_.push_back(nomAllie);
	}


protected:
	string getInformationsSupplementaires() const override;


private:
	vector<string> nomAllies_;
	string nomEnnemi_;
};