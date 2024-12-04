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



void Caisse::retirerArticle(const Article& article) {
	auto it = std::find(articles_.cbegin(), articles_.cend(), article);
	if (it != articles_.cend()){
		articles_.erase(it);
		sousTotal_ -= article.prix;
	}
	caisseModifiee();
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

	caisseModifiee();
}

void Caisse::calculerTaxes() {
	taxes_ = std::accumulate(articles_.cbegin(), articles_.cend(), 0.0, [](double sommeAccumulee, const Article& article) {return sommeAccumulee + (article.taxable ? article.prix * tauxTaxation_ : 0.0); });

}

void Caisse::calculerTotal() {
	total_ = sousTotal_ + taxes_;
}

void Caisse::caisseModifiee() {
	emit articleModifie(articles_);
	emit sousTotalModifie(sousTotal_);

	calculerTaxes();
	emit taxesModifiees(taxes_);

	calculerTotal();
	emit totalModifie(total_);
};

void Caisse::reinitialiserCaisse() {
	this->articles_.clear();
	this->total_ = 0.0;
	this->sousTotal_ = 0.0;
	this->taxes_ = 0.0;
	this->caisseModifiee();
}