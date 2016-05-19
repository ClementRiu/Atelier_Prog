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
            Heros_Graph heros1;
            Heros_Graph heros2;
            heros1.set_Heros_Graph("Héros gentil", "Heros_bleu", widthmap / 2 + 1, heightmap / 2, 1);
            heros2.set_Heros_Graph("Héros méchant", "Heros_rouge", widthmap / 2 + 10, heightmap / 2 + 10, 2);
            choix = gestion(carte, heros1, heros2);
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

