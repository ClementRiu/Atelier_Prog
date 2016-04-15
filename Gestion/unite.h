#pragma once

#include "../Combat/objet.h"

const int TAILLE_ARMEE = 6;
const int TAILLE_INVENTAIRE = 10;

class Unite {
    //caractéristiques de l'unité

    int PV;
    int PVMax;
    int mana;
    int manaMax;
    int force;
    int defense;
    int initiative;

    int numcase;
    int PDep;
    int PDepMax;


public:
    Unite();

    Unite(int dep);

    int getCase() const;

    void setCase(int num);

    int getDep() const;

    void prendDommage(int att); //à implémenter avec formule adaptée
    bool estVivant();
};


class Sbire : public Unite {
    int nombre;
};


class Armee {
    Sbire sbireArmee[TAILLE_ARMEE];
};


class Heros : public Unite {
    Armee ArmeeHeros;

    int niveau;
    int exp;

    Objet inventaire[TAILLE_INVENTAIRE];
    Objet equipeCasque;
    Objet equipeArmeDroite;
    Objet equipeArmeGauche;
    Objet equipeTorse;
    Objet equipeGants;
    Objet equipeJambes;
    Objet equipeBottes;
    Objet equipeAnneau1;
    Objet equipeAnneau2;

public:
    Heros(int dep);

    //à implémenter !!
    Objet equipe(Objet equipement);
};


