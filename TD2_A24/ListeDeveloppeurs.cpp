#include "ListeDeveloppeurs.hpp"
#include "gsl/span"

ListeDeveloppeurs::ListeDeveloppeurs() {
	nElements_ = 0;
	capacite_ = 0;
	elements_ = new Developpeur * [0];
}

ListeDeveloppeurs::~ListeDeveloppeurs() {

	for (Developpeur* developer : span()) {
		detruireDeveloppeur(developer);
	}

		delete[] elements_;
		elements_ = nullptr;

		std::cout << "Destroyed [ListeDeveloppeurs]" << std::endl;
}


void ListeDeveloppeurs::detruireDeveloppeur(Developpeur* developer)
{
	std::cout << "Destroying... [D�veloppeur, " << developer->getName() << ", " << developer << "]" << std::endl;

	developer->~Developpeur();

	for (Concepteur* c : spanListeConcepteurs(jeu->concepteurs)) {
		ListeJeux::removeGame(jeu, c->jeuxConcus);

		if (!concepteurParticipeJeu(*c))
			detruireConcepteur(c);
	}

	delete[] jeu->concepteurs.elements;
	jeu->concepteurs.elements = nullptr;

	delete jeu;
	jeu = nullptr;

	cout << "Destroyed [ptrJeu=" << jeu << "]" << endl;
}


gsl::span<Developpeur*> ListeDeveloppeurs::span() {
	return gsl::span<Developpeur*>(elements_, nElements_);
}


void ListeDeveloppeurs::afficher() {
	for (Developpeur* developer : span()) {
		developer->printGameList();
	}
}



void ListeDeveloppeurs::increaseCapacity(size_t newCapacity) {
	Developpeur** newDevelopers = new Developpeur * [newCapacity];
	int i = 0;

	for (Developpeur* developer : span()) {
		newDevelopers[i++] = developer;
	}

	delete[] elements_;

	elements_ = newDevelopers;
	capacite_ = newCapacity;
}


void ListeDeveloppeurs::addDeveloper(Developpeur& developer) {
	if (nElements_ >= capacite_) {
		if (capacite_ <= 0) {
			increaseCapacity(1);
		}
		else {
			increaseCapacity(capacite_ * 2);
		}
	}
	elements_[nElements_++] = &developer;
}


void ListeDeveloppeurs::removeDeveloper(Developpeur* developerToDelete) {
	gsl::span<Developpeur*> spanDeveloperList = span();
	for (Developpeur*& developer : spanDeveloperList) {
		if (developer == developerToDelete) {
			developer = spanDeveloperList[nElements_ - 1];
			nElements_--;
		}
	}
}


/**std::size_t nElements_, capacite_;
	Developpeur** elements_;
*/
