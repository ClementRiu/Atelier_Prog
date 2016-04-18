#include "attaque.h"



Attaque::Attaque(std::vector<Imagine::Coords<2> > zone, int power) {
    zoneInfluence = zone;
    puissance = power;
}


void Attaque::action(Unite &u) {
    // A MODIFIER
    u.prendDommage(puissance);
}


void Attaque::zone(Case *carte, Unite u, bool b) {
    int caseHeros = u.getCase();
    for (int i = 0; i < zoneInfluence.size(); ++i){
        if (caseHeros + zoneInfluence[i].y() * NbCase > 0 && caseHeros + zoneInfluence[i].y() * NbCase &&
                (caseHeros / NbCase == (caseHeros + zoneInfluence[i].x()) / NbCase)){
            carte[caseHeros + zoneInfluence[i].x() + zoneInfluence[i].y() * NbCase].brillanceOnOff(b);
        }
    }
}
