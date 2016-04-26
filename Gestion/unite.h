#pragma once

#include "../Combat/objet.h"
#include <Imagine/Graphics.h>
#include "carte.h"


const int TAILLE_ARMEE = 6;
const int TAILLE_INVENTAIRE = 10;

class Attaque {
    std::vector<Imagine::Coords<2> > zoneInfluence;
    int puissance;
public:
    Attaque(std::vector<Imagine::Coords<2> > zone, int power);

    // Affiche la zone d'influence de l'attaque
    void zone(Case *carte, Unite u, bool b);

    int getPuissance();
};

void attaque(Attaque attq, Case *carte, std::vector<Unite> &unites, int u);

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

    int orientation; //voir manuel, possible de changer

    int typeDegats;

public:
    Unite();

    Unite(float dep, int num);

    void changeOrientation(int i);

    int getCase() const;

    void setCase(int num);

    float getDep() const;

    void setDep(float dep);

    float getDepMax() const;

    void prendDommage(int att); //à implémenter avec formule adaptée
    bool estVivant();

    // Action que fait l'attaque, A COMPLETER (enlève des points de vie, pousse des ennemis pour des sous classes d'attaques...)
    void action(Attaque a, Unite &u);
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

    Equipement equipe(Equipement eq, int i);

    Equipement equipeCasque(Equipement casque);

    Equipement equipeArmeDroite(Equipement arme);

    Equipement equipeArmeGauche(Equipement arme);

    Equipement equipeTorse(Equipement torse);

    Equipement equipeGants(Equipement gants);

    Equipement equipeJambes(Equipement jambes);

    Equipement equipeBottes(Equipement bottes);

    Equipement equipeAnneau1(Equipement anneau);

    Equipement equipeAnneau2(Equipement anneau);
};






