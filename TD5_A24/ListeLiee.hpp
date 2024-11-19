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



template<typename T> class ListeLiee;
template<typename T> class Iterateur;

template<typename T>
struct Noeud
{
public:
	Noeud(const T& donnee) : donnee_(donnee), suivant_(passeFin), precedent_(passeFin) {}


private:
	Noeud* suivant_;
	Noeud* precedent_;
	T donnee_;

	inline static constexpr Noeud* passeFin = nullptr;
	friend class ListeLiee<T>;
	friend class Iterateur<T>;
};

template<typename T>
class Iterateur
{
	friend class ListeLiee<T>;
public:
	Iterateur(Noeud<T>* position = Noeud<T>::passeFin) : position_(position) {}

	void avancer()
	{
		Expects(position_ != Noeud<T>::passeFin);

		this->position_ = this->position_->suivant_;
	}
	void reculer()
	{
		//NOTE: On ne demande pas de supporter de reculer à partir de l'itérateur end().
		Expects(position_ != Noeud<T>::passeFin);

		this->position_ = this->position_->precedent_;
	}

	Iterateur& operator++() {
		this->avancer();
		return *this;
	}

	Iterateur& operator--() {
		this->reculer();
		return *this;
	}

	T& operator*()
	{
		Expects(position_ != Noeud<T>::passeFin);
		return position_->donnee_;
	}
	bool operator==(const Iterateur<T>& it) const = default;

private:
	Noeud<T>* position_;
};

template<typename T>
class ListeLiee
{
	friend class Iterateur<T>;
public:
	using iterator = Iterateur<T>;  // Définit un alias au type, pour que ListeLiee<T>::iterator corresponde au type de son itérateur.

	ListeLiee() : tete_(Noeud<T>::passeFin), queue_(Noeud<T>::passeFin), taille_(0) {};
	~ListeLiee()
	{
		while (tete_ != Noeud<T>::passeFin) {
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
		if (it.position_ == Noeud<T>::passeFin) {
			push_back(item);
			return Iterateur<T>(queue_);
		}

		Noeud<T>* apres = it.position_;
		Noeud<T>* avant = apres->precedent_;

		Noeud<T>* nouveauNoeud = new Noeud<T>(item);
		nouveauNoeud->suivant_ = apres;
		nouveauNoeud->precedent_ = avant;

		apres->precedent_ = nouveauNoeud;
		if (avant == Noeud<T>::passeFin)
			tete_ = nouveauNoeud;
		else
			avant->suivant_ = nouveauNoeud;

		++taille_;

		return Iterateur<T>(nouveauNoeud);
	}


	// Enlève l'élément à la position it et retourne un itérateur vers le suivant.
	iterator erase(const iterator& it) // Enlever le const & si jamais un problème de compatibilité survient (iterator it originalement)
	{
		//NOTE: On ne demande pas de supporter d'effacer le dernier élément (c'est similaire au cas pour enlever le premier).

		Noeud<T>* effacer = it.position_;
		Noeud<T>* avant = effacer->precedent_;
		Noeud<T>* apres = effacer->suivant_;

		if (avant != Noeud<T>::passeFin) {
			avant->suivant_ = apres;
		}
		else {
			tete_ = apres;
		}

		if (apres != Noeud<T>::passeFin) {
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
