#ifndef CAMP_H
#define CAMP_H

#include "unite.h"
#include "../Ville/ville.h"
#include <iostream>

const int NB_HEROS_MAX=10;

class Camp{
    std::vector<Unite> herosCamp; //ATTENTION HEROSCAMP EST UN VECTEUR d'UNITES !!
    std::vector<Ville> villesCamp;

public:
    Camp();
    Camp(std::vector<Unite*> unites, std::vector<Ville*> villes);
    Camp(std::vector<Unite*> unites); //uniquement pour tester

    void tourGestion(Carte &carte, std::vector<Unite *> unites, Bouton boutonFinTour, Bouton boutonSauvegarde, Bouton boutonAction, Bouton boutonInventaire, bool &save);
};



#endif