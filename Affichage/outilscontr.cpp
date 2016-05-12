#include "outilscontr.h"

//Permet de déplacer l'écran au clavier.
void mouvement_ecran(CarteduMonde &carte) {
    int directiondem = 0;
    Imagine::Event e;
    getEvent(0, e);
    if (e.type == Imagine::EVT_KEY_ON) {
        directiondem = e.key;
        carte.deplace(directiondem);
    }
}