/**
 * Vue et controlleur pour une caisse enregistreuse
 * \file   CaisseWindow.cpp
 * \author Bouisri et Xa
 * \date   4 décembre 2024
 * Créé le 19 novembre 2024
 */

#include "CaisseWindow.h"

#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QHBoxLayout>

#include <QPushButton>

#include <QButtonGroup>

#include <QLabel>

#include <QString>

#include <QVariant>

#pragma pop()

#include <iostream>

#include <type_traits>

#include <cppitertools/range.hpp><

using iter::range;

CaisseWindow::CaisseWindow(QWidget* parent) : QMainWindow(parent) {
    this->inputPrice_ = new QLineEdit(this);
    this->inputDescription_ = new QLineEdit(this);
    this->cboxTaxable_ = new QCheckBox("Taxable", this);
    this->listArticles_ = new QListWidget(this);
    this->btnAdd_ = new QPushButton("Add", this);
    this->btnRemove_ = new QPushButton("Remove", this);
    this->lblUntaxedPrice_ = new QLabel("Subtotal : 0.00", this);
    this->lblTaxes_ = new QLabel("Taxes : 0.00", this);
    this->lblUntaxedPrice_ = new QLabel("Total : 0.00", this);

    this->setupUI();
    this->connectSignals();
}

void CaisseWindow::setupUI() {

    auto* mainWidget = new QWidget(this);
    auto* mainLayout = new QVBoxLayout(mainWidget);

    // Article entry
    auto* entryLayout = new QHBoxLayout();
    entryLayout->addWidget(new QLabel("Description:"));
    entryLayout->addWidget(this->inputDescription_);
    entryLayout->addWidget(new QLabel("Price:"));
    entryLayout->addWidget(this->inputPrice_);
    entryLayout->addWidget(this->cboxTaxable_);

    mainLayout->addLayout(entryLayout);

    // Buttons
    auto* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(this->btnAdd_);
    buttonsLayout->addWidget(this->btnRemove_);
    //buttonsLayout->addWidget(this->btnReset_);
    mainLayout->addLayout(buttonsLayout);

    // Articles list
    mainLayout->addWidget(new QLabel("Order:"));
    mainLayout->addWidget(this->listArticles_);

    mainLayout->addWidget(this->lblUntaxedPrice_);
    mainLayout->addWidget(this->lblTaxes_);
    //mainLayout->addWidget(this->lblTotalPrice_);

    setCentralWidget(mainWidget);
    setWindowTitle("Cash Register");
    resize(400, 300);

    this->btnRemove_->setEnabled(false);

}

void CaisseWindow::connectSignals() {
    // Buttons
    this->connect(
        this->btnAdd_, &
        QPushButton::clicked, this, &
        CaisseWindow::addArticle);

    this->connect(
        this->btnRemove_, &
        QPushButton::clicked, this, &
        CaisseWindow::removeArticle);

    this->connect(
        this->btnReset_, &
        QPushButton::clicked, this, &
        CaisseWindow::reset);

    //
    this->connect(
        this->listArticles_, &
        QListWidget::itemSelectionChanged, this, &
        CaisseWindow::updateButtons);

    // this->connect(
    //     &model_,
    //     &CashRegisterModel::onUpdateArticles, this,
    //     &CaisseWindow::updatePrice);

    // this->connect(
    //     &model_,
    //     &CashRegisterModel::onUpdatePrice, this,
    //     &CaisseWindow::updatePrice);
}

void CaisseWindow::addArticle() {

}

void CaisseWindow::removeArticle() {

}

void CaisseWindow::reset() {

}

void CaisseWindow::update() {

}

void CaisseWindow::updatePrice() {

}

void CaisseWindow::updateButtons() {

}