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



using namespace std;



class VilainHeros : public Vilain, public Heros {

public:
	VilainHeros() = default;
	VilainHeros(const Vilain& vilain, const Heros& heros);

	ostream& afficher(ostream& os) override;

	// TODO : theme in constant
	ostream& changerCouleur(ostream& os, int theme) override;


protected:
	ostream& afficherSupplement(ostream& os);

private:
	string missionSpeciale_;


};
