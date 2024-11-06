/**
* Classe VilainHeros
* \file   VilainHeros.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 24 novembre 2024
*/

#pragma once

#include "Heros.hpp"
#include "Vilain.hpp"
#include <string>
#include <vector>
#include "verification_allocation.hpp"



using namespace std;



class VilainHeros : public Vilain, public Heros {

public:
	VilainHeros(const Vilain& vilain, const Heros& heros);

	ostream& afficher(ostream& os) const override;

	ostream& changerCouleur(ostream& os, int theme) const override;

protected:
	ostream& afficherSupplement(ostream& os) const override;

private:
	string missionSpeciale_;


};
