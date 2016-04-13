#include "carte.h"


TypeCase::TypeCase(int dep, std::string desc, Imagine::Color img){
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


void Case::Heros(){
    heros =! heros;
}


void Case::Brillance(){
    brillance =! brillance;
}


void Case::Affiche(){
    Imagine::fillRect(x, y, Taille, Taille, type.Image());
    if (brillance){
        Imagine::drawRect(x, y, Taille, Taille, Imagine::BLACK);
    }
}
