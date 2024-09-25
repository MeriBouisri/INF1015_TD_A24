#pragma once
#include <cstddef>
#include "Developpeur.hpp"
#include "gsl/span"

class ListeDeveloppeurs
{
	//TODO: En faire une classe qui suit les principes OO.
	//TODO: On veut pouvoir ajouter et enlever un Developpeur* de la liste, avec réallocation dynamique tel que faite pour ListeJeux.
	//NOTE: Le code sera principalement copié de certaines fonctions écrites pour la partie 1, mais mises dans une classe.
private:
	std::size_t nElements_, capacite_;
	Developpeur** elements_;
	gsl::span<Developpeur*> span();
	void detruireDeveloppeur(Developpeur* developer);
public:
	ListeDeveloppeurs();
	~ListeDeveloppeurs();
	void afficher();
	void increaseCapacity(size_t newCapacity);
	void addDeveloper(Developpeur& developer);
	void removeDeveloper(Developpeur* developerToDelete);


/**Classe ListeDeveloppeurs
Le constructeur crée une liste valide contenant aucun élément. Le destructeur libère le tableau dynamique.
La méthode afficher() parcourt le tableau et affiche son contenu en faisant appel à la méthode correspondante
de la classe Developpeur.
La méthode ajouterDeveloppeur ajoute un Developpeur existant (passé par adresse; cette méthode
n’alloue pas de Developpeur) uniquement s’il n’existe pas dans le tableau dynamique. Si la capacité du
tableau est atteinte on augmente la capacité du tableau dynamique (utiliser la même façon que l’allocation
dynamique dans la partie 1 en copiant le code dans une/des méthodes appropriées).
La méthode retirerDeveloppeur retire un Developpeur existant (passé par adresse) du tableau dynamique*/
/**class Developpeur
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
};*/