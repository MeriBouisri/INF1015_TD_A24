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


class CaisseWindow : public QMainWindow
{
    Q_OBJECT

public:
    CaisseWindow(QWidget* parent = nullptr);
    ~CaisseWindow() override = default;

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
