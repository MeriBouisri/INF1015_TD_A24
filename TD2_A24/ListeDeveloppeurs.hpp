#pragma once
#include <cstddef>
#include "Developpeur.hpp"

class ListeDeveloppeurs {
public:
	ListeDeveloppeurs();
	~ListeDeveloppeurs();
	void afficher();
	void augmenterCapacite(size_t nouvelleCapacite);
	void ajouterDeveloppeur(Developpeur& developpeurAAjouter);
	void retirerDeveloppeur(Developpeur* developpeurARetirer);
	static void testListeDeveloppeurs();

private:
	std::size_t nElements_, capacite_;
	Developpeur** developpeurs_;

	gsl::span<Developpeur*> span();
	void detruireDeveloppeur(Developpeur* developpeurADetruire);
};