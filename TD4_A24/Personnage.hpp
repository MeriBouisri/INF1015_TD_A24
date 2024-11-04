/**
* Classe Personnage
* \file   Personnage.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 24 novembre 2024
*/

#pragma once

#include <string>
#include "Affichable.hpp"

using namespace std;



class Personnage : public Affichable {

    public:
        Personnage() = default;
        Personnage(const string& nom, const string& jeuParution) : nom_(nom), jeuParution_(jeuParution) {}

        string getNom() const {
            return nom_;
        }
        
        string getJeuParution() const {
            return jeuParution_;
        }
        

        // TODO : Move to cpp
        ostream& afficher(ostream& fluxSortie) override {
            fluxSortie << "\nNom : " << nom_
                << "\nParution : " << jeuParution_ << endl;

            return afficherSupplement(fluxSortie);
        }

        // TODO : Move to cpp
        ostream& changerCouleur(ostream& fluxSortie, int theme) override {
            return fluxSortie;
        }


    protected:
        string nom_;
        string jeuParution_;

        virtual ostream& afficherSupplement(ostream& os) = 0;
};
