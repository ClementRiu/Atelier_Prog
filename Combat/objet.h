#ifndef OBJET_H
#define OBJET_H

#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <typeinfo>
#include "../Gestion/carte.h"
#include "../Gestion/boutons.h"


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
const int ZoneBoutonArgent[4] = {0, (NbCase - 2) * Taille, 50, NbCase * Taille};
const int BoutonMilieu[2] = {180, width - 100};


class Heros;
class Ville;
class Unite;


class Mere {
    int prix; // A CHANGER
    std::string nom;
public:

    Mere();

    Mere(std::string nom_, int price);

    Mere(const Mere &m);

    std::string getNom() const;

    int getPrix() const;

    /**
     * Fonction qui crée un bouton vide si les deux objets ne sont pas du même type,
     * et crée un bouton au nom de l'objet sur lequel la méthode est appelée sinon
     * @param obj
     * @param xmin : utilisé pour le constructeur du bouton
     * @param ymin : utilisé pour le constructeur du bouton
     * @param xmax : utilisé pour le constructeur du bouton
     * @param ymax : utilisé pour le constructeur du bouton
     * @return un bouton vide ou un bouton au nom de l'objet sur lequel la méthode est appelée
     */
    Bouton creeBouton(Mere *obj, int xmin, int &ymin, int xmax, int &ymax);

    /**
     * Fonction équipant l'objet à un endroit différent en fonction du type (main si arme, etc)
     * @param h : héros sur lequel on équipe
     * @param droite : non utilisé pour l'instant, destiné pour équiper les objets en main droite ou main gauche
     */
    virtual void equiper(Heros *h, bool droite);

    virtual Mere *clone() const;

    virtual void afficheCarac();
};


class Objet : public Mere {
    std::string nom;
    std::string type;
public:
    Objet();

    Objet(std::string nom_, int price);

    /**
     * Vérifie l'égalité des objets en se basant sur leur nom, non utilisé pour l'instant
     * @param B
     * @return true si les deux noms sont identiques
     */
    bool operator==(const Objet &B) const;

    virtual Objet *clone() const;
};


class Inventaire {
    std::vector<Mere *> contenu;
public:
    Inventaire();

    Inventaire(const Inventaire &inventaire);

    /**
     * @return la taille du vecteur contenu
     */
    int taille() const;

    /**
     * Ajoute un objet dans l'inventaire
     * @param obj : objet ajouté
     */
    void ajoute(Mere *obj);

    /**
     * @return le pointeur sur l'objet numero i
     */
    Mere *get(int i);

    /**
     * Cette fonction ouvre un inventaire et permet d'effectuer différentes actions dedans.
     * @param boutonsCategories : vecteur de boutons de types comme "Arme", "Anneau"
     * @param classeObjets : Inventaire contenant des instances de chaque classe que l'on souhaite afficher dans l'inventaire
     * @param ville : ville à laquelle on veut accéder si jamais on veut accéder à une ville
     * @param unite : unité qui ouvre l'inventaire ou la ville
     * @param faire : pointeur de fonctions : soit pour acheter un objet, soit pour équiper un équipement
     * @param ressources : ressources du joueur qui possède l'unité unite
     */
    void ouvreInventaire(std::vector<Bouton> boutonsCategories, Inventaire classeObjets, Ville* ville,
                         Unite *unite, void (Unite::*faire)(Ville*, int, bool, int&), int& ressources);

    /**
     * Retire le i-ème objet de l'inventaire
     * @param i
     */
    void retire(int i);

    ~Inventaire();
};




class Equipement : public Objet {
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

    Equipement(std::string nom_, int price);

    /**
     * Remplit l'écran de blanc et affiche les caractéristiques de l'équipement
     */
    virtual void afficheCarac();
};


class Casque : public Equipement {
public:
    Casque();

    Casque(std::string nom_, int price);

    virtual void equiper(Heros *h, bool droite);

    virtual Casque *clone() const;
};


class Anneau : public Equipement {
public:
    Anneau();

    Anneau(std::string nom_, int price);

    virtual void equiper(Heros *h, bool droite);

    virtual Anneau *clone() const;
};


class Gants : public Equipement {
public:
    Gants();

    Gants(std::string nom_, int price);

    virtual void equiper(Heros *h, bool droite);

    virtual Gants *clone() const;
};


class Jambes : public Equipement {
public:
    Jambes();

    Jambes(std::string nom_, int price);

    virtual void equiper(Heros *h, bool droite);

    virtual Jambes *clone() const;
};


class Bottes : public Equipement {
public:
    Bottes();

    Bottes(std::string nom_, int price);

    virtual void equiper(Heros *h, bool droite);

    virtual Bottes *clone() const;
};


class Arme : public Equipement {
public:
    Arme();

    Arme(std::string nom_, int price);

    virtual void equiper(Heros *h, bool droite);

    virtual Arme *clone() const;
};


class Torse : public Equipement {
public:
    Torse();

    Torse(std::string nom_, int price);

    virtual void equiper(Heros *h, bool droite);

    virtual Torse *clone() const;
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
