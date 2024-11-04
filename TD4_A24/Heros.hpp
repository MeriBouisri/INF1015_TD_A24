/**
* Classe Heros
* \file   Heros.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 24 novembre 2024
*/

#pragma once

#include <string>
#include "Personnage.hpp"
#include <vector>

using namespace std;



class Heros : public Personnage {
    
    public:
        Heros() = default;
        Heros(const string& nom, const string& jeuParution, const string& nomEnnemi) : Personnage(nom, jeuParution), nomEnnemi_(nomEnnemi) {
            nomsAllies_= {};
        }

        string getNomEnnemi() const {
            return nomEnnemi_;
        }

        // TODO : encapsulation (ajouterAllies)
        vector<string>& getNomsAllies() {
            return nomsAllies_;
        }


        // TODO : Move to cpp
        ostream& afficher(ostream& fluxSortie) override {
            Personnage::afficher(fluxSortie)
                << "Ennemi : " << nomEnnemi_
                << "\nAllies :";

            for (const auto& a : nomsAllies_)
                fluxSortie << "\t\n" << a << " ";
            
            return fluxSortie;
        }



    private:
        vector<string> nomsAllies_; // TODO : maybe not right type
        string nomEnnemi_;
};
