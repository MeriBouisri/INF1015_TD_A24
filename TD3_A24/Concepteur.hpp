#pragma once

#include "Jeu.hpp"
#include "Liste.hpp"
#include <string>

struct Concepteur
{
	std::string nom;
	int anneeNaissance;
	std::string pays;

	//friend std::ostream& operator<<(std::ostream& os, const shared_ptr<Concepteur>& c);
};
