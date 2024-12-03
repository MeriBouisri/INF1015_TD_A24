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

	int obtenirValeur() { return valeur_; }

public slots:
	void changerValeur(int valeur);
	void effacer();
	void ajouterChiffre(int chiffre);
	void changerOperation(const std::function<int(int, int)>& operation);
	void operationPlus();
	void operationMoins();
	void operationEgal();
	void effectuerOperation();

	double calculerTotal() const;
	void retirerArticle(const Article& article);
	void ajouterArticle(std::string description, double prix, bool taxable);

signals:
	void valeurChangee(int valeur);

private:
	static int plus(int x, int y);
	static int moins(int x, int y);
	static int egal(int, int y);

	bool estResultat_ = true;
	int valeur_ = 0;
	int resultatPrecedent_ = 0;
	std::function<int(int, int)> operation_ = egal;

	std::unordered_set<Article> articles_ = {};
	double sousTotal_ = 0.0;
	static constexpr auto tauxTaxation_ = 0.14975;
};
}
