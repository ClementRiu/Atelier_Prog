// Author:   Clement Riu

#include "constante.h"
#include "outilsaff.h"
#include "outilscontr.h"


int nombre_test = 5000;

int main() {
    // Vérification de la présence des images et chargement.
    if (!charge_image()) {
        return 0;
    }

    // Overture de l'écran de jeu.
    Imagine::openWindow(widthscreen, heightscreen);
    interface();
    CarteduMonde carte;
    carte.affiche();


    // Test du mouvement au clavier.
    int i = 0;
    while (i < nombre_test) {
        mouvement_ecran(carte);
        std::cout << "Appui cours flèche du clavier ou clique sur la minimap !" << std::endl;
        Imagine::milliSleep(100);
        i += 1;
    }
    Imagine::endGraphics();
    return 0;
}

