/**
* Interface Affichable pour les classes affichables
* \file   Affichable.hpp
* \author Bouisri et Xa
* \date   5 novembre 2024
* Créé le 22 octobre 2024
*/

#pragma once

#include <iostream>

using namespace std;


class Affichable {
public:
	virtual ostream& afficher(ostream& os) const = 0;
	virtual ostream& changerCouleur(ostream& os, int theme) const = 0;
};