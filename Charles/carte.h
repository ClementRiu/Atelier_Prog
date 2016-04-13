#ifndef CARTE_H
#define CARTE_H

#include <Imagine/Graphics.h>
#include <stdlib.h>

const int Taille=20;


// Classe definissant les différents types de cases que l'on peut trouver
class TypeCase{
    int nb_dep;
    std::string description;
    Imagine::Color image; // Sera remplace par une image ulterieurement
public:

};


// Classe definissant les cases de la carte
class Case{
    int x, y;
    int taille;
    bool heros;
    bool brillance;
    TypeCase type;
public:
    // Constructeur de la classe Case
    Case(int x1, int y1, TypeCase tc);
    // Place le heros sur cette case s'il n'y etait pas et l'enleve s'il y etait
    void Heros();
    // Place la case en surbrillance s'il n'y etait pas et enleve la surbrillance sinon
    void Brillance();
};



#endif // CARTE_H
