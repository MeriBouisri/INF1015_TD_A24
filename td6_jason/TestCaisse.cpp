/**
* Modèle pour une caisse enregistreuse
* \file   Caisse.cpp
* \author Bouisri et Xa
* \date   4 décembre 2024
* Créé le 19 novembre 2024
*/

#include "Caisse.h"
#include "Article.h"
#include "gtest/gtest.h"
#include <stdexcept>

namespace espaceModele {

    // Test for adding and removing articles
    TEST(Caisse, AjouterEtRetirerArticle) {
        Caisse caisse;
        Article article{ "Article1", 10.0, true };

        // Add article
        caisse.ajouterArticle("Article1", 10.0, true);
        EXPECT_EQ(caisse.getArticles().size(), 1);
        EXPECT_EQ(caisse.getSousTotal(), 10.0);

        // Remove article
        caisse.retirerArticle(article);
        EXPECT_TRUE(caisse.getArticles().empty());
        EXPECT_EQ(caisse.getSousTotal(), 0.0);
        EXPECT_EQ(caisse.getTaxes(), 0.0);
        EXPECT_EQ(caisse.getTotal(), 0.0);
    }

    // Test for exceptions when adding articles
    TEST(Caisse, AjouterArticleAvecErreur) {
        Caisse caisse;

        // Test for empty description
        EXPECT_THROW(caisse.ajouterArticle("", 10.0, true), ExceptionDescriptionVide);

        // Test for zero price
        EXPECT_THROW(caisse.ajouterArticle("Article2", 0.0, true), ExceptionPrixNul);

        // Test for valid article
        EXPECT_NO_THROW(caisse.ajouterArticle("Article3", 20.0, false));
    }

    // Test for tax and total calculations
    TEST(Caisse, CalculerTaxesEtTotal) {
        Caisse caisse;
        Article article1{ "Article1", 100.0, true };  // Taxable
        Article article2{ "Article2", 50.0, false };   // Non-taxable

        // Add articles
        caisse.ajouterArticle("Article1", 100.0, true);
        caisse.ajouterArticle("Article2", 50.0, false);

        // Check taxes and total calculations
        double expectedTaxes = 100.0 * 0.14975; // Tax rate of 14.975%
        double expectedTotal = 100.0 + 50.0 + expectedTaxes;

        EXPECT_NEAR(caisse.getTaxes(), expectedTaxes, 1e-6);
        EXPECT_NEAR(caisse.getTotal(), expectedTotal, 1e-6);
    }

    // Test for signal emission
    TEST(Caisse, EmissionDeSignaux) {
        Caisse caisse;
        Article article{ "Article1", 10.0, true };

        // Add article and test signal emission
        bool signalArticleModifieEmis = false;
        bool signalSousTotalModifieEmis = false;

        QObject::connect(&caisse, &Caisse::articleModifie, [&signalArticleModifieEmis](const std::unordered_set<Article>& articles) {
            signalArticleModifieEmis = true;
            EXPECT_EQ(articles.size(), 1); // Check the number of articles
            });

        QObject::connect(&caisse, &Caisse::sousTotalModifie, [&signalSousTotalModifieEmis](double sousTotal) {
            signalSousTotalModifieEmis = true;
            EXPECT_EQ(sousTotal, 10.0); // Check if the subtotal is correct
            });

        caisse.ajouterArticle("Article1", 10.0, true);

        EXPECT_TRUE(signalArticleModifieEmis);
        EXPECT_TRUE(signalSousTotalModifieEmis);
    }

} // namespace espaceModele
