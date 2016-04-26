#include "outilscontr.h"

/*
int Clavier() {
    Imagine::Event e;
    do {
        getEvent(0, e);
        if (e.type == Imagine::EVT_KEY_ON)
            return e.key;
    } while (e.type != Imagine::EVT_NONE);
    return 0;
}

void mouvement_ecran(CarteduMonde &carte) {
    int directiondem = 0;
    int pile_instruction = 0;
    int temps = 0;
    int x, y;
    while (pile_instruction < increment_mouv && temps < 10) {
        directiondem = Clavier();
        carte.deplace(directiondem);
        if (directiondem == Imagine::KEY_UP || directiondem == Imagine::KEY_DOWN ||
            directiondem == Imagine::KEY_RIGHT || directiondem == Imagine::KEY_LEFT) {
            pile_instruction += 1;
            carte.get_pos_centre(x, y);
            std::cout << x << "  " << y << std::endl;
        }
        temps += 1;
        Imagine::milliSleep(20);
    }
}
*/

void mouvement_ecran(CarteduMonde &carte) {
    int directiondem = 0;
    Imagine::Event e;
    getEvent(0, e);
    if (e.type == Imagine::EVT_KEY_ON) {
        directiondem = e.key;
        carte.deplace(directiondem);
    }
}