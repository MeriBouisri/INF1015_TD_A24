/**
* Modèle pour une caisse enregistreuse
* \file   Caisse.cpp
* \author Bouisri et Xa
* \date   19 novembre 2024
* Créé le 3 décembre 2024
*/

#include "Caisse.h"
using namespace espaceModele;

// slots:

void Caisse::changerValeur(int valeur) {
	if (valeur != valeur_) {
		valeur_ = valeur;
		emit valeurChangee(valeur_);
	}
}
void Caisse::effacer() {
	operation_ = egal; changerValeur(0);
}
void Caisse::ajouterChiffre(int chiffre) {
	if (estResultat_) {
		valeur_ = 0;
		estResultat_ = false;
	}
	changerValeur(valeur_ * 10 + chiffre);
}

void Caisse::changerOperation(const std::function<int(int, int)>& operation) {
	if (!estResultat_)
		effectuerOperation();
	operation_ = operation;
}

void Caisse::operationPlus() { changerOperation(plus); }
void Caisse::operationMoins() { changerOperation(moins); }
void Caisse::operationEgal() { changerOperation(egal); }

void Caisse::effectuerOperation() {
	resultatPrecedent_ = operation_(resultatPrecedent_, valeur_);
	estResultat_ = true;
	changerValeur(resultatPrecedent_);
}

double Caisse::calculerTotal() const {
	return std::accumulate(articles_.cbegin(), articles_.cend(), sousTotal_, [](double sommeAccumulee, const Article& article) {return sommeAccumulee + (article.taxable ? article.prix * tauxTaxation_ : 0.0); });
}

void Caisse::retirerArticle(const Article& article) {
	auto it = std::find(articles_.cbegin(), articles_.cend(), article);
	if (it != articles_.cend()){
		articles_.erase(it);
		sousTotal_ -= article.prix;
	}
}

void Caisse::ajouterArticle(std::string description, double prix, bool taxable) {
	static constexpr auto epsilon = 1e-6;
	auto estDescriptionVide = description.empty();
	auto estPrixNul = std::abs(prix) < epsilon;

	if (estDescriptionVide && estPrixNul) {
		throw std::invalid_argument("Erreur : Le nom de l'article ne peut pas être vide et le prix ne peut pas être zéro.");
	} else if (estDescriptionVide){
		throw ExceptionDescriptionVide("Erreur : Le nom de l'article ne peut pas être vide.");
	}
	else if (estPrixNul) {
		throw ExceptionPrixNul("Erreur : Le prix de l'article ne peut pas être zéro.");
	}

	articles_.insert(std::move(Article(description, prix, taxable)));
	sousTotal_ += prix;
}

// Fonctions pour l'opération:
// (on aurait pu à la place mettre des lambdas dans operationPlus() ...)
int Caisse::plus(int x, int y) { return x + y; }
int Caisse::moins(int x, int y) { return x - y; }
int Caisse::egal(int, int y) { return y; }
