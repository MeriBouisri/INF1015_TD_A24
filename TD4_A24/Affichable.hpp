#pragma once

#include <iostream>

using namespace std;


class Affichable {
public:
	virtual ostream& afficher(ostream& os) const = 0;
	virtual ostream& changerCouleur(ostream& os, int theme) const = 0;
};