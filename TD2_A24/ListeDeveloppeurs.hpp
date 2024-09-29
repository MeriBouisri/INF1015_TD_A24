#pragma once
#include <cstddef>
#include "Developpeur.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.

class ListeDeveloppeurs {
public:
	ListeDeveloppeurs();
	~ListeDeveloppeurs();
	void afficher();
	void augmenterCapacite(size_t nouvelleCapacite);
	void ajouterDeveloppeur(Developpeur& developpeurAAjouter);
	void retirerDeveloppeur(const Developpeur* developpeurARetirer);
	static void testListeDeveloppeurs();

private:
	std::size_t nElements_, capacite_;
	Developpeur** developpeurs_;

	gsl::span<Developpeur*> span();
	void detruireDeveloppeur(Developpeur* developpeurADetruire);
};