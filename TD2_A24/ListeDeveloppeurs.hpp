#pragma once
#include <cstddef>
#include "Developpeur.hpp"
#include "gsl/span"

class ListeDeveloppeurs
{
	//TODO: En faire une classe qui suit les principes OO.
	//TODO: On veut pouvoir ajouter et enlever un Developpeur* de la liste, avec réallocation dynamique tel que faite pour ListeJeux.
	//NOTE: Le code sera principalement copié de certaines fonctions écrites pour la partie 1, mais mises dans une classe.
private:
	std::size_t nElements_, capacite_;
	Developpeur** elements_;
	gsl::span<Developpeur*> span();
	void detruireDeveloppeur(Developpeur* developer);
public:
	ListeDeveloppeurs();
	~ListeDeveloppeurs();
	void afficher();
	void increaseCapacity(size_t newCapacity);
	void addDeveloper(Developpeur& developer);
	void removeDeveloper(Developpeur* developerToDelete);
};