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
};

// Classe definissant les cases de la carte
class Case{
    int x,y;
    int taille;
    bool heros;
    bool brillance;
    TypeCase type;

};



#endif // CARTE_H
