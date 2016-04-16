// Author:   Clement Riu


#include "outilsaff.h"


int main() {

    Imagine::openWindow(widthmap * taille_case, heightmap * taille_case);
    CarteduMonde carte;
    carte.affiche();
    Imagine::endGraphics();
    return 0;
}

