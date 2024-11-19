#pragma once
#include "gsl/gsl_assert"
#include "gsl/pointers"
#include "verification_allocation.hpp"
#include <cassert>


// AJOUT (etudiant) : Classe testable
class Testable {
public:
	virtual void test() = 0;
};



template<typename T> class ListeLiee;
template<typename T> class Iterateur;

template<typename T>
struct Noeud : public Testable
{
	friend class ListeLiee<T>;
	friend class Iterateur<T>;
public:
	//TODO [x]: Constructeur(s).
	Noeud(const T& donnee) : donnee_(donnee) {}


	void test() override {
		Noeud<int> n0(5);

		assert(n0.donnee_ == 5);
		assert(n0.suivant_ == Noeud::PAST_END);

		Noeud<int> n1(10);
		n0.suivant_ = &n1;
		n1.precedent_ = &n0;
		assert(n0.suivant_ == &n1);
		assert(n1.precedent_ == &n0);

		Noeud<int> n2(15);
		n1.suivant_ = &n2;
		n2.precedent_ = &n1;
		assert(n1.suivant_ == &n2);
		assert(n2.precedent_ == &n1);

		cout << "[TEST] Noeud : succes" << endl;
	}


private:
	//TODO [x]: Attributs d'un noeud.
	Noeud* suivant_ = Noeud::PAST_END;
	Noeud* precedent_ = Noeud::PAST_END;
	T donnee_;

	inline static constexpr Noeud* PAST_END = nullptr;
};

template<typename T>
class Iterateur
{
	friend class ListeLiee<T>;
public:
	//TODO [x]: Constructeur(s).
	Iterateur(Noeud<T>* position = Noeud<T>::PAST_END) : position_(position) {}

	void avancer()
	{
		Expects(position_ != Noeud<T>::PAST_END);

		// TODO [x]: Changez la position de l'itérateur pour le noeud suivant
		this->position_ = this->position_->suivant_;
	}
	void reculer()
	{
		//NOTE: On ne demande pas de supporter de reculer à partir de l'itérateur end().
		Expects(position_ != Noeud<T>::PAST_END);

		// TODO [x] : Changez la position de l'itérateur pour le noeud précédent
		this->position_ = this->position_->precedent_;
	}

	Iterateur& operator++() {
		this->avancer();
		return *this;
	}

	Iterateur operator--() {
		this->reculer();
		return *this;
	}

	T& operator*()
	{
		Expects(position_ != Noeud<T>::PAST_END);
		return position_->donnee_;
	}
	//TODO []: Ajouter ce qu'il manque pour que les boucles sur intervalles fonctionnent sur une ListeLiee.
	bool operator==(const Iterateur<T>& it) const = default;

	void test() {
		Noeud<int> n0(5);
		Noeud<int> n1(10);
		Noeud<int> n2(15);

		n0.suivant_ = &n1;
		n1.precedent_ = &n0;
		n1.suivant_ = &n2;
		n2.precedent_ = &n1;

		Iterateur<int> it(&n0);
		assert(*it == 5);
		it.avancer();
		assert(*it == 10);
		it.avancer();
		assert(*it == 15);
		it.reculer();
		assert(*it == 10);

		cout << "[TEST] Iterateur : succes" << endl;
	}
private:
	Noeud<T>* position_;
};

template<typename T>
class ListeLiee
{
	friend class Iterateur<T>;
public:
	using iterator = Iterateur<T>;  // Définit un alias au type, pour que ListeLiee<T>::iterator corresponde au type de son itérateur.

	//TODO: La construction par défaut doit créer une liste vide valide.
	ListeLiee() : tete_(Noeud<T>::PAST_END), queue_(Noeud<T>::PAST_END), taille_(0) {};
	~ListeLiee()
	{
		//TODO: Enlever la tête à répétition jusqu'à ce qu'il ne reste aucun élément.
		// Pour enlever la tête, 
		// 1. La tête doit devenir le suivant de la tête actuelle.
		// 2. Ne pas oublier de désallouer le noeud de l'ancienne tête (si pas fait automatiquement).
		while (tete_ != Noeud<T>::PAST_END) {
			auto temp = tete_;
			tete_ = tete_->suivant_;
			delete temp;
		}
	}

	bool estVide() const { return taille_ == 0; }
	unsigned size() const { return taille_; }
	//NOTE: to_address (C++20) permet que ce même code fonctionne que vous utilisiez des pointeurs bruts ou intelligents (ça prend le pointeur brut associé au pointeur intelligent, s'il est intelligent).
	iterator begin() { return { to_address(tete_) }; }
	iterator end() { return { to_address(queue_->suivant_) }; }

	// Ajoute à la fin de la liste
	// Adapté à partir de l'exemple dans les notes de cours : [1] F.-R. Boyer, M. Bellaïche, S. Kadoury, Complexité et conteneur non contigu. Montreal, QC  : Département de génie informatique et génie logiciel, 2021. [En ligne].
	void push_back(const T& item)
	{
		//TODO: Vous devez créer un nouveau noeud en mémoire.
		//TODO: Si la liste était vide, ce nouveau noeud est la tête et la queue;
		// autrement, ajustez la queue et pointeur(s) adjacent(s) en conséquence.
		Noeud<T>* nouveauNoeud = new Noeud<T>(item);
		if (tete_ == Noeud<T>::PAST_END && queue_ == Noeud<T>::PAST_END && taille_ <= 0)
			tete_ = nouveauNoeud;
		else {
			queue_->suivant_ = nouveauNoeud;
			nouveauNoeud->precedent_ = queue_;
		}
		queue_ = nouveauNoeud;
	}

	// Insère avant la position de l'itérateur.

	iterator insert(iterator it, const T& item)
	{

		//NOTE: Pour simplifier, vous n'avez pas à supporter l'insertion à la fin (avant "past the end"),
		// ni l'insertion au début (avant la tête), dans cette méthode.
		//TODO:
		// 1. Créez un nouveau noeud initialisé avec item.
		// 2. Modifiez les attributs suivant_ et precedent_ du nouveau noeud
		//    afin que le nouveau noeud soit lié au noeud précédent et suivant
		//    à l'endroit où il est inséré selon notre itérateur.
		// 3. Modifiez l'attribut precedent_ du noeud après la position d'insertion
		//    (l'itérateur) afin qu'il pointe vers le noeud créé.
		// 4. Modifiez l'attribut suivant_ du noeud avant la position d'insertion
		//    (précédent de l'itérateur) afin qu'il point vers le noeud créé.
		// 5. Incrémentez la taille de la liste.
		// 6. Retournez un nouvel itérateur initialisé au nouveau noeud.
	}

	// Enlève l'élément à la position it et retourne un itérateur vers le suivant.
	iterator erase(iterator it)
	{
		//TODO: Enlever l'élément à la position de l'itérateur.
		//  1. Le pointeur vers le Noeud à effacer est celui dans l'itérateur.
		//  2. Modifiez l'attribut suivant_ du noeud précédent pour que celui-ci
		//     pointe vers le noeud suivant la position de l'itérateur (voir 1.).
		//  3. Modifiez l'attribut precedent_ du noeud suivant la position de
		//     l'itérateur pour que celui-ci pointe vers le noeud précédent
		//     de la position de l'itérateur (voir 1.).
		//  4. Désallouez le Noeud à effacer (voir 1.).
		//  5. Décrémentez la taille de la liste
		//  6. Retournez un itérateur vers le suivant du Noeud effacé.
		//TODO: On veut supporter d'enlever le premier élément de la liste,
		//  donc en 2. il se peut qu'il n'y ait pas de précédent et alors c'est
		//  la tête de liste qu'il faut ajuster.
		//NOTE: On ne demande pas de supporter d'effacer le dernier élément (c'est similaire au cas pour enlever le premier).
	}

	//private:
	gsl::owner<Noeud<T>*> tete_ = Noeud::PAST_END;  //NOTE: Vous pouvez changer le type si vous voulez.

	Noeud<T>* queue_ = Noeud::PAST_END;
	unsigned taille_ = 0;
};
