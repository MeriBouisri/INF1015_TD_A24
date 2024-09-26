#pragma once
#include <cstddef>
#include "Developpeur.hpp"

class ListeDeveloppeurs {
public:
	ListeDeveloppeurs();
	~ListeDeveloppeurs();
	void afficher();
	void augmenterCapacite(size_t nouvelleCapacite);
	void ajouterDeveloppeur(Developpeur& developpeur);
	void eneleverDeveloppeur(Developpeur* developpeurASupprimer);

private:
	std::size_t nElements_, capacite_;

	Developpeur** developpeurs_;
	gsl::span<Developpeur*> span();
	void detruireDeveloppeur(Developpeur* developpeur);
};