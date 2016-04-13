#include "carte.h"


void Case::Heros(){
    heros =! heros;
}


void Case::Brillance(){
    brillance =! brillance;
}


Case::Case(int x1, int y1, TypeCase tc){
    x = x1;
    y = y1;
    taille = Taille;
    heros = false;
    brillance = false;
    type = tc;
}
