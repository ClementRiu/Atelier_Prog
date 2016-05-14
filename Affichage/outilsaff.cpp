#include "outilsaff.h"


//Cette fonction trace l'interface graphique.
void interface() {
    Imagine::display(fond_ecran, 0, 0);
    Imagine::drawRect(widthworld + (widthui - widthmmap) / 2 - 1, (widthui - widthmmap) / 2 - 1, widthmmap + 1,
                      heightmmap + 1, Imagine::BLACK, 1);
}

//Renvoi la couleur pour la 'mmap' en fonction du type de la case.
Imagine::Color couleur_case(std::string nom) {
    if (nom == std::string("Etendue d'Eau")) {
        return Imagine::BLUE;
    }
    if (nom == std::string("Foret")) {
        return Imagine::GREEN;
    }
    if (nom == std::string("Lande")) {
        return Imagine::YELLOW;
    }
    if (nom == std::string("Vide")) {
        return Imagine::BLACK;
    }
}



