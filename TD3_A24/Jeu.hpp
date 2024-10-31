#pragma once
#include "Concepteur.hpp"
#include "Liste.hpp"
#include <functional>
#include <string>
#include "verification_allocation.hpp"

using std::function;

struct Jeu
{
	std::string titre;
	int anneeSortie;
	std::string developpeur;
	Liste<Concepteur> concepteurs;

	Jeu() = default;

	Jeu(const Jeu& other) : titre(other.titre), anneeSortie(other.anneeSortie), developpeur(other.developpeur), concepteurs(other.concepteurs) {}
	
	shared_ptr<Concepteur> trouverConcepteur(const function<bool(const shared_ptr<Concepteur>&)>& critere) const {
		return concepteurs.trouver(critere);
	}
};