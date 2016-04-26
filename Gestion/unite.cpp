#include "unite.h"
#include <iostream>

Unite::Unite() {
    PDep = 8;
    numcase = 0;
}

Unite::Unite(float dep, int num) {
    PDep = dep;
    numcase = num;
    PDepMax = dep;
}

void Unite::changeOrientation(int i) {
    orientation = i;
}

int Unite::getCase() const {
    return numcase;
}


void Unite::setCase(int num) {
    numcase = num;
}


float Unite::getDep() const {
    return PDep;
}


void Unite::setDep(float dep) {
    PDep = dep;
}


float Unite::getDepMax() const {
    return PDepMax;
}


Heros::Heros(float dep, int num) : Unite(dep, num) {
}

//à implémenter
void Unite::prendDommage(int attRecue) {
    std::cout << "à implémenter !" << std::endl;
}

bool Unite::estVivant() {
    if (PV <= 0) {
        return false;
    }
    return true;
}


void Unite::action(Attaque att, Unite &u) {
    // A MODIFIER
    u.prendDommage(att.getPuissance());
}



void attaque(Attaque attq, Case *carte, std::vector<Unite> &unites, int u) {
    int x1, y1, u2 = 0;
    attq.zone(carte, unites[u], true);
    do {
        clic(x1, y1, carte);
    } while(x1 > Taille * NbCase || y1 > Taille * NbCase || !carte[numeroCase(x1, y1)].Brillance());
    if (carte[numeroCase(x1, y1)].getOccupe()) {
        while (unites[u2].getCase() != numeroCase(x1, y1)) {
            u2 += 1;
        }
        unites[u].action(attq, unites[u2]);
    }
    attq.zone(carte, unites[u], false);
}


//*********************************EQUIPEMENT********************************************
Equipement Heros::equipeCasque(Equipement casque) {
    Equipement desequipe = equipementCasque;

    equipementCasque = casque;

    return desequipe;
}

//manque gestion des deux mains !!
Equipement Heros::equipeArmeDroite(Equipement arme) {
    Equipement desequipe = equipementArmeDroite;

    equipementArmeDroite = arme;

    return desequipe;
}

Equipement Heros::equipeArmeGauche(Equipement arme) {
    Equipement desequipe = equipementArmeGauche;

    equipementArmeGauche = arme;

    return desequipe;
}


Equipement Heros::equipeTorse(Equipement torse) {
    Equipement desequipe = equipementTorse;

    equipementTorse = torse;

    return desequipe;

}

Equipement Heros::equipeGants(Equipement gants) {
    Equipement desequipe = equipementGants;

    equipementGants = gants;

    return desequipe;
}

Equipement Heros::equipeJambes(Equipement jambes) {
    Equipement desequipe = equipementJambes;

    equipementJambes = jambes;

    return desequipe;
}

Equipement Heros::equipeBottes(Equipement bottes) {
    Equipement desequipe = equipementBottes;

    equipementBottes = bottes;

    return desequipe;
}

//manque gestion des deux anneaux !!
Equipement Heros::equipeAnneau1(Equipement anneau) {
    Equipement desequipe = equipementAnneau1;

    equipementAnneau1 = anneau;

    return desequipe;
}


Equipement Heros::equipeAnneau2(Equipement anneau) {
    Equipement desequipe = equipementAnneau2;

    equipementAnneau2 = anneau;

    return desequipe;
}


Equipement Heros::equipe(Equipement eq, int i) {
    if (eq.getType() == 1) {
        return equipeCasque(eq);
    }
    if (eq.getType() == 2) {
        return equipeTorse(eq);
    }
    if (eq.getType() == 3) {
        return equipeGants(eq);
    }
    if (eq.getType() == 4) {
        return equipeJambes(eq);
    }
    if (eq.getType() == 5) {
        return equipeBottes(eq);
    }
    if (eq.getType() == 6) {
        if (i == 1) {
            return equipeAnneau1(eq);
        }
        else {
            return equipeAnneau2(eq);
        }
    }
    if (eq.getType() >= 10) {
        if (eq.getType() == 11 && equipementArmeDroite.getType() == 11 && equipementArmeGauche.getType() == 11) {
            return eq;
        }
        if (i == 1) {
            return equipeArmeDroite(eq);
        }
        else {
            return equipeArmeGauche(eq);
        }
    }
}


Equipement Heros::equipe(Equipement eq) {
    return equipe(eq, 0);
}


Attaque::Attaque(std::vector<Imagine::Coords<2> > zone, int power) {
    zoneInfluence = zone;
    puissance = power;
}


void Attaque::zone(Case *carte, Unite u, bool b) {
    int caseHeros = u.getCase();
    for (int i = 0; i < zoneInfluence.size(); ++i) {
        if (caseHeros + zoneInfluence[i].y() * NbCase > 0 && caseHeros + zoneInfluence[i].y() * NbCase &&
            (caseHeros / NbCase == (caseHeros + zoneInfluence[i].x()) / NbCase)) {
            carte[caseHeros + zoneInfluence[i].x() + zoneInfluence[i].y() * NbCase].brillanceOnOff(b);
        }
    }
}


int Attaque::getPuissance() {
    return puissance;
}
