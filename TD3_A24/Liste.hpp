/**
* Classe Liste generique
* \file   Liste.hpp
* \author Bouisri et Xa
* \date   21 octobre 2024
* Cree le 8 octobre 2024
*/

#include "cppitertools/range.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <gsl/span>
#include <memory>
#include "verification_allocation.hpp"

using std::shared_ptr;
using std::unique_ptr;
using std::make_unique;
using std::size_t;
using std::function;

#pragma once

template <typename T> class Liste {
public:
	Liste() = default;

	Liste(const Liste<T>& autre) : capacite_(autre.capacite_), nElements_(autre.nElements_){
		elements_ = make_unique<shared_ptr<T>[]>(capacite_);

		for (size_t i : iter::range(nElements_)) 
			elements_[i] = autre.elements_[i];
	}


	void ajouter(shared_ptr<T>&& nouvelElement) {
		if (nElements_ == capacite_)
			changerCapacite(std::max(size_t(1), capacite_ * 2));
		elements_[nElements_++] = move(nouvelElement);
	}


	void retirer(const shared_ptr<T> elementARetirer) {
		for (shared_ptr<T>& element : enSpan()) {
			if (element == elementARetirer) {
				if (nElements_ > 1) {
					element = elements_[nElements_ - 1];
				}
				nElements_--;
			}
		}
	}


	//void afficher() const {
	//	for (const auto& element : enSpan()) {
	//		element->afficher();
	//	}
	//}


	void changerCapacite(std::size_t nouvelleCapacite) {
		// Copie du code de changerTailleListeJeux, ajust� pour la classe.
		assert(nouvelleCapacite >= nElements_); // On ne demande pas de supporter les r�ductions de nombre d'�l�ments.
		auto nouvelleListe = make_unique<shared_ptr<T>[]>(nouvelleCapacite);
		// Pas n�cessaire de tester si liste.elements est nullptr puisque si c'est le cas, nElements est n�cessairement 0.
		for (size_t i : iter::range(nElements_)) {
			nouvelleListe[i] = move(elements_[i]);
		}

		elements_ = move(nouvelleListe);
		capacite_ = nouvelleCapacite;
	}  // Pas dit si �a doit �tre public ou non.


	shared_ptr<T> trouver(const function<bool(const shared_ptr<T>&)>& critere) const {
		for (const shared_ptr<T>& element : enSpan()) {
			if (critere(element)) {
				return element;
			}
		}
		return nullptr;
	}


	gsl::span<shared_ptr<T>> enSpan() const {
		return gsl::span<shared_ptr<T>>(elements_.get(), nElements_);
	}

	void setNElements(size_t nElements) {
		nElements_ = nElements;
	}


	size_t getNElements() const {
		return nElements_;
	}


	void setElements(unique_ptr<shared_ptr<T>[]> elements) {
		elements_ = move(elements);
	}

	shared_ptr<T>& operator[](size_t index) const {
		if (index >= nElements_) 
			throw std::out_of_range("Index hors limites");
		
		return elements_[index];
	}

private:
	size_t capacite_ = 0, nElements_ = 0;	// Pas besoin de d�clarer explicitement un corps de constructeur avec ces initialisations.
	unique_ptr<shared_ptr<T>[]> elements_ = {};
};