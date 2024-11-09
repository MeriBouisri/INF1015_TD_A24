/**
* Classe représentant un vilain héros
* \file   VilainHeros.hpp
* \author Bouisri et Xa
* \date   5 novembre 2024
* Créé le 22 octobre 2024
*/

#pragma once

#include "Heros.hpp"
#include "verification_allocation.hpp"
#include "Vilain.hpp"
#include <string>
#include <vector>



using namespace std;



class VilainHeros : public Vilain, public Heros {

public:
	VilainHeros(const Vilain& vilain, const Heros& heros);

	ostream& changerCouleur(ostream& os, int theme) const override;

protected:
	string getInformationsSupplementaires() const override;

private:
	string missionSpeciale_;
};
