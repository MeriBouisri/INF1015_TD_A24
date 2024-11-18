/**
* Fonctions pour la lecture de fichiers binaires
* \file   lectureBinaire.hpp
* \author Département de génie informatique et génie logiciel
* \date   5 novembre 2024
* Créé le 22 octobre 2024
*/

#pragma once

#include <cstddef>
#include <fstream>
#include <string>

std::size_t lireUintTailleVariable(std::istream& fichier);
std::string lireString(std::istream& fichier);