#include "ListeDeveloppeurs.hpp"
#include "gsl/span"

ListeDeveloppeurs::ListeDeveloppeurs() {
	nElements_ = 0;
	capacite_ = 0;
	developpeurs_ = new Developpeur * [0];
}


ListeDeveloppeurs::~ListeDeveloppeurs() {
	for (Developpeur* developpeur : span()) {
		detruireDeveloppeur(developpeur);
	}

	delete[] developpeurs_;
	developpeurs_ = nullptr;
	std::cout << "Destroyed [ListeDeveloppeurs]" << std::endl;
}


void ListeDeveloppeurs::detruireDeveloppeur(Developpeur* developpeur) {
	std::cout << "Destroying... [Développeur, " << developpeur->obtenirNom() << ", " << developpeur << "]" << std::endl;
	developpeur->~Developpeur();
}


gsl::span<Developpeur*> ListeDeveloppeurs::span() {
	return gsl::span<Developpeur*>(developpeurs_, nElements_);
}


void ListeDeveloppeurs::afficher() {
	for (Developpeur* developpeur : span()) {
		developpeur->afficherJeux();
	}
}


void ListeDeveloppeurs::augmenterCapacite(size_t nouvelleCapacite) {
	Developpeur** newDevelopers = new Developpeur * [nouvelleCapacite];
	int i = 0;

	for (Developpeur* developpeur : span()) {
		newDevelopers[i++] = developpeur;
	}

	delete[] developpeurs_;
	developpeurs_ = newDevelopers;
	capacite_ = nouvelleCapacite;
}


void ListeDeveloppeurs::ajouterDeveloppeur(Developpeur& developpeur) {
	if (nElements_ >= capacite_) {
		if (capacite_ <= 0) {
			augmenterCapacite(1);
		}
		else {
			augmenterCapacite(capacite_ * 2);
		}
	}
	developpeurs_[nElements_++] = &developpeur;
}


void ListeDeveloppeurs::eneleverDeveloppeur(Developpeur* developpeurASupprimer) {
	gsl::span<Developpeur*> spanDeveloperList = span();
	for (Developpeur*& developpeur : spanDeveloperList) {
		if (developpeur == developpeurASupprimer) {
			if (nElements_ > 1) {
				developpeur = spanDeveloperList[nElements_ - 1];
			}
			nElements_--;
		}
	}
}


/**std::size_t nElements_, capacite_;
	Developpeur** elements_;
*/
