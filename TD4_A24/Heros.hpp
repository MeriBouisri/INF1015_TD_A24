/**
* Classe Heros
* \file   Heros.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 24 novembre 2024
*/

#pragma once

#include <string>

using namespace std;



class Heros : public Personnage {

public:
	Heros() = default;
	Heros(const string& nom, const string& jeuParution) : Personnage(nom, jeuParution) {}
};
