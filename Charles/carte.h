#ifndef CARTE_H
#define CARTE_H


#include <Imagine/Graphics.h>
#include <stdlib.h>


const int Taille = 20;
const int LargDroite = 50;
const int NbCase = 10 ;
const int Separation = 20; // Separation entre la carte et la mini map


// Classe definissant les différents types de cases que l'on peut trouver
class TypeCase{
    float nb_dep; // Nombre de deplacements nécessaires pour aller sur cette case
    std::string description;
    Imagine::Color image; // Sera remplace par une image ulterieurement
public:
    // Constructeur de la classe TypeCase
    TypeCase(float dep, std::string desc, Imagine::Color img);
    // Constructeur vide de la classe TypeCase
    TypeCase();
    // Accesseur a l'image du type de la case
    Imagine::Color Image();
};


// Classe definissant les cases de la carte
class Case{
    int x, y;
    int taille;
    bool heros; // Variavle indiquant si le heros est sur la case
    bool brillance; // Variable indiquant si la case est en surbrillance
    TypeCase type;
public:
    // Constructeur de la classe Case
    Case(int x1, int y1, TypeCase tc);
    // Constructeur vide de la classe Case
    Case();
    // Place le heros sur cette case s'il n'y etait pas et l'enleve s'il y etait
    void Heros();
    // Place la case en surbrillance s'il n'y etait pas et enleve la surbrillance sinon
    void Brillance();
    // Affiche la case
    void Affiche();
};


#endif // CARTE_H
