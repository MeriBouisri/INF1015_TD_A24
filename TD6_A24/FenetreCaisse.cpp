#include "FenetreCaisse.h"
#include "Caisse.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>


FenetreCaisse::FenetreCaisse(QWidget* parent)
    : QMainWindow(parent) {
    // Initialisation des widgets
    inputDescription_ = new QLineEdit(this);
    inputPrix_ = new QLineEdit(this);
    cboxTaxable_ = new QCheckBox("Taxable", this);
    btnAjouter_ = new QPushButton("Ajouter", this);
    btnRetirer_ = new QPushButton("Retirer", this);
    btnReinitialiser_ = new QPushButton("Réinitialiser", this);
    listArticles_ = new QListWidget(this);
    lblSousTotal_ = new QLabel("Sous-total : 0.00", this);
    lblTaxes_ = new QLabel("Taxes : 0.00", this);
    lblTotal_ = new QLabel("Total : 0.00", this);

    // Configuration de l'interface et connexions
    configurerInterface();
    connecterSignaux();
}

void FenetreCaisse::configurerInterface() {
    auto* layoutPrincipal = new QVBoxLayout();
    auto* layoutChamps = new QHBoxLayout();
    auto* layoutBoutons = new QHBoxLayout();

    // Champs de saisie
    layoutChamps->addWidget(inputDescription_);
    inputDescription_->setPlaceholderText("Description de l'article");
    layoutChamps->addWidget(inputPrix_);
    inputPrix_->setPlaceholderText("Prix (en $)");
    layoutChamps->addWidget(cboxTaxable_);

    // Boutons
    layoutBoutons->addWidget(btnAjouter_);
    layoutBoutons->addWidget(btnRetirer_);
    layoutBoutons->addWidget(btnReinitialiser_);

    // Assemblage du layout principal
    layoutPrincipal->addLayout(layoutChamps);
    layoutPrincipal->addLayout(layoutBoutons);
    layoutPrincipal->addWidget(listArticles_);
    layoutPrincipal->addWidget(lblSousTotal_);
    layoutPrincipal->addWidget(lblTaxes_);
    layoutPrincipal->addWidget(lblTotal_);

    // Définir le widget principal
    auto* widgetPrincipal = new QWidget();
    widgetPrincipal->setLayout(layoutPrincipal);
    setCentralWidget(widgetPrincipal);
    setWindowTitle("Caisse enregistreuse");
    resize(400, 300);
}

void FenetreCaisse::connecterSignaux() {
    connect(btnAjouter_, &QPushButton::clicked, this, &FenetreCaisse::ajouterArticle);
    connect(btnRetirer_, &QPushButton::clicked, this, &FenetreCaisse::retirerArticle);
    connect(btnReinitialiser_, &QPushButton::clicked, this, &FenetreCaisse::reinitialiser);

    // Connexion des signaux du modèle avec les slots de la vue
    connect(&modele_, &espaceModele::Caisse::sousTotalModifie, this, &FenetreCaisse::mettreAJourSousTotal);
    connect(&modele_, &espaceModele::Caisse::taxesModifiees, this, &FenetreCaisse::mettreAJourTaxes);
    connect(&modele_, &espaceModele::Caisse::totalModifie, this, &FenetreCaisse::mettreAJourTotal);
}

void FenetreCaisse::ajouterArticle() {
    QString description = inputDescription_->text().trimmed();
    bool conversionReussie;
    double prix = inputPrix_->text().toDouble(&conversionReussie);

    if (description.isEmpty() || !conversionReussie || prix <= 0) {
        afficherErreur("Conversion echoue.");
        return;
    }

    try {
        modele_.ajouterArticle(description.toStdString(), prix, cboxTaxable_->isChecked());
        auto* nouvelItem = new QListWidgetItem(
            QString("%1 - %2 %3").arg(description).arg(prix, 0, 'f', 2).arg(cboxTaxable_->isChecked() ? "(Taxable)" : ""));
        listArticles_->addItem(nouvelItem);
    }
    catch (const std::exception& e) {
        afficherErreur(e.what());
    }
}

void FenetreCaisse::retirerArticle() {
    auto* articleSelectionne = listArticles_->currentItem();
    if (!articleSelectionne) {
        afficherErreur("Aucun article sélectionné.");
        return;
    }

    QString description = articleSelectionne->text().split(" - ").first();
  //  modele_.retirerArticle(espaceModele::Article{ description.toStdString(), 0.0, false });
  
   // TODO: tell model
   // this->modele_.retirerArticle(); 
   delete articleSelectionne;

}

void FenetreCaisse::reinitialiser() {
    this->listArticles_->clear();
    this->modele_.reinitialiserCaisse();
    this->actualiser();
}

void FenetreCaisse::actualiser() {
    this->mettreAJourSousTotal(this->modele_.getSousTotal());
    this->mettreAJourTaxes(this->modele_.getTaxes());
    this->mettreAJourTotal(this->modele_.getTotal());
}

void FenetreCaisse::mettreAJourSousTotal(double sousTotal) {
    lblSousTotal_->setText(QString("Sous-total : %1").arg(sousTotal, 0, 'f', 2));
}

void FenetreCaisse::mettreAJourTaxes(double taxes) {
    lblTaxes_->setText(QString("Taxes : %1").arg(taxes, 0, 'f', 2));
}

void FenetreCaisse::mettreAJourTotal(double total) {
    lblTotal_->setText(QString("Total : %1").arg(total, 0, 'f', 2));
}

void FenetreCaisse::afficherErreur(const QString& message) {
    QMessageBox::warning(this, "Erreur", message);
}
