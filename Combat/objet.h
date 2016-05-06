#ifndef OBJET_H
#define OBJET_H

#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include "typeinfo.h"
#include "../Gestion/carte.h"


const int NB_RES = 6;
const int NB_DEG_PHY = 3;
const int Police = 20;
const int EcartementLignesInventaire = 3 * Police; // Ecartement entre les lignes de l'inventaire
const int ZoneBoutonFerme[4] = {NbCase * Taille + Separation, Taille * (NbCase - 5),
                                NbCase * Taille + Separation + LargDroite, NbCase * Taille}; // Zone du bouton ferme
const int ZoneBoutonUp[4] = {NbCase * Taille + Separation, 0, NbCase * Taille + Separation + LargDroite,
                             LargDroite}; // Zone du bouton Up
const int ZoneBoutonDown[4] = {NbCase * Taille + Separation, LargDroite + 10,
                               NbCase * Taille + Separation + LargDroite, 2 * LargDroite + 10}; // Zone du bouton Down
const int BoutonMilieu[2] = {180, width - 100};


class Heros;
class Unite;


class Objet {
    std::string nom;
    std::string type;
public:
    Objet();

    Objet(std::string nom_);

    Objet(const Objet& o);

    bool operator==(const Objet &B) const;

    std::string getNom();

    // Fonction vide utile uniquement pour les equipements
    virtual void equiper(Heros *h, bool droite);

    // Fonction creeant un bouton vide si les 2 objets ne sont pas du meme type et
    // Creant un bouton au nom de l'objet sur lequel la methode est effectuee sinon
    Bouton creeBouton(Objet *obj, int xmin, int &ymin, int xmax, int &ymax);
};


// Fonction a modifier
// faire vien plutot de Unite
class Inventaire{
    std::vector<Objet*> contenu;
public:
    int taille();

    // Ajoute un objet dans l'inventaire
    void ajoute(Objet *obj);

    // renvoie le pointeur sur l'objet numero i
    Objet* get(int i);

    // Cette fonction ouvre un inventaire et sert a effectuer differentes actions dedans.
    // Voir unite.h pour avoir un exemple
    void ouvreInventaire(std::vector<Bouton> boutonsCategories, Inventaire classeObjets,
                                     Unite *unite, void (Unite::*faire)(int, bool));

    ~Inventaire();
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

    virtual void equiper(Heros *h, bool droite);
};


class Anneau : public Equipement {
public:
    Anneau();

    Anneau(std::string nom_);

    virtual void equiper(Heros *h, bool droite);
};


class Gants : public Equipement {
public:
    Gants();

    Gants(std::string nom_);

    virtual void equiper(Heros *h, bool droite);
};


class Jambes : public Equipement {
public:
    Jambes();

    Jambes(std::string nom_);

    virtual void equiper(Heros *h, bool droite);
};


class Bottes : public Equipement {
public:
    Bottes();

    Bottes(std::string nom_);

    virtual void equiper(Heros *h, bool droite);
};


class Arme : public Equipement {
public:
    Arme();

    Arme(std::string nom_);

    virtual void equiper(Heros *h, bool droite);
};


class Torse : public Equipement {
public:
    Torse();

    Torse(std::string nom_);

    virtual void equiper(Heros *h, bool droite);
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
