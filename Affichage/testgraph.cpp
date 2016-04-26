// Author:   Clement Riu

#include "constante.h"
#include "outilsaff.h"
#include "outilscontr.h"


int main() {
    if (!charge_image()) {
        return 0;
    }
    Imagine::openWindow(widthscreen, heightscreen);
    CarteduMonde carte;
    carte.affiche();
    int i = 0;
    while (i < 5000) {
        mouvement_ecran(carte);
        std::cout << "Appui cours clavier !" << std::endl;
        Imagine::milliSleep(100);
        i += 1;
    }
    Imagine::endGraphics();
    return 0;
}

