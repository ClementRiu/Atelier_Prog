#pragma once


#include <vector>
#include <Imagine/Graphics.h>
#include "../Gestion/carte.h"


class Attaque{
    std::vector<Imagine::Coords<2> > zoneInfluence;
    int puissance;
public:
    Attaque(std::vector<Imagine::Coords<2> > zone, int power);
    // Affiche la zone d'influence de l'attaque
    void zone(Case *carte, Unite u, bool b);
    // Action que fait l'attaque, A COMPLETER (enlève des points de vie, pousse des ennemis pour des sous classes d'attaques...)
    void action(Unite &u);
};

void attaque(Attaque attq, Case *carte, std::vector<Unite> &unites, int u);
