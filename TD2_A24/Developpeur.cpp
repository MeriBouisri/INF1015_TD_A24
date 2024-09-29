/**
* Impl�mentation de la classe Developpeur, repr�sentant un d�veloppeur de jeu vid�o
* \file   Developpeur.cpp
* \author Bouisri et Xa
* \date   29 septembre 2024
* Cr�� le 17 septembre 2024
*/

#include "Developpeur.hpp"

using namespace std;

Developpeur::Developpeur(string nom) {
	paireNomJeux_ = pair<string, ListeJeux>(nom, { 0, 0, new Jeu * [0] });
}


Developpeur::~Developpeur() {
	for (Jeu* jeu : ListeJeux::span(paireNomJeux_.second))
		ListeJeux::enleverJeu(jeu, paireNomJeux_.second);

	delete[] paireNomJeux_.second.elements;
	paireNomJeux_.second.elements = nullptr;

	cout << "Developpeur detruit : [" << paireNomJeux_.first << ", " << paireNomJeux_.second.elements << "]" << endl;
}


string Developpeur::obtenirNom() const {
	return paireNomJeux_.first;
}


ListeJeux Developpeur::obtenirJeux() const {
	return paireNomJeux_.second;
}


void Developpeur::viderJeux() {
	for (Jeu* jeu : ListeJeux::span(paireNomJeux_.second))
		ListeJeux::enleverJeu(jeu, paireNomJeux_.second);

	delete[] paireNomJeux_.second.elements;
	paireNomJeux_.second.elements = new Jeu * [0];
	paireNomJeux_.second.nElements = 0;
	paireNomJeux_.second.capacite = 0;
}


int Developpeur::compterJeux(ListeJeux& jeux) const {
	int compte = 0;
	for (Jeu* jeu : ListeJeux::span(jeux))
		if (jeu->developpeur == paireNomJeux_.first)
			compte++;

	return compte;
}


void Developpeur::actualiserJeux(ListeJeux& jeux) {
	// Éviter de dupliquer les jeux
	viderJeux();
	ListeJeux::augmenterCapacite(
		this->compterJeux(jeux),
		paireNomJeux_.second);

	for (Jeu* jeu : ListeJeux::span(jeux))
		if (jeu->developpeur == obtenirNom())
			ListeJeux::ajouterJeu(*jeu, paireNomJeux_.second);
}

void Developpeur::afficherJeux() {

	cout << "[INFO][Developpeur::afficherJeux()] Jeux de [developpeur.nom=" << this->obtenirNom() << "] :" << endl;

	// Iterate over the list of games associated with the developer and display each one
	for (Jeu* jeu : ListeJeux::span(paireNomJeux_.second)) {
		cout << "\t[jeu->titre=" << jeu->titre << ", jeu->anneeSortie=" << jeu->anneeSortie<< "]" << endl;
	}

	if (paireNomJeux_.second.nElements == 0) {
		cout << "[INFO][Developpeur::afficherJeux] Aucun jeu pour ce developpeur." << endl;
	}
	
}


bool Developpeur::testActualiserJeux() {
	bool success = false;

	Developpeur* developpeur = new Developpeur("dev01");
	 

	cout << "[TEST][Developpeur::testActualiserJeux] Initialisation : [developpeur.nom=" << developpeur->obtenirNom() << ", " << developpeur << "]" << endl;
	cout << "[TEST][Developpeur::testActualiserJeux] Test pret" << endl;

	ListeJeux jeux = { 0, 0, new Jeu * [2] };

	Jeu jeu1 = { "jeu1", 2020, "dev01" };
	Jeu jeu2 = { "jeu2", 2020, "dev01" };

	ListeJeux::ajouterJeu(jeu1, jeux);
	ListeJeux::ajouterJeu(jeu2, jeux);

	developpeur->actualiserJeux(jeux);

	// Test 1/4
	success = (developpeur->obtenirJeux().nElements == 2)
		&& (int(developpeur->obtenirJeux().capacite) == developpeur->compterJeux(jeux))
		&& (developpeur->obtenirJeux().elements[0]->titre == string("jeu1"))
		&& (developpeur->obtenirJeux().elements[1]->titre == "jeu2");


	cout << "[TEST][Developpeur::testActualiserJeux] Liberation de memoire : [jeux.elements=" << jeux.elements << "]" << endl;

	delete[] jeux.elements;
	delete developpeur;

	cout << "[TEST][Developpeur::testActualiserJeux] 4/4 tests finis" << endl;


	if (success)
		cout << "[SUCCES][Developpeur::testActualiserJeux] Tests reussis" << endl;

	return success;
}

bool Developpeur::testCompterJeux() {
	cout << "\n[TEST][Developpeur::testCompterJeux] Debut du test" << endl;
	bool success = false;

	Developpeur* dev01 = new Developpeur("dev01");
	cout << "[TEST][Developpeur::testCompterJeux] Initialisation : [dev01.nom=" << dev01->obtenirNom() << ", " << dev01 << "]" << endl;

	Developpeur* dev02 = new Developpeur("dev02");
	cout << "[TEST][Developpeur::testCompterJeux] Initialisation : [dev02.nom=" << dev02->obtenirNom() << ", " << dev02 << "]" << endl;

	cout << "[TEST][Developpeur::testCompterJeux] Test pret" << endl;

	ListeJeux jeux = { 0, 0, new Jeu * [0] };

	Jeu jeu01 = { "jeu01", 2021, "dev01" };
	Jeu jeu02 = { "jeu02", 2022, "dev02" };
	Jeu jeu03 = { "jeu03", 2023, "dev02" };

	ListeJeux::ajouterJeu(jeu01, jeux);
	ListeJeux::ajouterJeu(jeu02, jeux);
	ListeJeux::ajouterJeu(jeu03, jeux);

	// Test 1/2
	if (dev01->compterJeux(jeux) != 1)
		cout << "[ECHEC][Developpeur::testCompterJeux] developpeur.compterJeux(jeux) : [attendu=1, actuel=" << dev01->compterJeux(jeux) << "] 1/2" << endl;

	// Test 2/2
	else if (dev02->compterJeux(jeux) != 2)
		cout << "[ECHEC][Developpeur::testCompterJeux] developpeur.compterJeux(jeux) : [attendu=2, actuel=" << dev02->compterJeux(jeux) << "] 2/2" << endl;

	else
		success = true;

	cout << "[TEST][Developpeur::testCompterJeux] Liberation de memoire : [jeux.elements=" << jeux.elements << "]" << endl;

	delete[] jeux.elements;
	jeux.elements = nullptr;

	delete dev01;
	dev01 = nullptr;

	delete dev02;
	dev02 = nullptr;

	cout << "[TEST][Developpeur::testCompterJeux] 2/2 tests finis\n\n";

	if (success)
		cout << "[SUCCES][Developpeur::testCompterJeux] Tests reussis" << endl;

	return success;
}

bool Developpeur::testViderJeux() {
	cout << "\n[TEST][Developpeur::testViderJeux] Debut du test" << endl;
	bool success = false;

	Developpeur* dev01 = new Developpeur("dev01");
	cout << "[TEST][Developpeur::testViderJeux] Initialisation : [dev01.nom=" << dev01->obtenirNom() << ", " << dev01 << "]" << endl;

	cout << "[TEST][Developpeur::testViderJeux] Test pret" << endl;

	ListeJeux jeux = { 0, 0, new Jeu * [2] };

	Jeu jeu01 = { "jeu01", 2021, "dev01" };
	Jeu jeu02 = { "jeu02", 2022, "dev01" };

	ListeJeux::ajouterJeu(jeu01, jeux);
	ListeJeux::ajouterJeu(jeu02, jeux);

	dev01->actualiserJeux(jeux);

	success = dev01->obtenirJeux().nElements == 2
		&& dev01->obtenirJeux().capacite == 2
		&& dev01->obtenirJeux().elements[0]->titre == "jeu01"
		&& dev01->obtenirJeux().elements[1]->titre == "jeu02";
	
	if (success)
		dev01->viderJeux();


	success = dev01->obtenirJeux().nElements == 0
		&& dev01->obtenirJeux().capacite == 0
		&& dev01->compterJeux(dev01->paireNomJeux_.second) == 0;



	cout << "[TEST][Developpeur::testViderJeux] Liberation de memoire : [jeux.elements=" << jeux.elements << "]" << endl;

	delete[] jeux.elements;
	jeux.elements = nullptr;

	delete dev01;
	dev01 = nullptr;

	cout << "[TEST][Developpeur::testViderJeux] 8/8 tests finis" << endl;

	if (success)
		cout << "[SUCCES][Developpeur::testViderJeux] Tests reussis" << endl;

	return success;
}

bool Developpeur::testObtenirNom() {
	cout << "\n[TEST][Developpeur::testObtenirNom] Debut du test" << endl;
	bool success = false;

	string nom = "dev01";

	Developpeur* dev01 = new Developpeur(nom);
	cout << "[TEST][Developpeur::testObtenirNom] Initialisation : [dev01.nom=" << dev01->obtenirNom() << ", " << dev01 << "]" << endl;

	cout << "[TEST][Developpeur::testObtenirNom] Test pret" << endl;

	success = dev01->obtenirNom() == nom;

	delete dev01;
	dev01 = nullptr;

	cout << "[TEST][Developpeur::testObtenirNom] 1/1 tests finis\n\n";

	if (success)
		cout << "[SUCCES][Developpeur::testObtenirNom] Tests reussis "<< endl;

	return success;
}

bool Developpeur::testAfficherJeux() {
	bool success = false;


	ListeJeux jeux = { 0, 0, new Jeu * [2] };

	Developpeur* dev = new Developpeur("dev");

	Jeu jeu01 = { "jeu01", 2021, "dev" };
	Jeu jeu02 = { "jeu02", 2022, "dev" };

	ListeJeux::ajouterJeu(jeu01, jeux);
	ListeJeux::ajouterJeu(jeu02, jeux);

	
	dev->actualiserJeux(jeux);


	cout << "[TEST][Developpeur::testAfficherJeux] Initialisation : [dev01.nom=" << dev->obtenirNom() << ", " << dev << "]" << endl;

	cout << "[TEST][Developpeur::testAfficherJeux] Test pret" << endl;

	dev->afficherJeux();


	delete dev;
	dev = nullptr;

	delete[] jeux.elements;
	jeux.elements = nullptr;

	cout << "[TEST][Developpeur::testObtenirNom] 1/1 tests finis\n\n";

	success = true;

	if (success)
		cout << "[SUCCES][Developpeur::testObtenirNom] Tests reussis " << endl;

	return success;
}




bool Developpeur::testDeveloppeur() {

	bool success = Developpeur::testActualiserJeux()
		&& Developpeur::testCompterJeux()
		&& Developpeur::testViderJeux()
		&& Developpeur::testObtenirNom()
		&& Developpeur::testAfficherJeux();

	if (success)
		cout << "\n[SUCCES][Developpeur::testDeveloppeur] Classe Developpeur passe tous les tests\n" << endl;

	return success;
}