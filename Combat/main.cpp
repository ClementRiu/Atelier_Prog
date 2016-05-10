#include "../Gestion/unite.h"
#include <Imagine/Graphics.h>
#include "../Gestion/carte.h"

int main() {
    Imagine::openWindow(width, height);

    // Initialisation d'une attaque
    std::vector<Imagine::Coords<2> > zoneInfl;
    zoneInfl.push_back(portee10);
    zoneInfl.push_back(portee_10);
    zoneInfl.push_back(portee20);
    zoneInfl.push_back(portee_20);
    zoneInfl.push_back(portee01);
    zoneInfl.push_back(portee02);
    zoneInfl.push_back(portee0_2);
    zoneInfl.push_back(portee0_1);
    Attaque coinCoinOuille(zoneInfl, 10);

    Carte carte;

    // Initialisation des unites
    std::vector<Unite*> unites;
    carte[204].flagHeros();
    carte[203].flagHeros();
    unites.push_back(new Unite(5, 204));
    unites.push_back(new Unite(10, 203));

    // Affichage des cases
    for (int i = 0; i < NbCase; i++) {
        for (int j = 0; j < NbCase; j++) {
            carte[NbCase * j + i].affiche();
        }
    }

    // Affichage du bouton fin de tour
    Bouton boutonFinTour(NbCase * Taille + Separation, Taille * (NbCase - 5),
                         NbCase * Taille + Separation + LargDroite, NbCase * Taille, Imagine::BLACK,
                         "End turn");
    boutonFinTour.affiche();
    Unite unit;


    while (true) {
        unites[0]->tour(carte, unites, boutonFinTour);
        unites[1]->tour(carte, unites, boutonFinTour
                       );
    }

    Imagine::endGraphics();

    // Destruction des unités
    for (int i = 0; i < unites.size(); ++i){
        unites[i]->~Unite();
        delete unites[i];
        unites[i] = 0;
    }
    return 0;
}

