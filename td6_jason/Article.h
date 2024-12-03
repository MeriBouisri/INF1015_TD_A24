#pragma once

#pragma warning(push, 0) // Suppress Qt warnings.
#include <QObject>
#include <string>
#include <boost/functional/hash.hpp>
#pragma pop()

// Define in the desired namespace.
namespace espaceModele {

    struct Article {
        std::string description;
        double prix;
        bool taxable;

        // Default comparison operator
        bool operator==(const Article&) const = default;
    };

    // Extend the `std` namespace for the hash specialization
    namespace std {
        template<> struct hash<espaceModele::Article> {
            size_t operator()(const espaceModele::Article& article) const {
                std::size_t seed = 0;
                boost::hash_combine(seed, article.description);
                boost::hash_combine(seed, article.prix);
                boost::hash_combine(seed, article.taxable);
                return seed;
            }
        };
    }

} // namespace espaceModele
