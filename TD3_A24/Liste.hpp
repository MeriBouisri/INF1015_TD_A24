template <typename T>
class Liste {
public:
	Liste() = default;


	void ajouter(const shared_ptr<T>& nouvelElement) {
		if (nElements_ == capacite_)
			changerCapacite(max(size_t(1), capacite_ * 2));
		elements_[nElements_++] = nouvelElement;
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


	void afficher() const {
		for (const auto& element : enSpan()) {
			element->afficher();
		}
	}


private:
	size_t capacite_ = 0, nElements = 0;	// Pas besoin de déclarer explicitement un corps de constructeur avec ces initialisations.
	unique_ptr<shared_ptr<T>[]> elements_ = nullptr;

	//TODO: En faire une classe qui suit les principes OO.
	//TODO: On veut pouvoir ajouter et enlever un Developpeur* de la liste, avec réallocation dynamique tel que faite pour ListeJeux.
	//NOTE: Le code sera principalement copié de certaines fonctions écrites pour la partie 1, mais mises dans une classe.

	void changerCapacite(std::size_t nouvelleCapacite) {
		// Copie du code de changerTailleListeJeux, ajusté pour la classe.
		assert(nouvelleCapacite >= nElements_); // On ne demande pas de supporter les réductions de nombre d'éléments.
		auto nouvelleListe = make_unique<shared_ptr<T>[]>(nouvelleCapacite);
		// Pas nécessaire de tester si liste.elements est nullptr puisque si c'est le cas, nElements est nécessairement 0.
		for (size_t i : iter::range(nElements_)) {
			nouvelleListe[i] = move(elements_[i]);
		}

		elements_ = move(nouvelleListe);
		capacite_ = nouvelleCapacite;
	}  // Pas dit si ça doit être public ou non.
	gsl::span<shared_ptr<T>> enSpan() const { return { elements_, nElements_ }; }  // Pourrait être public.
};