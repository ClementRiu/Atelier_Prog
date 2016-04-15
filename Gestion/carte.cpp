#include "carte.h"


int numeroCase(int x, int y) {
    return ((y / Taille) * NbCase + x / Taille);
}


TypeCase::TypeCase(float dep, std::string desc, Imagine::Color img) {
    PDep = dep;
    description = desc;
    image = img;
}


TypeCase::TypeCase() {
}


Imagine::Color TypeCase::Image() {
    return image;
}


float TypeCase::NbDep() {
    return PDep;
}


Case::Case(int x1, int y1, TypeCase tc) {
    x = x1;
    y = y1;
    taille = Taille;
    occupe = false;
    brillance = false;
    type = tc;
}


Case::Case() {
}


void Case::flagHeros() {
    occupe = !occupe;
}


void Case::deplaceHeros(Heros &h, Case &c) {
    this->flagHeros();
    c.flagHeros();
    this->affiche();
    c.affiche();
    h.setCase(numeroCase(c.x, c.y));
}


void Case::brillanceOnOff(bool flag) {
    brillance = flag;
    this->affiche();
}


void Case::affiche() {
    Imagine::fillRect(x, y, Taille - 1, Taille - 1, type.Image());
    if (brillance) {
        Imagine::drawRect(x, y, Taille - 2, Taille - 2, Imagine::BLACK);
    }
    int taillemax = LargDroite / NbCase;
    Imagine::fillRect(x * taillemax / Taille + Taille * NbCase + Separation, y * taillemax / Taille, taillemax,
                      taillemax, type.Image());
    if (occupe) {
        Imagine::fillRect(x + Taille / 4, y + Taille / 4, (Taille - 1) / 2, (Taille - 1) / 2, Imagine::BLACK);
        Imagine::fillRect(x * taillemax / Taille + Taille * NbCase + Separation, y * taillemax / Taille, taillemax,
                          taillemax, Imagine::BLACK);
    }
}


float Case::NbDep() {
    return type.NbDep();
}


bool Case::Brillance() {
    return brillance;
}
