#pragma once

#include <iostream>

using namespace std;


class Affichable {
public:
	virtual ostream& afficher(ostream& os) = 0;
	virtual ostream& changerCouleur(ostream& os, int theme) = 0;
};