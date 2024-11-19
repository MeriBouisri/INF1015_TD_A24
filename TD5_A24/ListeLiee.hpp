/**
* Classes servant à implémenter une liste à liens doubles à partir de noeuds et itérateurs.
* \file   ListeLiee.hpp
* \author Bouisri, Département de génie informatique et génie logiciel et Xa
* \date   19 novembre 2024
* Créé le 5 novembre 2024
*/

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
public:
	//TODO [x]: Constructeur(s).
	Noeud(const T& donnee) : donnee_(donnee) {}


	void test() override {
		/*Noeud<int> n0(5);

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

		cout << "[TEST] Noeud : succes" << endl;*/
	}


private:
	//TODO [x]: Attributs d'un noeud.
	Noeud* suivant_ = Noeud::PASSE_FIN;
	Noeud* precedent_ = Noeud::PASSE_FIN;
	T donnee_;

	inline static constexpr Noeud* PASSE_FIN = nullptr;
	friend class ListeLiee<T>;
	friend class Iterateur<T>;
};

template<typename T>
class Iterateur
{
	friend class ListeLiee<T>;
public:
	//TODO [x]: Constructeur(s).
	Iterateur(Noeud<T>* position = Noeud<T>::PASSE_FIN) : position_(position) {}

	void avancer()
	{
		Expects(position_ != Noeud<T>::PASSE_FIN);

		// TODO [x]: Changez la position de l'itérateur pour le noeud suivant
		this->position_ = this->position_->suivant_;
	}
	void reculer()
	{
		//NOTE: On ne demande pas de supporter de reculer à partir de l'itérateur end().
		Expects(position_ != Noeud<T>::PASSE_FIN);

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
		Expects(position_ != Noeud<T>::PASSE_FIN);
		return position_->donnee_;
	}
	//TODO []: Ajouter ce qu'il manque pour que les boucles sur intervalles fonctionnent sur une ListeLiee.
	bool operator==(const Iterateur<T>& it) const = default;

	void test() {
		/*Noeud<int> n0(5);
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

		cout << "[TEST] Iterateur : succes" << endl;*/
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
	ListeLiee() : tete_(Noeud<T>::PASSE_FIN), queue_(Noeud<T>::PASSE_FIN), taille_(0) {};
	~ListeLiee()
	{
		//TODO: Enlever la tête à répétition jusqu'à ce qu'il ne reste aucun élément.
		// Pour enlever la tête, 
		// 1. La tête doit devenir le suivant de la tête actuelle.
		// 2. Ne pas oublier de désallouer le noeud de l'ancienne tête (si pas fait automatiquement).
		while (tete_ != Noeud<T>::PASSE_FIN) {
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
		if (taille_ <= 0)
			tete_ = nouveauNoeud;
		else {
			queue_->suivant_ = nouveauNoeud;
			nouveauNoeud->precedent_ = queue_;
		}
		queue_ = nouveauNoeud;
		++taille_;
	}


	// Insère avant la position de l'itérateur.
	// Adapté à partir de l'exemple dans les notes de cours : [1] F.-R. Boyer, M. Bellaïche, S. Kadoury, Complexité et conteneur non contigu. Montréal, QC  : Département de génie informatique et génie logiciel, 2021. [En ligne].
	iterator insert(const iterator& it, const T& item) // Enlever le const & si jamais un problème de compatibilité survient (iterator it originalement)
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
		if (it.position_ == Noeud<T>::PASSE_FIN) {
			push_back(item);
			return Iterateur<T>(queue_);
		}

		Noeud<T>* apres = it.position_;
		Noeud<T>* avant = apres->precedent_;

		Noeud<T>* nouveauNoeud = new Noeud<T>(item);
		nouveauNoeud->suivant_ = apres;
		nouveauNoeud->precedent_ = avant;

		apres->precedent_ = nouveauNoeud;
		if (avant == Noeud<T>::PASSE_FIN)
			tete_ = nouveauNoeud;
		else
			avant->suivant_ = nouveauNoeud;

		++taille_;

		return Iterateur<T>(nouveauNoeud);
	}


	// Enlève l'élément à la position it et retourne un itérateur vers le suivant.
	iterator erase(const iterator& it) // Enlever le const & si jamais un problème de compatibilité survient (iterator it originalement)
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

		Noeud<T>* effacer = it.position_;
		Noeud<T>* avant = effacer->precedent_;
		Noeud<T>* apres = effacer->suivant_;

		if (avant != Noeud<T>::PASSE_FIN) {
			avant->suivant_ = apres;
		}
		else {
			tete_ = apres;
		}

		if (apres != Noeud<T>::PASSE_FIN) {
			apres->precedent_ = avant;
		}
		else {
			queue_ = avant;
		}

		delete effacer;

		--taille_;

		return Iterateur<T>(apres);
	}

private:
	gsl::owner<Noeud<T>*> tete_;  //NOTE: Vous pouvez changer le type si vous voulez.

	Noeud<T>* queue_;
	unsigned taille_;
};
