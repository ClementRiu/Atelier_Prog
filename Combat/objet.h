#ifndef OBJET_H
#define OBJET_H

#include <stdlib.h>
#include <cstdlib>
#include <iostream>


const int NB_RES = 6;
const int NB_DEG_PHY = 3;


class Heros;


class Objet {
    std::string nom;
    std::string type;
public:
    Objet();

    Objet(const Objet& o);

    Objet(std::string nom_);

    bool operator==(const Objet &B) const;

    std::string getNom();

    virtual void equiper(Heros *h);
};


const Objet nul("NUL");


class Equipement : public Objet {
    int type;

    int PV;
    int mana;
    int force;
    int defense;
    int dexterite;
    int initiative;

    float PDep;

public:
    Equipement();

    Equipement(const Equipement &eq);

    Equipement(std::string nom_);

    int getType();
};


class Casque : public Equipement {
public:
    Casque();

    Casque(std::string nom_);

    virtual void equiper(Heros *h);
};


class Anneau : public Equipement {
public:
    virtual void equiper(Heros *h);
};


class Gants : public Equipement {
public:
    virtual void equiper(Heros *h);
};


class Jambes : public Equipement {
public:
    virtual void equiper(Heros *h);
};


class Bottes : public Equipement {
public:
    virtual void equiper(Heros *h);
};


class Arme : public Equipement {
public:
    virtual void equiper(Heros *h);
};


class Torse : public Equipement {
public:
    virtual void equiper(Heros *h);
};


/*
class Arme : public Objet {
    int degat;
    int bonus_attaque;
    int bonus_defense;
    int type_de_degat;
public:
    //constructeurs
    Arme();

    Arme(int deg, int att, int def, int type);

    //accesseur
    int get_degat();

    int get_bonus_attaque();

    int get_bonus_defense();

    int get_type_de_degat();

    //setteurs
    void set_degat(int deg);

    void set_attaque(int att);

    void set_defense(int def);

    void set_type_de_degat(int type);
};

class Armure : public Objet {
    int bonus_defense;
    int bonus_resistance[NB_RES];// fonctionne en pourcentage
public:
    //constructeurs
    Armure();

    Armure(int def, int res[NB_RES]);

    //accesseurs
    int get_defense();

    int getbonus_resistance(int i);

    //setteurs
    void set_defense(int def);

    void set_bonus_resistance(int res[NB_RES]);
};
*/


#endif // OBJET_H
