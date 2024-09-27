#pragma once
#include <cstddef>
#include <gsl/span>
#include <iostream>
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.
// La déclaration suivante plutôt qu'un #include "Jeu.hpp" est nécessaire sinon il y aurait une boucle d'inclusion (ListeJeux.hpp > Jeu.hpp > ListeConcepteurs.hpp > Concepteur.hpp > ListeJeux.hpp), la boucle serait arrêtée par le "pragma once" mais ListeJeux ne serait alors pas déclaré lors de la compilation de Concepteur.
struct Jeu;  // Déclaration avancée ("forward declaration") pour pouvoir utilise le nom du type avant qu'il soit complètement défini.

struct ListeJeux {
	std::size_t nElements, capacite;
	Jeu** elements;

	static void ajouterJeu(Jeu& jeu, ListeJeux& jeux) {
		if (jeux.nElements >= jeux.capacite) {
			if (jeux.capacite <= 0) {
				ListeJeux::augmenterCapacite(1, jeux);
			}
			else {
				ListeJeux::augmenterCapacite(jeux.capacite * 2, jeux);
			}
		}
		jeux.elements[jeux.nElements++] = &jeu;
	}

	static void enleverJeu(Jeu* jeuASupprimer, ListeJeux& jeux) {
		gsl::span<Jeu*> spanJeux = gsl::span<Jeu*>(jeux.elements, jeux.nElements);
		for (Jeu*& jeu : spanJeux) {
			if (jeu == jeuASupprimer) {
				if (jeux.nElements > 1) {
					jeu = spanJeux[jeux.nElements - 1];
				}
				jeux.nElements--;
			}
		}
	}


	static void augmenterCapacite(size_t nouvelleCapacite, ListeJeux& jeux) {
		Jeu** nouveauJeux = new Jeu * [nouvelleCapacite];
		gsl::span<Jeu*> spanJeux = gsl::span<Jeu*>(jeux.elements, jeux.nElements);

		int i = 0;
		for (Jeu*& jeu : spanJeux) {
			nouveauJeux[i++] = jeu;
		}

		delete[] jeux.elements;

		jeux.elements = nouveauJeux;
		jeux.capacite = nouvelleCapacite;
	}


	static gsl::span<Jeu*> span(const ListeJeux& jeux) {
		return gsl::span<Jeu*>(jeux.elements, jeux.nElements);
	}

	gsl::span<Jeu*> span() {
		return ListeJeux::span(*this);
	}


	static void test() {

		// ListeJeux::ajouterJeu //

		// ListeJeux::enleverJeu //

		// ListeJeux::augmenterCapacite //
	}
};