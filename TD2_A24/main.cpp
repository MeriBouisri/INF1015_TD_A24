#include "Jeu.hpp"
#include <iostream>
#include <fstream>
#include <cstdint>
#include "cppitertools/range.hpp"
#include "gsl/span"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.

using namespace std;
using namespace iter;
using namespace gsl;

#pragma region "Fonctions de base pour vous aider"
template <typename T>
T lireType(istream& fichier)
{
	T valeur{};
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}
#define erreurFataleAssert(message) assert(false&&(message)),terminate()
static const uint8_t enteteTailleVariableDeBase = 0xA0;
size_t lireUintTailleVariable(istream& fichier)
{
	uint8_t entete = lireType<uint8_t>(fichier);
	switch (entete) {
	case enteteTailleVariableDeBase+0: return lireType<uint8_t>(fichier);
	case enteteTailleVariableDeBase+1: return lireType<uint16_t>(fichier);
	case enteteTailleVariableDeBase+2: return lireType<uint32_t>(fichier);
	default:
		erreurFataleAssert("Tentative de lire un entier de taille variable alors que le fichier contient autre chose à cet emplacement.");
	}
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUintTailleVariable(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
gsl::span<Jeu*> spanListeJeux(const ListeJeux& liste)
{
	return gsl::span(liste.elements, liste.nElements);
}
gsl::span<Concepteur*> spanListeConcepteurs(const ListeConcepteurs& liste)
{
	return gsl::span(liste.elements, liste.nElements);
}
#pragma endregion


Concepteur* findDesigner(string name, const ListeJeux& gameList) {
	gsl::span<Jeu*> spanGameList = spanListeJeux(gameList);
	for (Jeu* game : spanGameList) {
		gsl::span<Concepteur*> spanDesignerList = spanListeConcepteurs(game->concepteurs);
		for (Concepteur* designer : spanDesignerList) {
			if (designer->nom == name) {
				return designer;
			}
		}
	}
	return nullptr;
}


Concepteur* lireConcepteur(istream& fichier, const ListeJeux& gameList)
{
	Concepteur concepteur = {}; // On initialise une structure vide de type Concepteur.
	concepteur.nom = lireString(fichier);
	concepteur.anneeNaissance = int(lireUintTailleVariable(fichier));
	concepteur.pays = lireString(fichier);
	// Rendu ici, les champs précédents de la structure concepteur sont remplis
	// avec la bonne information.

	//TODO (done): Ajouter en mémoire le concepteur lu. Il faut revoyer le pointeur créé.
	// Attention, valider si le concepteur existe déjà avant de le créer, sinon
	// on va avoir des doublons car plusieurs jeux ont des concepteurs en commun
	// dans le fichier binaire. Pour ce faire, cette fonction aura besoin de
	// la liste de jeux principale en paramètre.
	// Afficher un message lorsque l'allocation du concepteur est réussie.

	Concepteur* ptrConcepteur = findDesigner(concepteur.nom, gameList);

	if (!ptrConcepteur)
		ptrConcepteur = new Concepteur(concepteur);

	// TODO (personnel) : Ajout methodes struct Concepteur
	ptrConcepteur->jeuxConcus = {};
	ptrConcepteur->jeuxConcus.capacite = 0;
	ptrConcepteur->jeuxConcus.nElements = 0;
	ptrConcepteur->jeuxConcus.elements = new Jeu*[ptrConcepteur->jeuxConcus.capacite];

	cout << "Allocated [Concepteur, " << ptrConcepteur->nom << ", " << ptrConcepteur << "]" << endl;

	return ptrConcepteur; //TODO (done): Retourner le pointeur vers le concepteur crée.
}


void increaseGameListCapacity(size_t newCapacity, ListeJeux& gameList) {
	Jeu** newGames = new Jeu* [newCapacity];
	gsl::span<Jeu*> spanGameList = spanListeJeux(gameList);
	int i = 0;

	for (Jeu* game : spanGameList) {
		newGames[i++] = game;
	}

	delete[] gameList.elements;

	gameList.elements = newGames;
	gameList.capacite = newCapacity;
}


void addGame(Jeu& game, ListeJeux& gameList) {
	if (gameList.nElements >= gameList.capacite) {
		increaseGameListCapacity(gameList.capacite*2, gameList);
	}
	gameList.elements[gameList.nElements++] = &game;
}



//TODO: Fonction qui enlève un jeu de ListeJeux.
// Attention, ici il n'a pas de désallocation de mémoire. Elle enlève le
// pointeur de la ListeJeux, mais le jeu pointé existe encore en mémoire.
// Puisque l'ordre de la ListeJeux n'a pas être conservé, on peut remplacer le
// jeu à être retiré par celui présent en fin de liste et décrémenter la taille
// de celle-ci.

Jeu* lireJeu(istream& fichier, ListeJeux& gameList)
{
	Jeu jeu = {}; // On initialise une structure vide de type Jeu
	jeu.titre = lireString(fichier);
	jeu.anneeSortie = int(lireUintTailleVariable(fichier));
	jeu.developpeur = lireString(fichier);
	jeu.concepteurs.nElements = lireUintTailleVariable(fichier);
	// Rendu ici, les champs précédents de la structure jeu sont remplis avec la
	// bonne information.

	//TODO (done): Ajouter en mémoire le jeu lu. Il faut revoyer le pointeur créé.
	// Attention, il faut aussi créer un tableau dynamique pour les concepteurs
	// que contient un jeu. Servez-vous de votre fonction d'ajout de jeu car la
	// liste de jeux participé est une ListeJeu. Afficher un message lorsque
	// l'allocation du jeu est réussie.

	Jeu* ptrJeu = new Jeu(jeu);
	ptrJeu->concepteurs.elements = new Concepteur*[jeu.concepteurs.nElements]; 

	for ([[maybe_unused]] size_t i : iter::range(jeu.concepteurs.nElements)) {
		//TODO (done): Mettre le concepteur dans la liste des concepteur du jeu.
		Concepteur* concepteur = lireConcepteur(fichier, gameList);  
		ptrJeu->concepteurs.elements[i] = concepteur;
		
		//TODO (done): Ajouter le jeu à la liste des jeux auquel a participé le concepteur.
		addGame(*ptrJeu, concepteur->jeuxConcus);
	}

	cout << "Allocated [Jeu, " << ptrJeu->titre << ", " << ptrJeu << "]" << endl;

	return ptrJeu; // TODO (done): Retourner le pointeur vers le nouveau jeu.
}

ListeJeux creerListeJeux(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);

	ListeJeux listeJeux = {};

	listeJeux.nElements = 0;
	listeJeux.capacite = lireUintTailleVariable(fichier);
	listeJeux.elements = new Jeu*[listeJeux.capacite];
	
	for([[maybe_unused]] size_t n : iter::range(listeJeux.capacite))
	{
		Jeu* jeu = lireJeu(fichier, listeJeux); // (done) TODO: Ajouter le jeu à la ListeJeux.
		addGame(*jeu, listeJeux);
	}

	return listeJeux; // (done) TODO: Renvoyer la ListeJeux.
}

//TODO: Fonction pour détruire un concepteur (libération de mémoire allouée).
// Lorsqu'on détruit un concepteur, on affiche son nom pour fins de débogage.

//TODO: Fonction qui détermine si un concepteur participe encore à un jeu.

//TODO: Fonction pour détruire un jeu (libération de mémoire allouée).
// Attention, ici il faut relâcher toute les cases mémoires occupées par un jeu.
// Par conséquent, il va falloir gérer le cas des concepteurs (un jeu contenant
// une ListeConcepteurs). On doit commencer par enlever le jeu à détruire des jeux
// qu'un concepteur a participé (jeuxConcus). Si le concepteur n'a plus de
// jeux présents dans sa liste de jeux participés, il faut le supprimer.  Pour
// fins de débogage, affichez le nom du jeu lors de sa destruction.

//TODO: Fonction pour détruire une ListeJeux et tous ses jeux.

void afficherConcepteur(const Concepteur& d)
{
	cout << "\t" << d.nom << ", " << d.anneeNaissance << ", " << d.pays
			  << endl;
}

//TODO: Fonction pour afficher les infos d'un jeu ainsi que ses concepteurs.
// Servez-vous de la fonction afficherConcepteur ci-dessus.
void afficherJeu(const Jeu& j)
{
	cout << j.titre << ", " << j.anneeSortie << ", " << j.developpeur << endl;
	cout << "Concepteurs:" << endl;
	for (Concepteur* c : spanListeConcepteurs(j.concepteurs))
		afficherConcepteur(*c);
}

//TODO: Fonction pour afficher tous les jeux de ListeJeux, séparés par un ligne.
// Servez-vous de la fonction d'affichage d'un jeu crée ci-dessus. Votre ligne
// de séparation doit être différent de celle utilisée dans le main.
void afficherListeJeux(const ListeJeux& listeJeux)
{
	for (Jeu* j : spanListeJeux(listeJeux)) {
		afficherJeu(*j);
		cout << "\n";
	}
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi(); 
	#pragma endregion

	int* fuite = new int;  // Pour vérifier que la détection de fuites fonctionne; un message devrait dire qu'il y a une fuite à cette ligne.

	ListeJeux gameList = creerListeJeux("jeux.bin"); //TODO (done): Appeler correctement votre fonction de création de la liste de jeux.

	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	cout << ligneSeparation << endl;
	cout << "Premier jeu de la liste :" << endl;

	//TODO (done): Afficher le premier jeu de la liste (en utilisant la fonction).  Devrait être Chrono Trigger.

	cout << gameList.elements[0]->titre << endl;

	cout << ligneSeparation << endl;

	//TODO (done): Appel à votre fonction d'affichage de votre liste de jeux.

	afficherListeJeux(gameList);

	cout << ligneSeparation << endl;
	
	//TODO: Faire les appels à toutes vos fonctions/méthodes pour voir qu'elles fonctionnent et avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.



	//TODO: Détruire tout avant de terminer le programme.  Devrait afficher "Aucune fuite detectee." a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
}
