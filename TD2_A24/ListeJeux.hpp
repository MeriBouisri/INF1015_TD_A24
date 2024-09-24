#pragma once
#include <cstddef>
#include <gsl/span>
#include <iostream>
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
// La déclaration suivante plutôt qu'un #include "Jeu.hpp" est nécessaire sinon il y aurait une boucle d'inclusion (ListeJeux.hpp > Jeu.hpp > ListeConcepteurs.hpp > Concepteur.hpp > ListeJeux.hpp), la boucle serait arrêtée par le "pragma once" mais ListeJeux ne serait alors pas déclaré lors de la compilation de Concepteur.
struct Jeu;  // Déclaration avancée ("forward declaration") pour pouvoir utilise le nom du type avant qu'il soit complètement défini.

struct ListeJeux
{
	std::size_t nElements, capacite;
	Jeu** elements;
	
    static void addGame(Jeu& game, ListeJeux& gameList) {
    	if (gameList.nElements >= gameList.capacite) {
    		if (gameList.capacite <= 0) {
    			ListeJeux::increaseCapacity(1, gameList);
    		}
    		else {
    			ListeJeux::increaseCapacity(gameList.capacite * 2, gameList);
    		}
    	}
    	gameList.elements[gameList.nElements++] = &game;
    }

	//TODO: Fonction qui enlève un jeu de ListeJeux.
	// Attention, ici il n'a pas de désallocation de mémoire. Elle enlève le
	//// pointeur de la ListeJeux, mais le jeu pointé existe encore en mémoire.
	//// Puisque l'ordre de la ListeJeux n'a pas être conservé, on peut remplacer le
	//// jeu à être retiré par celui présent en fin de liste et décrémenter la taille
	//// de celle-ci.
	static void removeGame(Jeu* gameToDelete, ListeJeux& gameList) {
		gsl::span<Jeu*> spanGameList = gsl::span<Jeu*>(gameList.elements, gameList.nElements);
		for (Jeu* game : spanGameList) {
			if (game == gameToDelete) {
				game = spanGameList[--gameList.nElements];
			}
		}
	}

    static void increaseCapacity(size_t newCapacity, ListeJeux& gameList) {
    	Jeu** newGames = new Jeu * [newCapacity];
    	gsl::span<Jeu*> spanGameList = gsl::span<Jeu*>(gameList.elements, gameList.nElements);
    	int i = 0;

    	for (Jeu* game : spanGameList) {
    		newGames[i++] = game;
    	}

    	delete[] gameList.elements;

    	gameList.elements = newGames;
    	gameList.capacite = newCapacity;
    }

	static gsl::span<Jeu*> span(const ListeJeux& gameList) {
		return gsl::span<Jeu*>(gameList.elements, gameList.nElements);
	}

	static void test() {

		// ListeJeux::addGame //

		// ListeJeux::removeGame //

		// ListeJeux::increaseCapacity //
	}
};
