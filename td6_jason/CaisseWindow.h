/**
 * Vue et controlleur pour une caisse enregistreuse
 * \file   CaisseWindow.h
 * \author Bouisri et Xa
 * \date   4 décembre 2024
 * Créé le 19 novembre 2024
 */

#pragma once

#include "Caisse.h"

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>

#include <QLabel>

#include <QPushButton>

#include <QCheckBox>

#include <QList>

#include <QLineEdit>

#include <QListWidget>

#include <QVBoxLayout>

#include <QHBoxLayout>

#include <QMessageBox>

#include <QString>

#pragma pop()

using namespace espaceModele;

class CaisseWindow : public QMainWindow {
    Q_OBJECT

public:
    CaisseWindow(QWidget* parent = nullptr);
    ~CaisseWindow() override =
        default;

private slots:
    void addArticle();
    void removeArticle();
    void reset();
    void update();
    void updatePrice();
    void updateButtons();

private:
    Caisse model_;

    QLineEdit* inputDescription_; // 1a
    QLineEdit* inputPrice_; // 1b
    QPushButton* btnAdd_; // 2a
    QPushButton* btnRemove_; // 2b
    QPushButton* btnReset_; // 2c
    QCheckBox* cboxTaxable_; // 3
    QListWidget* listArticles_; // 4

    QLabel* lblUntaxedPrice_; // 5a
    QLabel* lblTaxes_; // 5b
    QLabel* lblTotalPrice_; // 5c

    // Methodes

    void setupUI();
    void connectSignals();

};