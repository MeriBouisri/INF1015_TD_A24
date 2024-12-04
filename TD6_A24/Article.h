/**
* Structure pour un article
* \file   Article.h
* \author Bouisri et Xa
* \date   19 novembre 2024
* Créé le 3 décembre 2024
*/

#pragma once

#pragma warning(push, 0)
#include <QObject> 
#include <string>
#include <boost/functional/hash.hpp>
#pragma pop()

namespace espaceModele {
    struct Article {
        std::string description;
        double prix;
        bool taxable;

        bool operator==(const Article&) const = default;
    };
}

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
