#include "ecran_menu.h"


/*
    // Ecran de menu
    Bouton nouvellePartie(width / 4, height / 2 - 20, 3 * width / 4, height / 2 + 20, Imagine::BLUE, "Nouvelle Partie");
    int x = 0, y = 0;
    nouvellePartie.affiche();
    while (!nouvellePartie.boutonActive(x, y)) {
        clicSimple(x, y);
    }

    // Affichage des cases
    for (int i = 0; i < NbCase; i++) {
        for (int j = 0; j < NbCase; j++) {
            carte[NbCase * j + i].affiche();
        }
    }
    */

int affiche_menu(){
    Imagine::display(fond_ecran,0,0);
    Imagine::display(parchemin,0,0);
    Imagine::milliSleep(1000);
    return 1;
}