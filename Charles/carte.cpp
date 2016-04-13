#include "carte.h"


TypeCase::TypeCase(float dep, std::string desc, Imagine::Color img){
    nb_dep = dep;
    description = desc;
    image = img;
}


TypeCase::TypeCase(){
}


Imagine::Color TypeCase::Image(){
    return image;
}


Case::Case(int x1, int y1, TypeCase tc){
    x = x1;
    y = y1;
    taille = Taille;
    heros = false;
    brillance = false;
    type = tc;
}


Case::Case(){
}


void Case::Heros(){
    heros =! heros;
}


void Case::Brillance(){
    brillance =! brillance;
}


void Case::Affiche(){
    Imagine::fillRect(x, y, Taille - 1, Taille - 1, type.Image());
    if (brillance){
        Imagine::drawRect(x, y, Taille - 1, Taille - 1, Imagine::BLACK);
    }
    int taillemax = LargDroite/NbCase;
    Imagine::fillRect(x * taillemax / Taille + Taille * NbCase + Separation, y * taillemax / Taille, taillemax, taillemax, type.Image());
    std::cout << taillemax;
}
