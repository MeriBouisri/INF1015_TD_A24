/**
* Structure d'un article d'une caisse enregistreuse
* \file   Article.h
* \author Bouisri et Xa
* \date   4 décembre 2024
* Créé le 19 novembre 2024
*/

#pragma once

#pragma warning(push, 0) // Sinon Qt soulève des avertissements à /W4.
#include <boost/functional/hash.hpp>
#pragma pop()

namespace espaceModele {
    struct Article {
        std::string description;
        double prix;
        bool taxable;

        bool operator==(const Article&) const = default; // Opérateur de comparaison pour les algorithmes de recherce.
    };
}


// Redéfinition de la fonction de hachage pour les articles
using namespace espaceModele;
    namespace std {
        template<> struct hash<Article> {
            size_t operator()(const Article& article) const {
                std::size_t seed = 0;
                boost::hash_combine(seed, article.description);
                boost::hash_combine(seed, article.prix);
                boost::hash_combine(seed, article.taxable);
                return seed;
            }
        };
    }