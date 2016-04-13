#ifndef CARTE_H
#define CARTE_H


#include <Imagine/Graphics.h>
#include <stdlib.h>


const int Taille = 20;
const int LargDroite = 50;
const int NbCase = 10 ;
const int Separation = 20; // Separation entre la carte et la mini map


int NumeroCase(int x, int y);


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
    // Accesseur au nombre de déplacement que coûte la case
    float NbDep();

};

// Classe definissant le heros
class Heros{
    int numcase;
    int nb_dep;
public:
    // Constructeur de la classe Heros
    Heros(int dep);
    // Accesseur a la case du heros
    int GetCase() const;
    // setteur de la case du heros
    void SetCase(int num);
    // Accesseur a la case du heros
    int GetDep() const;
};

// Classe definissant les cases de la carte
class Case{
    int x, y; // Position effective du coin haut gauche de la case
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
    void FlagHeros();
    // Deplace et actualise la position du Heros sur la carte
    void DeplaceHeros(Heros &h, Case &c);
    // Place la case en surbrillance, ou enleve la surbrillance selon le booleen
    void BrillanceOnOff(bool flag);
    // Affiche la case
    void Affiche(); // Cette methode devrait être const mais je n'arrive pas a le faire !!!!!
    // Accesseur au nombre de déplacement que coûte la case
    float NbDep();
    // Accesseur a la brillance de la case
    bool Brillance();
};


#endif // CARTE_H
