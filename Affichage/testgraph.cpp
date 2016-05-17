// Author:   Clement Riu

#include "include_graph.h"


int nombre_test = 5000;

int main() {
    // Vérification de la présence des images et chargement.
    if (!charge_image()) {
        return 0;
    }

    Imagine::openWindow(widthscreen, heightscreen);
    while (true) {
        int choix = affiche_accueil();
        if (choix == 1) {
            affiche_chargement();
            CarteduMonde carte;
            choix = gestion(carte);
        }
        if (choix == 2) {
            affiche_chargement();
            Imagine::milliSleep(2000);
            return 0;
        }
        if (choix == 3) {
            return 0;
        }
    }
    Imagine::endGraphics();
    return 0;
}

