#pragma once
#include <string>
#include <iostream>
#include "ListeJeux.hpp"
#include "Jeu.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.

class Developpeur {
public:
	Developpeur(std::string nom);
	~Developpeur();
	std::string obtenirNom() const;
	ListeJeux obtenirJeux() const;
	void viderJeux();
	int compterJeux(ListeJeux& jeux) const;
	void actualiserJeux(ListeJeux& jeux);
	void afficherJeux() const;
	static bool testDeveloppeur();
	static bool testActualiserJeux();
	static bool testCompterJeux();
	static bool testViderJeux();
	static bool testObtenirNom();
	static bool testObtenirJeux();


private:
	std::pair<std::string, ListeJeux> paireNomJeux_;
};