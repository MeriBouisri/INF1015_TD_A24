/**
 * Vue et contrôleur pour une caisse enregistreuse
 * \file   FenetreCaisse.h
 * \author Bouisri et Xa
 * \date   19 novembre 2024
 * Créé le 3 décembre 2024
 */

#pragma once

#include "Caisse.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <string>
#include <stdexcept>


    class FenetreCaisse : public QMainWindow {
        Q_OBJECT

    public:
        explicit FenetreCaisse(QWidget* parent = nullptr);

    private slots:
        void ajouterArticle();
        void retirerArticle();
        void reinitialiser();
        void actualiser();
        void mettreAJourSousTotal(double sousTotal);
        void mettreAJourTaxes(double taxes);
        void mettreAJourTotal(double total);

    private:
        // Modèle
        espaceModele::Caisse modele_;

        // Widgets
        QLineEdit* inputDescription_;
        QLineEdit* inputPrix_;
        QCheckBox* cboxTaxable_;
        QPushButton* btnAjouter_;
        QPushButton* btnRetirer_;
        QPushButton* btnReinitialiser_;
        QListWidget* listArticles_;
        QLabel* lblSousTotal_;
        QLabel* lblTaxes_;
        QLabel* lblTotal_;

        // Méthodes utilitaires
        void configurerInterface();
        void connecterSignaux();
        void afficherErreur(const QString& message);
    };
