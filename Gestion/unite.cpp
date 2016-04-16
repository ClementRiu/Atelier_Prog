#include "unite.h"
#include <iostream>

Unite::Unite() {
    PDep = 8;
    numcase = 0;
}

Unite::Unite(int dep, int num) {
    PDep = dep;
    numcase = num;
}


int Unite::getCase() const {
    return numcase;
}


void Unite::setCase(int num) {
    numcase = num;
}


int Unite::getDep() const {
    return PDep;
}


Heros::Heros(int dep, int num) : Unite(dep, num) {
}

//à implémenter
void Unite::prendDommage(int attRecue) {
    std::cout << "à implémenter !" << std::endl;
}

bool Unite::estVivant() {
    if (PV <= 0) {
        return false;
    }
    return true;
}


//à implémenter !!
Objet Heros::equipe(Objet equipement){

}
