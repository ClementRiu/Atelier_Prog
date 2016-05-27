#pragma once

#include <Imagine/Graphics.h>
#include <stdlib.h>
#include "priorite.h"
#include <Imagine/Images.h>
#include <bits/stl_deque.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include "constante.h"

/*
class CarteduMonde;
class Case_Graph {
private:
    const char *nom;  // Nom de la case.
    std::string description;  // Texte à afficher sur le côté.
    std::string nom_image;    // Nom de l'image.
    Imagine::Image<Imagine::Color> frame;   // Image de la case.
public:
    //Constructeur par défaut.
    Case_Graph();

    //Assesseur en lecture de l'attribut nom.
    const char *get_nom();

    //Assesseur en lecture de l'attribut description.
    std::string get_description();

    //Assesseur en lecture de l'attribut nom_image.
    std::string get_nom_image();

    //Assesseur en écriture de l'attribut nom.
    void set_nom(char *nom_voulu);

    //Assesseur en écriture de l'attribut description.
    void set_description(std::string description_voulue);

    //Assesseur en écriture de l'attribut nom_image.
    void set_nom_image(const char *nom_image_voulue);

    //Assesseur en écriture de l'attribut frame.
    void set_frame(const char *nom_image_voulue);

    //Méthode qui modifie l'intégralité des paramètres de la case.
    void set_Case_Graph(char *nom_voulu, std::string description_voulue, const char *name);

    void affiche(int x, int y, CarteduMonde carte) const;
};

const int Taille = 30;
const int NbCase = 20;
const int LargDroite = 3 * NbCase;
const int LargGauche = 0;
const int Separation = 20; // Separation entre la carte et la mini map
const int width = NbCase * Taille + Separation + LargDroite;
const int height = NbCase * Taille;
const std::string descVille = "La ville, le doux foyer"; // Descrption de la case ville. Variable a ne par retirer sans regarder la fonction boutonAction


class Heros;
class Unite;
class Ville;
class Carte;


// Classe definissant les différents types de cases que l'on peut trouver
class TypeCase {
    float PDep; // Nombre de deplacements nécessaires pour aller sur cette case
    std::string description;
    Case_Graph case_aff; //Objet graphique.
public:
    // Constructeur de la classe TypeCase
    TypeCase(const float dep, const std::string desc);


    // Constructeur vide de la classe TypeCase
    TypeCase();

    //Assesseur en écriture de l'attribut case_aff.
    void set_case_aff(char *nom_voulu, std::string description_voulue, const char *name);


    // Affiche la case
    void affiche(int x, int y, CarteduMonde carte) const;

    //Assesseur en lecture de l'attribute case_aff.
    Case_Graph get_case_aff();

    // Accesseur au nombre de déplacement que coûte la case
    float NbDep() const;

    // Accesseur à la desctiprion de la case
    std::string Description() const;

    // affichage à modifier
    // Fonction qui créé une fenêtre pop un avec une question fermé et qui renvoie le résultat
    bool popUp(const std::string question) const;

    virtual void action(Unite* h);

    virtual TypeCase *clone() const;

    // Cree des boutons où on pour choisir si l'on veut effecter l'action de la case ou non
    virtual bool boutonChoix();
};


class CaseVille : public TypeCase {
    Ville* ville;
public:
    CaseVille(const std::string desc, Ville* v, int camp);

    CaseVille();

    virtual void action(Unite* h);

    virtual CaseVille *clone() const;

    virtual bool boutonChoix();
};


class CaseCombat : public TypeCase {
public:
    CaseCombat(const std::string desc, const char *nom);

    CaseCombat();

    virtual CaseCombat *clone() const;

    virtual bool boutonChoix();
};


class CaseNormale : public TypeCase {
public:
    CaseNormale(const float dep, const std::string desc, const char *nom);

    CaseNormale();

    virtual CaseNormale *clone() const;
};


// Classe definissant les cases de la carte
class Case {
    int x, y; // Position effective du coin haut gauche de la case
    int taille;
    Unite* pointeurUnite;
    bool brillance; // Variable indiquant si la case est en surbrillance
    bool utileChemin; // Variable indiquant si la case sert actuellement a montrer un chemin pour le Heros
    TypeCase *type;

public:
    // Constructeur de la classe Case
    Case(const int x1, const int y1, TypeCase* tc);

    // Constructeur vide de la classe Case
    Case();

    //Assesseur en lecture du nom de l'image, attribut de case_aff.
    std::string get_nom_image();

    //Assesseur en lecture du nom de l'image, attribut de case_aff.
    std::string get_nom();

    Case(const Case &tuile);

    //Set la case.
    void set_case_aff(char *nom_voulu, std::string description_voulue, const char *name);

    // Place le heros sur cette case s'il n'y etait pas et l'enleve s'il y etait
    void flagHeros(Unite* u);

    void retireUnite();

    bool getOccupe() const;

    // renvoie le pointeur de l'unité sur la case
    Unite* getUnite();

    //get temporaire à se débarasser !!
    int get(const int i) const;

    // Place la case en surbrillance, ou enleve la surbrillance selon le booleen et affiche la case
    void brillanceOnOff(const bool flag);


    //Affiche les chemins et la surbrillance.
    void affiche_chemin();

    // Accesseur au nombre de déplacement que coûte la case
    float NbDep() const;

    // Accesseur a la brillance de la case
    bool Brillance() const;

    // Change le booleen utileChemin
    void setChemin();

    bool getChemin() const;

    // Renvoie le plus proche voisin en surbrillance, ou qui a le numéro numcase
    int plusProcheVoisineBrillante(const int x1, const int y1, CarteduMonde &carte, const int numcase) const;

    // Renvoie les numéros des cases voisines (Attention, il peut y en avoir que 3 ou 2 ...) dans l'ordre du plus proche
    // du point (x, y) au plus éloigné
    std::vector<int> casesVoisines(const int x1, const int y1) const;

    // Algorithme de FastMarching pour mettre en surbrillance les cases autorisées au Heros
    std::vector<std::vector<int> > fastMarching(const float dep, CarteduMonde &carte, const bool brillance, float &dep_restant,
                                                const int case_a_atteindre);


    // Renvoie l'image correspondant a la case (type a changer pour l'affichage)
    Imagine::Color getImage() const;


    // Affiche la case
    void affiche(CarteduMonde carte) const;

    // Renvoie le texte correspondant a la case
    std::string getDescription() const;

    // Permet de choisir si l'on veut effectuer l'action relative à la case
    bool boutonChoix() const;

    // Fais l'action sur la case s'il y en a une A CHANGER
    void action(Unite* u);

    ~Case();
};

/*
class Carte {
    Case carte[NbCase * NbCase];
public:
    //Construit une carte aléatoire (ou on aimerait que ça le fasse)
    Carte(int inutilePourLInstant);

    // Construit une carte de base
    Carte(Ville* v);

    // affiche la carte
    void affiche();



    // Permer d'accéder à carte[i]
    Case &operator[](const int i);
};



// Renvoie le numero de la case associee au pixel (x, y) et renvoie -1 si aucune case n'est associee
int numeroCase(const int x, const int y);

// Fonction renvoyant en référence dans x et y la position d'un clic et affichant les cases survolees
void clic(int &x, int &y, CarteduMonde &carte, std::vector<std::vector<int> > differentsChemins, int numcase);


*/