#pragma once

#include <Imagine/Graphics.h>
#include <stdlib.h>


class Batiment {
    bool construit;
    Imagine::Color image; // A remplacer par une image
    std::string description;
    int niveau;
    int camp;
public:
    // Affiche le Batiment cf Clement
    void affiche();
    // Fait monter la batiment de niveau
    void monteNiveau();
};


class Armurerie : public Batiment {

};


class Reserve : public Batiment {

};


class Eglise : public Batiment {

};
