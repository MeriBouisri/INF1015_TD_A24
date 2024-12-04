/**
* Modèle pour une caisse enregistreuse
* \file   Caisse.h
* \author Bouisri et Xa
* \date   19 novembre 2024
* Créé le 3 décembre 2024
*/

#pragma once

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QObject>
#include "Article.h"
#include "ExceptionsPersonnalisees.h"
#include <unordered_set>
#pragma pop()

namespace espaceModele {

class Caisse : public QObject {
	Q_OBJECT

public:
	Caisse() = default;

	const std::unordered_set<Article>& getArticles() const { return articles_; }
	double getSousTotal() const { return sousTotal_; }
	double getTaxes() const { return taxes_; }
	double getTotal() const { return total_; }
	void reinitialiserCaisse();

public slots:
	void retirerArticle(const Article& article);
	void ajouterArticle(std::string description, double prix, bool taxable);

signals:
	void articleModifie(const std::unordered_set<Article>& articles);
	void sousTotalModifie(double sousTotal);
	void taxesModifiees(double taxes);
	void totalModifie(double total);

private:
	std::unordered_set<Article> articles_ = {};
	double sousTotal_ = 0.0;
	double taxes_ = 0.0;
	double total_ = 0.0;
	static constexpr auto tauxTaxation_ = 0.14975;

	void calculerTaxes();
	void calculerTotal();
	void caisseModifiee();
};
}
