#include "unite.h"
#include <iostream>

//attaque de base
Attaque::Attaque() {
    zoneInfluence.push_back(portee10);
    zoneInfluence.push_back(portee01);
    zoneInfluence.push_back(portee_10);
    zoneInfluence.push_back(portee0_1);

    puissance = 10;
}

//vérifier que la copie de vectors fonctionne bien !!
Attaque::Attaque(const Attaque &att) {
    zoneInfluence = att.zoneInfluence;
    puissance = att.puissance;
}

Attaque::Attaque(std::vector<Imagine::Coords<2> > zone, int power) {
    zoneInfluence = zone;
    puissance = power;
}


void Attaque::zone(Case *carte, bool b, int caseUnite) {
    for (int i = 0; i < zoneInfluence.size(); ++i) {
        if (caseUnite + zoneInfluence[i].y() * NbCase > 0 && caseUnite + zoneInfluence[i].y() * NbCase &&
            (caseUnite / NbCase == (caseUnite + zoneInfluence[i].x()) / NbCase)) {
            carte[caseUnite + zoneInfluence[i].x() + zoneInfluence[i].y() * NbCase].brillanceOnOff(b);
        }
    }
}


int Attaque::getPuissance() {
    return puissance;
}

Unite::Unite() {
    PDep = 8;
    numcase = 0;
}

Unite::Unite(const Unite &unit) {
    PV = unit.PV;
    PVMax = unit.PVMax;
    mana = unit.mana;
    manaMax = unit.manaMax;
    force = unit.force;
    dexterite = unit.dexterite;
    initiative = unit.initiative;
    numcase = unit.numcase;
    PDep = unit.PDep;
    PDepMax = unit.PDepMax;

    for (int i = 0; i++; i < NB_DEG_PHY) {
        defensePhy[i] = unit.defensePhy[i];
    }

    for (int i = 0; i++; i < NB_RES) {
        defenseMag[i] = unit.defenseMag[i];
    }

    for (int i = 0; i++; i < NB_MAX_ATTAQUES) {
        competences[i] = unit.competences[i];
    }
}

Unite::Unite(float dep, int num) {
    PDep = dep;
    numcase = num;
    PDepMax = dep;
}


void Unite::deplacement(Case *carte) {
    int x1, y1;
    float dep = PDep;
    if (dep > 0) {
        // On met la variable deplacement juste parce qu'on est oblige, elle n'est pas modifiee ici
        afficheCaseDisponibleOnOff(carte, true, dep, 0);
        do {
            clic(x1, y1, carte);

            //Si le joueur clique sur l'unité on annule la phase de déplacement et on retourne au choix d'action
            if (numeroCase(x1, y1) == numcase) {
                afficheCaseDisponibleOnOff(carte, false, dep, numeroCase(x1, y1));
                return;
            }
        } while (numeroCase(x1, y1) == -1 || !carte[numeroCase(x1, y1)].Brillance());


        afficheCaseDisponibleOnOff(carte, false, dep, numeroCase(x1, y1));
        deplaceVersCase(carte[numeroCase(x1, y1)], carte[numcase]);
        PDep = dep;
    }
}

// Fonction simple permettant d'afficher les cases disponibles pour le Heros, ou de les enlever
void Unite::afficheCaseDisponibleOnOff(Case *carte, bool b, float &deplacement, int case_a_atteindre) {
    carte[numcase].fastMarching(PDep, carte, b, deplacement, case_a_atteindre);
}

void Unite::deplaceVersCase(Case &c2, Case &c1) {
    if (!c2.getOccupe()) {
        c1.flagHeros();
        c2.flagHeros();
        c1.affiche();
        c2.affiche();
        numcase = numeroCase(c2.get(0), c2.get(1));
    }
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


void Unite::setDepMax(float depMax) {
    PDepMax = depMax;
}


float Unite::getDepMax() const {
    return PDepMax;
}


Heros::Heros(float dep, int num) : Unite(dep, num) {
}

Heros::Heros(const Heros &h) : Unite(h) {
    niveau = h.niveau;
    exp = h.exp;
    ArmeeHeros = h.ArmeeHeros;
}


//à implémenter
void Unite::prendDommage(int attRecue) {
    std::cout << "à implémenter !" << std::endl;
}

void Unite::setAttaque(Attaque att, int i) {
    competences[i] = att;
}

bool Unite::estVivant() {
    if (PV <= 0) {
        return false;
    }
    return true;
}


void Unite::tour(Case carte[NbCase * NbCase], std::vector<Unite> &unites, Bouton boutonFinTour) {
    bool tourContinue = true;
    int x = 0, y = 0;

    while (tourContinue) {
        int choix = -1;

        choisir(choix, x, y);

        if (boutonFinTour.boutonActive(x, y)) {
            break;
        }

        if (choix == Imagine::KEY_NUMPAD0) {
            deplacement(carte);
        }
        if (choix == Imagine::KEY_NUMPAD1) {
            competences[1].zone(carte, true, getCase());
            attaque(competences[0], carte, unites);
            competences[1].zone(carte, false, getCase());
            PDep = 0;
        }
        if (PDep == 0 || choix == Imagine::KEY_SPACE) {
            tourContinue = false;
        }
    }
    finTourCombat(unites);
}


void Unite::action(Attaque att, Unite &u) {
    // A MODIFIER
    u.prendDommage(att.getPuissance());
}


void Unite::attaque(Attaque attq, Case *carte, std::vector<Unite> &unites) {
    int x1, y1, u2 = 0;

    do {
        clic(x1, y1, carte);
    } while (numeroCase(x1, y1) < 0 || !carte[numeroCase(x1, y1)].Brillance());
    //CETTE PARTIE DU CODE EST ATROCE !!!!!!!!
    if (carte[numeroCase(x1, y1)].getOccupe()) {
        while (unites[u2].getCase() != numeroCase(x1, y1)) {
            u2 += 1;
        }
        action(attq, unites[u2]);
    }
}

Sbire::Sbire() {

}

Sbire::Sbire(const Sbire &s) {

}

Armee::Armee() {

}

Armee::Armee(std::vector<Sbire> sbires) {
    for (int i = 0; i < TAILLE_ARMEE; i++) {
        sbireArmee[i] = sbires[i];
    }
}

Armee::Armee(const Armee &a) {
    for (int i = 0; i < TAILLE_ARMEE; i++) {
        sbireArmee[i] = a.sbireArmee[i];
    }
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



