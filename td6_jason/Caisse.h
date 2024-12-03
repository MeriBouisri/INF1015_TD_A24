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

public slots:

	void retirerArticle(const Article& article);
	void ajouterArticle(std::string description, double prix, bool taxable);

signals:
	void articleModifie();
private:
	std::unordered_set<Article> articles_ = {};
	double sousTotal_ = 0.0;
	static constexpr auto tauxTaxation_ = 0.14975;

	double calculerTotal() const;
};
}
