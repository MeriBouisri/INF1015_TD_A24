#ifndef CASHREGISTERVIEW_H
#define CASHREGISTERVIEW_H

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
#include "CashRegisterModel.h"


class CashRegisterView : public QMainWindow
{
    Q_OBJECT

public:
    CashRegisterView(QWidget *parent = nullptr);
    ~CashRegisterView() override = default;

private slots:
    void addArticle();
    void removeArticle();
    void reset();
    void update();
    void updatePrice();
    void updateButtons();


private:
    CashRegisterModel model_;

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
#endif // CASHREGISTERVIEW_H
