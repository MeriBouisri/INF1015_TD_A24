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

        Heros(const Heros& heros) : Personnage(heros), nomEnnemi_(heros.nomEnnemi_), nomsAllies_(heros.nomsAllies_) {}

        Heros(ifstream& fichier) {
            // TODO : Lecture fichier heros
        }

        string getNomEnnemi() const {
            return nomEnnemi_;
        }

        // TODO : encapsulation (ajouterAllies)
        vector<string>& getNomsAllies() {
            return nomsAllies_;
        }

        ostream& afficher(ostream& fluxSortie) override {
            return Personnage::afficher(fluxSortie);
        }

        // TODO : theme in constant
        ostream& changerCouleur(ostream& fluxSortie, int theme = 94) override {
            return Personnage::changerCouleur(fluxSortie, theme);
        }


    protected:
        vector<string> nomsAllies_; // TODO : maybe not right type
        string nomEnnemi_;
        
        ostream& afficherSupplement(ostream& os) override {
            os << "Ennemi : " << nomEnnemi_
                << "\nAllies :";

            for (const auto& a : nomsAllies_)
                os << "\t\n" << a << " ";

            return os;
        }

};
