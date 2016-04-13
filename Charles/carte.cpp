#include "carte.h"

int NumeroCase(int x, int y){
    return ((y / Taille) * NbCase + x / Taille);
}


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


int Heros::GetCase() const{
    return numcase;
}


void Heros::SetCase(int num){
    numcase = num;
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


void Case::FlagHeros(){
    heros = !heros;
}



void Case::DeplaceHeros(Heros &h, Case &c){
    this->FlagHeros();
    c.FlagHeros();
    this->Affiche();
    c.Affiche();
    h.SetCase(NumeroCase(c.x, c.y));
}


void Case::Brillance(){
    brillance = !brillance;
}


void Case::Affiche(){
    Imagine::fillRect(x, y, Taille - 1, Taille - 1, type.Image());
    if (brillance){
        Imagine::drawRect(x, y, Taille - 1, Taille - 1, Imagine::BLACK);
    }
    int taillemax = LargDroite/NbCase;
    Imagine::fillRect(x * taillemax / Taille + Taille * NbCase + Separation, y * taillemax / Taille, taillemax, taillemax, type.Image());
    if (heros){
        Imagine::fillRect(x + Taille / 4, y + Taille / 4, (Taille - 1) / 2, (Taille - 1) / 2, Imagine::BLACK);
        Imagine::fillRect(x * taillemax / Taille + Taille * NbCase + Separation, y * taillemax / Taille, taillemax, taillemax, Imagine::BLACK);
    }
}
