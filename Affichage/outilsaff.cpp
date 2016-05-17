#include "outilsaff.h"


//Cette fonction trace l'interface graphique.
void interface(Bouton fin_tour, Bouton menu) {
    Imagine::display(fond_ecran, 0, 0);
    Imagine::drawRect(widthworld + (widthui - widthmmap) / 2 - 1, (widthui - widthmmap) / 2 - 1, widthmmap + 1,
                      heightmmap + 1, Imagine::BLACK, 1);

    fin_tour.affiche_graph();

    menu.affiche_graph();
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



