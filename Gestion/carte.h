#ifndef CARTE_H
#define CARTE_H


#include <Imagine/Graphics.h>
#include <stdlib.h>
#include "priorite.h"
#include <Imagine/Images.h>
#include <bits/stl_deque.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>

const float INF = 1.0f / 0.0f; // Infini en float
const int Taille = 30;
const int NbCase = 20;
const int LargDroite = 3 * NbCase;
const int LargGauche = 0;
const int Separation = 20; // Separation entre la carte et la mini map
const int width = NbCase * Taille + Separation + LargDroite;
const int height = NbCase * Taille;
const std::string descVille = "Ville"; // Descrption de la case ville. Variable a ne par retirer sans regarder la fonction boutonAction


class Heros;
class Unite;
class Ville;
class Carte;


// Classe definissant les différents types de cases que l'on peut trouver
class TypeCase {
    float PDep; // Nombre de deplacements nécessaires pour aller sur cette case
    std::string description;
    Imagine::Color image; // Sera remplace par une image ulterieurement
public:
    // Constructeur de la classe TypeCase
    TypeCase(float dep, std::string desc, Imagine::Color img);

    // Constructeur vide de la classe TypeCase
    TypeCase();

    // Accesseur a l'image du type de la case
    Imagine::Color Image() const;

    // Accesseur au nombre de déplacement que coûte la case
    float NbDep() const;

    // Accesseur à la desctiprion de la case
    std::string Description() const;

    // affichage à modifier
    // Fonction qui créé une fenêtre pop un avec une question fermé et qui renvoie le résultat
    bool popUp(std::string question) const;

    virtual void action(Unite* h);

    virtual TypeCase *clone() const;

    // Cree des boutons où on pour choisir si l'on veut effecter l'action de la case ou non
    virtual bool boutonChoix();
};


class CaseVille : public TypeCase {
    Ville* ville;
public:
    CaseVille(std::string desc, Imagine::Color img, Ville* v);

    CaseVille();

    virtual void action(Unite* h);

    virtual CaseVille *clone() const;

    virtual bool boutonChoix();
};


class CaseCombat : public TypeCase {
public:
    CaseCombat(std::string desc, Imagine::Color img);

    CaseCombat();

    virtual CaseCombat *clone() const;

    virtual bool boutonChoix();
};


class CaseNormale : public TypeCase {
public:
    CaseNormale(float dep, std::string desc, Imagine::Color img);

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
    Case(int x1, int y1, TypeCase* tc);

    // Constructeur vide de la classe Case
    Case();

    Case(const Case &tuile);

    // Place le heros sur cette case
    void placeUnite(Unite* u);

    void retireUnite();

    bool getOccupe() const;

    // renvoie le pointeur de l'unité sur la case
    Unite* getPointeurUnite();

    //get temporaire à se débarasser !!
    int get(int i) const;

    // Place la case en surbrillance, ou enleve la surbrillance selon le booleen et affiche la case
    void brillanceOnOff(bool flag);

    // Affiche la case
    void affiche() const;

    // Accesseur au nombre de déplacement que coûte la case
    float NbDep() const;

    // Accesseur a la brillance de la case
    bool Brillance() const;

    // Change le booleen utileChemin
    void setChemin();

    bool getChemin() const;

    // Renvoie le plus proche voisin en surbrillance, ou qui a le numéro numcase
    int plusProcheVoisineBrillante(int x1, int y1, Carte &carte, int numcase) const;

    // Renvoie les numéros des cases voisines (Attention, il peut y en avoir que 3 ou 2 ...) dans l'ordre du plus proche
    // du point (x, y) au plus éloigné
    std::vector<int> casesVoisines(int x1, int y1) const;

    // Algorithme de FastMarching pour mettre en surbrillance les cases autorisées au Heros
    std::vector<std::vector<int> > fastMarching(float dep, Carte &carte, bool brillance, float &dep_restant,
                                                int case_a_atteindre, std::vector< Imagine::Coords<2> > &vecCaseBrillante);

    // Renvoie l'image correspondant a la case (type a changer pour l'affichage)
    Imagine::Color getImage() const;

    // Renvoie le texte correspondant a la case
    std::string getDescription() const;

    // Permet de choisir si l'on veut effectuer l'action relative à la case
    bool boutonChoix() const;

    // Fais l'action sur la case s'il y en a une A CHANGER
    void action(Unite* u);

    ~Case();
};


class Carte {
    Case carte[NbCase * NbCase];
public:
    //Construit une carte aléatoire (ou on aimerait que ça le fasse)
    Carte(int inutilePourLInstant);

    // Construit une carte de base
    Carte(Ville* v);

    // affiche la carte
    void affiche() const;

    // Permer d'accéder à carte[i]
    Case &operator[](int i);

    // Permet d'accéder à carte[i] en const
    Case get(int i) const;
};


// Renvoie le numero de la case associee au pixel (x, y) et renvoie -1 si aucune case n'est associee
int numeroCase(int x, int y);

// Fonction renvoyant en référence dans x et y la position d'un clic et affichant les cases survolees
void clic(int &x, int &y, Carte &carte, std::vector<std::vector<int> > differentsChemins, int numcase);


#endif // CARTE_H
