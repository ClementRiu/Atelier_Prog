#ifndef CARTE_H
#define CARTE_H


#include <Imagine/Graphics.h>
#include <stdlib.h>
#include "unite.h"
#include "priorite.h"


const int Taille = 20;
const int NbCase = 30;
const int LargDroite = 3 * NbCase;
const int Separation = 20; // Separation entre la carte et la mini map


int numeroCase(int x, int y);


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
    Imagine::Color Image();

    // Accesseur au nombre de déplacement que coûte la case
    float NbDep() const;

};

// Classe definissant les cases de la carte
class Case {
    int x, y; // Position effective du coin haut gauche de la case
    int taille;
    bool occupe; // Variable indiquant si le heros est sur la case
    bool brillance; // Variable indiquant si la case est en surbrillance
    TypeCase type;
public:
    // Constructeur de la classe Case
    Case(int x1, int y1, TypeCase tc);

    // Constructeur vide de la classe Case
    Case();

    // Place le heros sur cette case s'il n'y etait pas et l'enleve s'il y etait
    void flagHeros();

    bool getOccupe() const;

    // Deplace et actualise la position du Heros sur la carte
    void deplaceHeros(Unite &h, Case &c);

    // Place la case en surbrillance, ou enleve la surbrillance selon le booleen et affiche la case
    void brillanceOnOff(bool flag);

    // Affiche la case
    void affiche(); // Cette methode devrait être const mais je n'arrive pas a le faire !!!!!
    // Accesseur au nombre de déplacement que coûte la case
    float NbDep() const;

    // Accesseur a la brillance de la case
    bool Brillance() const;

    // Algorithme de FastMarching pour mettre en surbrillance les cases autorisées au Heros
    void fastMarching(float dep, Case *carte, bool brillance, float &dep_restant, int case_a_atteindre);
};


#endif // CARTE_H
