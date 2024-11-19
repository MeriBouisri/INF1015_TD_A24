/**
* Interface Affichable pour les classes affichables
* \file   Affichable.hpp
* \author Département de génie informatique et génie logiciel
* \date   19 novembre 2024
* Créé le 5 novembre 2024
*/

#pragma once
#include <array>
#include <iostream>
using namespace std;

enum class Theme { sombre, clair };
class Affichable
{
public:
	virtual ~Affichable() = default;  // Important!  Toute classe polymorphe doit avoir un destructeur virtuel, sinon la destruction par la classe de base est "undefined behavior".
	virtual void afficher(ostream&) const = 0;
	virtual void changerCouleur(ostream&, Theme) const = 0;

	enum class Couleur { noir, rouge, vert, jaune, bleu, magenta, cyan, blancGris, noirGris, rougeIntense, vertIntense, jauneIntense, bleuIntense, magentaIntense, cyanIntense, blancIntense };
	static void changerCouleurTexteFond(ostream& os, Couleur texte, Couleur fond) {  // Noter que cette méthode est statique et n'est donc pas une méthode de l'objet, donc généralement accepté comme pouvant être dans une interface; sinon simplement sortir la fonction de la classe.
		static const array<int, 16> enumCouleurVersAnsi = { 30,31,32,33,34,35,36,37,90,91,92,93,94,95,96,97 };
		auto envoyerCodeCouleur = [&](int codeCouleurAnsi) { os << "\033[" << codeCouleurAnsi << "m"; };
		envoyerCodeCouleur(0);
		envoyerCodeCouleur(enumCouleurVersAnsi[int(texte)]);
		envoyerCodeCouleur(enumCouleurVersAnsi[int(fond)] + 10);
	}
};