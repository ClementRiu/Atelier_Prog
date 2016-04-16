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


float TypeCase::NbDep() const{
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


bool Case::getOccupe() const {
    return occupe;
}


void Case::deplaceHeros(Unite &h, Case &c) {
    if (!c.getOccupe()){
        this->flagHeros();
        c.flagHeros();
        this->affiche();
        c.affiche();
        h.setCase(numeroCase(c.x, c.y));
    }
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


float Case::NbDep() const {
    return type.NbDep();
}


bool Case::Brillance() const {
    return brillance;
}

void Case::fastMarching(float dep, Case *carte, bool brillance) {
    int num_case=numeroCase(x,y);
    FilePriorite F;
    CaseDist depart(num_case, dep);
    F.push(depart);
    while (!F.empty()) {
        CaseDist c = F.pop();
        for (int i = -1; i <= 1; i = i + 2) {
            for (int j = 1; j <= NbCase; j = j + NbCase - 1) {
                if (c.getNum() + i * j >= 0 && c.getNum() + i * j < NbCase * NbCase &&
                    ((c.getNum() + i * j) % NbCase != 0 || c.getNum() % NbCase != NbCase - 1) &&
                    ((c.getNum() + i * j) % NbCase != NbCase - 1 || c.getNum() % NbCase != 0) &&
                    c.getDep() - carte[c.getNum() + i * j].NbDep() >= 0 &&
                    carte[c.getNum() + i * j].Brillance() != brillance &&
                    !carte[c.getNum() + i * j].getOccupe()) {
                    carte[c.getNum() + i * j].brillanceOnOff(brillance);
                    CaseDist c2(c.getNum() + i * j, c.getDep() - carte[c.getNum() + i * j].NbDep());
                    F.push(c2);
                }
            }
        }
    }
}

