#pragma once

using namespace std;

class Affichable {
public:
	virtual ostream& afficher(ostream& fluxSortie) = 0;
	virtual ostream& changerCouleur(ostream& fluxSortie, int theme) = 0;
};


