#pragma once

#include "../Combat/objet.h"

const int TAILLE_ARMEE = 6;
const int TAILLE_INVENTAIRE = 10;

class Unite {
    //caractéristiques de l'unité
    float PV;
    float PVMax;
    float mana;
    float manaMax;
    float force;
    float defensePhy[NB_DEG_PHY];
    float defenseMag[NB_RES];
    float dexterite;
    float initiative;

    int numcase;
    float PDep;
    float PDepMax;

    int typeDegats;

public:
    Unite();

    Unite(float dep, int num);

    int getCase() const;

    void setCase(int num);

    float getDep() const;

    void setDep(float dep);

    float getDepMax() const;

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
    Equipement equipementCasque;
    Equipement equipementArmeDroite;
    Equipement equipementArmeGauche;
    Equipement equipementTorse;
    Equipement equipementGants;
    Equipement equipementJambes;
    Equipement equipementBottes;
    Equipement equipementAnneau1;
    Equipement equipementAnneau2;

public:
    Heros(float dep, int num);

    //equipe appelle la méthode adéquate en fonction du type d'équipement
    Equipement equipe(Equipement eq);

    Equipement equipeCasque(Equipement casque);

    Equipement equipeArme(Equipement arme);

    Equipement equipeTorse(Equipement torse);

    Equipement equipeGants(Equipement gants);

    Equipement equipeJambes(Equipement jambes);

    Equipement equipeBottes(Equipement bottes);

    Equipement equipeAnneau(Equipement anneau);
};


