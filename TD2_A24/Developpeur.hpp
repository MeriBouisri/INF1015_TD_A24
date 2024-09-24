#pragma once
#include <string>
#include <iostream>
#include "ListeJeux.hpp"
#include "Jeu.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.

class Developpeur
{
	//TODO: En faire une classe qui suit les principes OO.
	//TODO: La destruction d'un Developpeur doit s'assurer que la désallocation de ListeJeux est faite.
	//TODO: Les méthodes à faire...

	std::pair<std::string, ListeJeux> paireNomJeux_;

	public:
		Developpeur(std::string nom);
		~Developpeur();
		std::string getName() const;
		ListeJeux getGameList();
		void clearGameList();
		int countGames(ListeJeux& gameList);
		void updateGameList(ListeJeux& gameList);
		void printGameList();
		static void test();
};
