#include "CashRegisterView.h"

CashRegisterView::CashRegisterView(QWidget *parent)
    : QMainWindow(parent) {
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

void CashRegisterView::setupUI() {

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
    buttonsLayout->addWidget(this->btnReset_);
    mainLayout->addLayout(buttonsLayout);

    // Articles list
    mainLayout->addWidget(new QLabel("Order:"));
    mainLayout->addWidget(this->listArticles_);

    mainLayout->addWidget(this->lblUntaxedPrice_);
    mainLayout->addWidget(this->lblTaxes_);
    mainLayout->addWidget(this->lblTotalPrice_);

    setCentralWidget(mainWidget);
    setWindowTitle("Cash Register");
    resize(400, 300);

    this->btnRemove_->setEnabled(false);

}

void CashRegisterView::connectSignals() {
    // Buttons
    this->connect(
        this->btnAdd_,
        &QPushButton::clicked, this,
        &CashRegisterView::addArticle);

    this->connect(
        this->btnRemove_,
        &QPushButton::clicked, this,
        &CashRegisterView::removeArticle);

    this->connect(
        this->btnReset_,
        &QPushButton::clicked, this,
        &CashRegisterView::reset);

    //
    this->connect(
        this->listArticles_,
        &QListWidget::itemSelectionChanged, this,
        &CashRegisterView::updateButtons);

    // this->connect(
    //     &model_,
    //     &CashRegisterModel::onUpdateArticles, this,
    //     &CashRegisterView::updatePrice);

    // this->connect(
    //     &model_,
    //     &CashRegisterModel::onUpdatePrice, this,
    //     &CashRegisterView::updatePrice);
}

void CashRegisterView::addArticle() {

}

void CashRegisterView::removeArticle() {

}

void CashRegisterView::reset() {

}

void CashRegisterView::update() {

}

void CashRegisterView::updatePrice() {

}

void CashRegisterView::updateButtons() {

}
