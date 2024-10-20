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


};