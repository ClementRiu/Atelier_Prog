#pragma once

const int TAILLE_ARMEE = 6;

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
};


class Sbire : public Unite {
    int nombre;
};


class Armee{
    Sbire sbireArmee[TAILLE_ARMEE];
};


class Heros : public Unite {
    Armee ArmeeHeros;

    int niveau;
    int exp;

public:
    Heros(int dep);
};


