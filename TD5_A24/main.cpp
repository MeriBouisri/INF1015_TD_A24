/**
* Utilisation de conteneurs, algorithmes et itérateurs pour manipuler des personnages de jeux vidéos
* \file   main.cpp
* \author Bouisri, Département de génie informatique et génie logiciel et Xa
* \date   19 novembre 2024
* Créé le 5 novembre 2024
*/

#include "bibliotheque_cours.hpp"
#include "cppitertools/range.hpp"
#include "Heros.hpp"
#include "lectureBinaire.hpp"
#include "lireVectorDuFichier.hpp"
#include "ListeLiee.hpp"
#include "Personnage.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"
#include <cassert>
#include <fstream>
#include <functional>
#include <memory>
#include <set>
#include <sstream>
#include <vector>

using namespace std;
using namespace iter;

ifstream ouvrirFichierBinaire(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	return fichier;
}

void testsPourCouvertureLectureBinaire()
{
	istringstream iss("\xA0\x12\xA1\x21\x43\xA2\x98\xBA\xDC\xFE");
	assert(lireUintTailleVariable(iss) == 0x12);
	assert(lireUintTailleVariable(iss) == 0x4321);
	assert(lireUintTailleVariable(iss) == 0xFEDCBA98);
}


// versReferenceAffichable permet d'avoir une référence à l'affichable, que le paramètre soit un
// unique_ptr ou une référence.  On aurait pu faire un template plus générique pour const/non const, et
// même utiliser un concept, mais ce n'est pas nécessaire pour que ça fonctionne.
// lireFichier aurait aussi pu retourner un vector de unique_ptr pour ne pas avoir besoin de
// versReferenceAffichable pour supporter à la fois les références et les unique_ptr.
const Affichable& versReferenceAffichable(const Affichable& p) { return p; }
template <typename T>
const Affichable& versReferenceAffichable(const unique_ptr<T>& p) { return *p; }


// Trait de separation
static const string trait =
"═════════════════════════════════════════════════════════════════════════";

// On ne demande pas particulièrement la surcharge de << dans ce TD.
template <typename T>
void afficherAffichables(const vector<T>& affichables, Theme theme)
{
	static const string separateurElements = "\033[33m" + trait + "\n";
	Affichable::changerCouleurTexteFond(cout, Affichable::Couleur::blancGris, (theme == Theme::clair) ? Affichable::Couleur::blancIntense : Affichable::Couleur::noir);

	for (auto&& a : affichables) {
		cout << separateurElements;
		auto& x = versReferenceAffichable(a);
		x.changerCouleur(cout, theme);
		x.afficher(cout);
	}
}

// Permet d'avoir une référence non-const à un objet temporaire.
template <typename T> T& temporaireModifiable(T&& objet) { return objet; }

template <typename T>
vector<T> lireVectorDuFichier(const string& nomFichier)
{
	return lireVectorDuFichier<T>(temporaireModifiable(ouvrirFichierBinaire(nomFichier)));
}

template <typename T>
ListeLiee<T>::iterator trouverParNom(ListeLiee<T>& liste, const string& nom)
{
	//? Quand on accède à un membre dans un type qui n'est pas encore connu (ici T n'est pas connu donc
	// ListeLiee<T> n'est pas connu non plus) lors de l'analyse syntaxique du programme, dans le cas
	// général il ne peut pas savoir si ce membre est un type.  Pour cette raison on doit ajouter le mot
	// typename devant pour lui dire.
	typename ListeLiee<T>::iterator fin = liste.end();
	for (typename ListeLiee<T>::iterator pos = liste.begin(); pos != fin; pos.avancer()) {
		if ((*pos).getNom() == nom)
			return pos;
	}
	return fin;
}

void testAll() {
	Noeud<int> n0(5);
	n0.test();

	Iterateur<int> it(&n0);
	it.test();


}

int main()
{

#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

	testsPourCouvertureLectureBinaire();

	static const string separateurSections = "\033[95m" + trait + "\n";

	//{ Solutionnaire du TD4:
	vector<Heros> heros = lireVectorDuFichier<Heros>("heros.bin");
	vector<Vilain> vilains = lireVectorDuFichier<Vilain>("vilains.bin");
	vector<unique_ptr<Personnage>> peronnages;  // Doit être des pointeurs pour le polymorphisme,
	//l'énoncé ne force pas les unique_ptr.

#if 1 //TODO: Vous n'avez pas à conserver ces affichages pour le TD5, ils sont pour le solutionnaire du
	//TD4:
	cout << separateurSections << "Heros:" << endl;
	afficherAffichables(heros, Theme::sombre);

	cout << separateurSections << "Vilains:" << endl;
	afficherAffichables(vilains, Theme::sombre);

	for (auto& h : heros)
		peronnages.push_back(make_unique<Heros>(h));

	for (auto& v : vilains)
		peronnages.push_back(make_unique<Vilain>(v));

	peronnages.push_back(make_unique<VilainHeros>(vilains[1], heros[2]));

	cout << separateurSections << "Personnages:" << endl;
	afficherAffichables(peronnages, Theme::sombre);

	cout << separateurSections << "Affichage avec un autre thème de couleurs:" << endl;
	afficherAffichables(peronnages, Theme::clair);

	Affichable::changerCouleurTexteFond(cout, Affichable::Couleur::blancGris, Affichable::Couleur::noir);
#endif
	//}

	//testAll();


	//TODO: Transférez les héros du vecteur heros dans une ListeLiee.
	// Transfert des héros du vecteur heros dans une ListeLiee
	ListeLiee<Heros> listeHeros{};
	for (const auto& h : heros)
		listeHeros.push_back(h);

	//TODO: Créez un itérateur sur la liste liée à la position du héros Alucard.  Servez-vous de la
	// fonction trouverParNom définie plus haut.
	// Création d'un itérateur de la liste liée à la position du héros Alucard
	auto it = trouverParNom(listeHeros, "Alucard");

	//TODO: Servez-vous de l'itérateur créé précédemment pour trouver l'héroine Aya Brea, en sachant
	// qu'elle se trouve plus loin dans la liste, en itérant sur les éléments.
	// Recherche de la héroine Aya Brea en itérant sur les éléments à partir d'un itérateur
	for (it; it != listeHeros.end(); ++it) {
		if ((*it).getNom() == "Aya Brea") {
			break;
		}
	}
	cout << trait << "\n";


	//TODO: Ajouter un hero bidon à la liste avant Aya Brea en vous servant de l'itérateur.
	// Ajout d'un héros à la liste avant Aya Brea avec un itérateur.
	cout << "Taille de la liste de héros avant l'insertion : " << listeHeros.size() << "\n";
	it = listeHeros.insert(it, Heros("LeBron James", "NBA ShootOut 2004", "Stephen Curry"));
	cout << trait << "\n";


	//TODO: Assurez-vous que la taille de la liste est correcte après l'ajout.
	// Vérification de la taille de la liste après l'ajout.
	cout << "Taille de la liste de héros après l'insertion de LeBron James : " << listeHeros.size()
		<< "\n";
	cout << trait << "\n";
	(*it).afficher(cout);
	cout << trait << "\n";


	//TODO: Reculez votre itérateur jusqu'au héros Mario et effacez-le en utilisant l'itérateur, puis
	// affichez le héros suivant dans la liste (devrait êter "Naked Snake/John").
	// Recul de l'itérateur jusqu'à Mario et retrait de Mario en utilisant l'itérateur et affichage du
	// héros suivant dans la liste.
	for (it; it != listeHeros.begin(); --it) {
		if ((*it).getNom() == "Mario") {
			break;
		}
	}

	it = listeHeros.erase(it);
	(*it).afficher(cout);
	cout << trait << "\n";


	//TODO: Assurez-vous que la taille de la liste est correcte après le retrait.
	// Vérification de la taille de la liste après le retrait.
	cout << "Taille de la liste de héros après la suppression de Mario : " << listeHeros.size() << "\n";
	cout << trait << "\n";


	//TODO: Effacez le premier élément de la liste.
	// Retrait du premier élément de la liste.
	it = listeHeros.erase(listeHeros.begin());


	//TODO: Affichez votre liste de héros en utilisant un itérateur. La liste débute avec le héros Randi,
	// n'a pas Mario, et le précédent de "Aya Brea" est ce que vous avez inséré. Servez-vous des methodes
	// begin et end de la liste...
	// Affichage de la liste de héros en utilisant un itérateur.
	cout << "Affichage de la liste avec un itérateur :\n";
	for (auto iter = listeHeros.begin(); iter != listeHeros.end(); ++iter) {
		(*iter).afficher(cout);
		cout << "\n";
	}
	cout << trait << "\n";


	//TODO: Refaite le même affichage mais en utilisant une simple boucle "for" sur intervalle.
	// Affichage de la liste de héros en utilisant une boucle for étendue.
	cout << "Affichage de la liste avec une boucle sur intervalle :\n";
	for (const auto& elem : listeHeros) {
		elem.afficher(cout);
		cout << "\n";
	}
	cout << trait << "\n";


	//TODO: Utilisez un conteneur pour avoir les héros en ordre alphabétique (voir point 2 de l'énoncé).
	//2.1 Utilisation d'un ensemble comme conteneur pour avoir les héros en ordre alphabétique.
	set<Heros> ensembleHeros{};
	for (const auto& h : listeHeros)
		ensembleHeros.insert(h);


	//2.2 Affichage d'un héro en le trouvant par son nom dans l'ensemble (set) en 2.1. 
	// La complexité en moyenne de cette recherche est O(log(n)) où n est la taille de l'ensemble puisque
	// la recherche s'effectue à partir d'un arbre binaire ordonné selon le critère de comparaison des
	// clés de l'ensemble.
	cout << "Affichage de LeBron James en le trouvant dans l'ensemble (set : conteneur) :\n";
	auto itTrouve = ensembleHeros.find(Heros("LeBron James"));
	assert(itTrouve != ensembleHeros.end());
	itTrouve->afficher(cout);
	cout << "\n";


	//2.3 Selon nous, lors d'une recherche d'un héros par le nom, l'ensemble (set : conteneur utilisé en
	// 2.1) permet la recherche la plus rapide, puisque la complexité est logarithmique par rapport à sa
	// taille O(log(n)). La complexité d'une recherche dans une liste liée (1) est linéaire à sa taille O
	// (n).


	//TODO: Assurez-vous de n'avoir aucune ligne non couverte dans les classes pour la liste liée.  Il peut y avoir des lignes non couvertes dans les personnages...
}
