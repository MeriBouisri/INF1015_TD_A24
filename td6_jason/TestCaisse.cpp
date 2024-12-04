/**
 * Tests unitaires pour la classe Caisse
 * \file   TestCaisse.cpp
 * \author Bouisri et Xa
 * \date   4 décembre 2024
 * Créé le 19 novembre 2024
 */

#include "Caisse.h"

#include "Article.h"

#include "gtest/gtest.h"

#include <stdexcept>

namespace espaceModele {
    // Test pour l'ajout et le retrait d'article
    TEST(Caisse, AjouterEtRetirerArticle) {
        Caisse caisse;
        Article article{
          "Article1",
          10.0,
          true
        };

        // Ajouter l'article
        caisse.ajouterArticle("Article1", 10.0, true);
        EXPECT_EQ(caisse.getArticles().size(), 1);
        EXPECT_EQ(caisse.getSousTotal(), 10.0);

        // Retirer l'article
        caisse.retirerArticle(article);
        EXPECT_TRUE(caisse.getArticles().empty());
        EXPECT_EQ(caisse.getSousTotal(), 0.0);
        EXPECT_EQ(caisse.getTaxes(), 0.0);
        EXPECT_EQ(caisse.getTotal(), 0.0);
    }

    // Test pour l'ajout d'article avec des erreurs
    TEST(Caisse, AjouterArticleAvecErreur) {
        Caisse caisse;

        // Test pour une description vide
        EXPECT_THROW(caisse.ajouterArticle("", 10.0, true), ExceptionDescriptionVide);

        // Test pour un prix nul
        EXPECT_THROW(caisse.ajouterArticle("Article2", 0.0, true), ExceptionPrixNul);

        // Test pour un article valide
        EXPECT_NO_THROW(caisse.ajouterArticle("Article3", 20.0, false));
    }

    // Test pour le calcul des taxes et du total
    TEST(Caisse, CalculerTaxesEtTotal) {
        Caisse caisse;
        Article article1{
          "Article1",
          100.0,
          true
        }; // Taxable
        Article article2{
          "Article2",
          50.0,
          false
        }; // Non-taxable

        // Ajout des articles
        caisse.ajouterArticle("Article1", 100.0, true);
        caisse.ajouterArticle("Article2", 50.0, false);

        // Vérification des taxes et du total
        double taxesAttendues = 100.0 * 0.14975; // Taux taxable de 14.975%
        double totalAttendu = 100.0 + 50.0 + taxesAttendues;

        EXPECT_NEAR(caisse.getTaxes(), taxesAttendues, 1e-6);
        EXPECT_NEAR(caisse.getTotal(), totalAttendu, 1e-6);
    }

    // Test pour l'émission de signaux
    TEST(Caisse, EmissionDeSignaux) {
        Caisse caisse;
        Article article{
          "Article1",
          10.0,
          true
        };

        // Ajout de l'article et vérification des signaux
        bool signalArticleModifieEmis = false;
        bool signalSousTotalModifieEmis = false;

        QObject::connect(&caisse, &Caisse::articleModifie, [&signalArticleModifieEmis](const std::unordered_set < Article >& articles) {
            signalArticleModifieEmis = true;
            EXPECT_EQ(articles.size(), 1); // Vérifie si l'article a été ajouté
            });

        QObject::connect(&caisse, &Caisse::sousTotalModifie, [&signalSousTotalModifieEmis](double sousTotal) {
            signalSousTotalModifieEmis = true;
            EXPECT_EQ(sousTotal, 10.0); // Vérifie si le sous-total est correct
            });

        caisse.ajouterArticle("Article1", 10.0, true);

        EXPECT_TRUE(signalArticleModifieEmis);
        EXPECT_TRUE(signalSousTotalModifieEmis);
    }
}