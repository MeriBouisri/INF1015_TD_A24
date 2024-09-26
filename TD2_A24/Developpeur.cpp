#include "Developpeur.hpp"

Developpeur::Developpeur(std::string nom) {
	paireNomJeux_ = std::pair<std::string, ListeJeux>(nom, { 0, 0, new Jeu * [0] });
}

Developpeur::~Developpeur() {
	for (Jeu* jeu : ListeJeux::span(paireNomJeux_.second))
		ListeJeux::eneleverJeu(jeu, paireNomJeux_.second);

	delete[] paireNomJeux_.second.elements;
	paireNomJeux_.second.elements = nullptr;

	std::cout << "Developpeur detruit : [" << paireNomJeux_.first << ", " << paireNomJeux_.second.elements << "]" << std::endl;
}

std::string Developpeur::obtenirNom() const {
	return paireNomJeux_.first;
}

ListeJeux Developpeur::obtenirJeux() const {
	return paireNomJeux_.second;
}

void Developpeur::viderJeux() {
	for (Jeu* jeu : ListeJeux::span(paireNomJeux_.second))
		ListeJeux::eneleverJeu(jeu, paireNomJeux_.second);

	delete[] paireNomJeux_.second.elements;
	paireNomJeux_.second.elements = new Jeu * [0];
	paireNomJeux_.second.nElements = 0;
	paireNomJeux_.second.capacite = 0;
}


int Developpeur::compterJeux(ListeJeux& jeux) const {
	int count = 0;
	for (Jeu* jeu : ListeJeux::span(jeux))
		if (jeu->developpeur == paireNomJeux_.first)
			count++;

	return count;
}

void Developpeur::mettreAJourJeux(ListeJeux& jeux) {
	// EViter de dupliquer les jeux
	viderJeux();

	for (Jeu* jeu : ListeJeux::span(jeux))
		if (jeu->developpeur == obtenirNom())
			ListeJeux::ajouterJeu(*jeu, paireNomJeux_.second);
}

void Developpeur::afficherJeux() const {
	std::cout << "Developpeur : " << obtenirNom() << std::endl;

	for (Jeu* jeu : ListeJeux::span(obtenirJeux()))
		std::cout << "\t" << jeu->titre << std::endl;
}




void Developpeur::test() {
	Developpeur* dev = new Developpeur("dev01");

	std::cout << "Developpeur created : [dev.nom=" << dev-> obtenirNom() << ", " << dev << "]" << std::endl;

	ListeJeux jeux = { 0, 0, new Jeu * [3] };

	Jeu jeu1 = { "jeu1", 2020, "dev01" };
	Jeu jeu2 = { "jeu2", 2020, "dev01" };
	Jeu jeu3 = { "jeu3", 2020, "dev02" };

	ListeJeux::ajouterJeu(jeu1, jeux);
	ListeJeux::ajouterJeu(jeu2, jeux);
	ListeJeux::ajouterJeu(jeu3, jeux);

	dev->mettreAJourJeux(jeux);

	dev->afficherJeux();

	delete[] jeux.elements;
	delete dev;
}