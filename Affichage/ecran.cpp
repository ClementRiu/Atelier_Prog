#include "ecran.h"

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

int affiche_menu() {
    Bouton NouvellePartieG(200, 160, 520, 190, std::string("Nouvelle Partie"), 0);
    Bouton ChargerPartieG(200, 240, 520, 270, std::string("Charger Partie"), 0);
    Bouton QuitterJeuG(200, 320, 520, 350, std::string("Quitter le Jeu"), 0);
    Imagine::display(parchemin, 0, 0);
    NouvellePartieG.affiche_graph();
    ChargerPartieG.affiche_graph();
    QuitterJeuG.affiche_graph();
    return 1;
}

void affiche_chargement() {
    Imagine::display(fond_ecran, 0, 0);
    Imagine::drawString(widthscreen / 2 - 11 * 6 * 1.2, heightscreen / 2 - 6, "Chargement en cours...", gris);
}