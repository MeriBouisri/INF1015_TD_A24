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
#pragma pop()
#include <functional>
#include <unordered_set>

namespace espaceModele {
	struct Article {
		std::string description;
		double price;
		bool taxable;
	};
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

	std::vector<Article> articles_ = {};
	double sousTotal_ = 0.0;
	static constexpr auto tauxTaxation_ = 0.14975;
};
}
