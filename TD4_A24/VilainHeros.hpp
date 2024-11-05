/**
* Classe VilainHeros
* \file   VilainHeros.hpp
* \author Bouisri et Xa
* \date   05 novembre 2024 2024
* Cree le 24 novembre 2024
*/

#pragma once

#include <string>
#include "Personnage.hpp"
#include <vector>

using namespace std;



class VilainHeros : public Vilain, public Heros {
    
    public:
        VilainHeros() = default;
        VilainHeros(const Vilain& vilain, const Heros& heros) : Vilain(vilain), Heros(heros) {
            Personnage::nom_ = vilain.getNom() + "-" + heros.getNom();
            Personnage::jeuParution_ = vilain.getJeuParution() + "-" + heros.getJeuParution();
            missionSpeciale_ = vilain.getObjectif() + " dans le monde de " + heros.getJeuParution();
            // TODO : Changer couleur 
        }

        ostream& afficher(ostream& fluxSortie) override {
            return Personnage::afficher(fluxSortie);
        }

        // TODO : theme in constant
        ostream& changerCouleur(ostream& fluxSortie, int theme = 35) override {
            return Personnage::changerCouleur(fluxSortie, theme);
        }


    protected:
        ostream& afficherSupplement(ostream& os) override {
            Vilain::afficherSupplement(os) << endl;
            Heros::afficherSupplement(os) << endl;

            return os << "Mission speciale : " << missionSpeciale_;
        }

        

    private:
        string missionSpeciale_;


};
