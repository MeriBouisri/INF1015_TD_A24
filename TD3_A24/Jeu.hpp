#pragma once
#include "Concepteur.hpp"
#include "Liste.hpp"
#include <string>

struct Jeu
{
	std::string titre;
	int anneeSortie;
	std::string developpeur;
	Liste<Concepteur> concepteurs;
};