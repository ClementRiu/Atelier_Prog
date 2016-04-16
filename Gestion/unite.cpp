#include "unite.h"
#include <iostream>

Unite::Unite() {
    PDep = 8;
    numcase = 0;
}

Unite::Unite(float dep, int num) {
    PDep = dep;
    numcase = num;
    PDepMax = dep;
}


int Unite::getCase() const {
    return numcase;
}


void Unite::setCase(int num) {
    numcase = num;
}


float Unite::getDep() const {
    return PDep;
}


void Unite::setDep(float dep) {
    PDep = dep;
}


float Unite::getDepMax() const {
    return PDepMax;
}


Heros::Heros(float dep, int num) : Unite(dep, num) {
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
