﻿/**
* Implémentation des fonctions pour la lecture de fichiers binaires
* \file   lectureBinaire.cpp
* \author Département de génie informatique et génie logiciel
* \date   19 novembre 2024
* Créé le 5 novembre 2024
*/

#include "lectureBinaire.hpp"
#include <cassert>
#include <exception>
using namespace std;

namespace {

	template <typename T>
	T lireType(istream& fichier)
	{
		T valeur{};
		fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
		return valeur;
	}

}

#define erreurFataleAssert(message) assert(false&&(message)),terminate()
static const uint8_t enteteTailleVariableDeBase = 0xA0;
size_t lireUintTailleVariable(istream& fichier)
{
	uint8_t entete = lireType<uint8_t>(fichier);
	switch (entete) {
	case enteteTailleVariableDeBase + 0: return lireType<uint8_t>(fichier);
	case enteteTailleVariableDeBase + 1: return lireType<uint16_t>(fichier);
	case enteteTailleVariableDeBase + 2: return lireType<uint32_t>(fichier);
	default:
		erreurFataleAssert("Tentative de lire un entier de taille variable alors que le fichier contient autre chose à cet emplacement."); // Non couvert puisque les tentatives de lecture sont toutes valides
	}
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUintTailleVariable(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
