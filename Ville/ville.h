#pragma once

#include <Imagine/Graphics.h>
#include <stdlib.h>
#include "../Gestion/unite.h"

const int NB_BATIMENTS = 10;
const int NB_AMELIORATIONS = 3;


class Ville {
    int batiments[NB_BATIMENTS]; //Chaque élément du tableau représente un bâtiment, si batiment[i]=0 il n'est pas construit, batiment[i]=2 il est au niveau 2 etc
    Imagine::Color image[NB_BATIMENTS];
    std::string description[NB_BATIMENTS * NB_BATIMENTS]; //description pour chaque bâtiment et ses améliorations
    int cout[NB_BATIMENTS * NB_AMELIORATIONS];

    int camp; //le joueur à qui appartient la ville
public:
    // Affiche le Batiment cf Clement
    void affiche();

    // Fait monter la batiment de niveau
    void ameliore(int i);
};


class Reserve {
    Armee armeeReserve;
};
