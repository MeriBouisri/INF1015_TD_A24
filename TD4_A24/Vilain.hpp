/**
* Classe Vilain
* \file   Vilain.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 04 novembre 2024
*/

#pragma once

#include <string>

using namespace std;



class Vilain : public Personnage {
    
    public:
        Vilain() = default;
        Vilain(const string& nom, const string& jeuParution) : Personnage(nom, jeuParution) {}
};
