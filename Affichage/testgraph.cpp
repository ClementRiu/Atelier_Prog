// Author:   Clement Riu

#include "include_graph.h"


int nombre_test = 5000;

int main() {
    // Vérification de la présence des images et chargement.
    if (!charge_image()) {
        return 0;
    }

    Imagine::openWindow(widthscreen, heightscreen);
    if (affiche_menu()==1) {

        // Overture de l'écran de gestion.
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
    }
    Imagine::endGraphics();
    return 0;
}

