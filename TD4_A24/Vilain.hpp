/**
* Classe Vilain
* \file   Vilain.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 04 novembre 2024
*/

#pragma once

#include <string>

using namespace std;



class Vilain : public Personnage {
    
    public:
        Vilain() = default;
        Vilain(const string& nom, const string& jeuParution, const string& objectif) : Personnage(nom, jeuParution), objectif_(objectif) {}

        Vilain(const Vilain& vilain) : Personnage(vilain), objectif_(vilain.objectif_) {}

        string getObjectif() const {
            return objectif_;
        }

        ostream& afficher(ostream& fluxSortie) override {
            return Personnage::afficher(fluxSortie);
        }

    protected:
        string objectif_;

        ostream& afficherSupplement(ostream& os) override {
            return os << "Objectif : " << objectif_;
        }

};
