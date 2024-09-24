#include "Developpeur.hpp"

Developpeur::Developpeur(std::string nom) {
    paireNomJeux_ = std::pair<std::string, ListeJeux>(nom, {0, 0, new Jeu*[0]});
}

Developpeur::~Developpeur() {
    for (Jeu* jeu : ListeJeux::span(paireNomJeux_.second))
        ListeJeux::removeGame(jeu, paireNomJeux_.second);
    
    delete[] paireNomJeux_.second.elements;
    paireNomJeux_.second.elements = nullptr;

    std::cout << "Developpeur detruit : [" << paireNomJeux_.first << ", " << paireNomJeux_.second.elements << "]" << std::endl;
}

std::string Developpeur::getName() const {
    return paireNomJeux_.first;
}

ListeJeux Developpeur::getGameList() {
    return paireNomJeux_.second;
}

void Developpeur::clearGameList() {
    for (Jeu* jeu : ListeJeux::span(paireNomJeux_.second))
        ListeJeux::removeGame(jeu, paireNomJeux_.second);
    
    delete[] paireNomJeux_.second.elements;
    paireNomJeux_.second.elements = new Jeu*[0];
    paireNomJeux_.second.nElements = 0;
    paireNomJeux_.second.capacite = 0;
}


int Developpeur::countGames(ListeJeux& gameList) {
    int count = 0;
    for (Jeu* jeu : ListeJeux::span(gameList))
        if (jeu->developpeur == paireNomJeux_.first) 
            count++;

    return count;
}

void Developpeur::updateGameList(ListeJeux& gameList) {
    // EViter de dupliquer les jeux
    this->clearGameList();

    for (Jeu* jeu : ListeJeux::span(gameList))
        if (jeu->developpeur == this->getName()) 
            ListeJeux::addGame(*jeu, paireNomJeux_.second);
}

void Developpeur::printGameList() {
    std::cout << "Developpeur : " << this->getName() << std::endl;

    for (Jeu* jeu : ListeJeux::span(this->getGameList()))
        std::cout << "\t" << jeu->titre << std::endl;
}




void Developpeur::test() {
    Developpeur* dev = new Developpeur("dev01");

    std::cout << "Developpeur created : [dev.nom=" << dev->getName() << ", " << dev << "]" << std::endl;

    ListeJeux gameList = {0, 0, new Jeu*[3]};

    Jeu jeu1 = {"jeu1", 2020, "dev01"};
    Jeu jeu2 = {"jeu2", 2020, "dev01"};
    Jeu jeu3 = {"jeu3", 2020, "dev02"};

    ListeJeux::addGame(jeu1, gameList);
    ListeJeux::addGame(jeu2, gameList);
    ListeJeux::addGame(jeu3, gameList);

    dev->updateGameList(gameList);

    dev->printGameList();

    delete dev;
}