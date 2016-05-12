// Author:   Clement Riu

#include "include_graph.h"

int nombre_test = 0;

int main() {
    // Vérification de la présence des images et chargement.
    if (!charge_image()) {
        return 0;
    }

    // Overture de l'écran de jeu.
    Imagine::openWindow(widthscreen, heightscreen);
    CarteduMonde carte;
    carte.affiche();

    // Test du mouvement au clavier.
    int i = 0;
    while (i < nombre_test) {
        mouvement_ecran(carte);
        std::cout << "Appui cours clavier !" << std::endl;
        Imagine::milliSleep(100);
        i += 1;
    }
    Imagine::endGraphics();
    return 0;
}

