#pragma once
#include "Concepteur.hpp"
#include "Liste.hpp"
#include <functional>
#include <string>

using std::function;

struct Jeu
{
	std::string titre;
	int anneeSortie;
	std::string developpeur;
	Liste<Concepteur> concepteurs;

	shared_ptr<Concepteur> chercher(const function<bool(const shared_ptr<Concepteur>&)>& critere) const {
		return concepteurs.chercher(critere);
	}
};