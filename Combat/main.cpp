#include "../Gestion/unite.h"
#include <Imagine/Graphics.h>
#include "../Gestion/carte.h"

int main() {
    Imagine::openWindow(NbCase * Taille + Separation + LargDroite, NbCase * Taille);
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
    // Initialisation des types de case
    TypeCase route(1, "Une case a moindre cout de deplacement", Imagine::YELLOW);
    // Initialisation de la carte
    Case carte[NbCase * NbCase];
    // Creation de la carte
    for (int i = 0; i < NbCase * Taille; i += Taille) {
        for (int j = 0; j < NbCase * Taille; j += Taille) {
            Case c(i, j, route);
            carte[numeroCase(i, j)] = c;
        }
    }
    // Initialisation des unites
    std::vector<Unite> unites;
    Unite h(5, 204);
    carte[204].flagHeros();
    Unite h2(10, 203);
    carte[203].flagHeros();
    unites.push_back(h);
    unites.push_back(h2);
    // Affichage des cases
    for (int i = 0; i < NbCase; i++) {
        for (int j = 0; j < NbCase; j++) {
            carte[NbCase * j + i].affiche();
        }
    }
    Bouton boutonFinTour(NbCase * Taille + Separation, Taille * (NbCase - 5),
                         NbCase * Taille + Separation + LargDroite, NbCase * Taille, Imagine::BLACK,
                         "End turn");
    boutonFinTour.affiche();
    Unite unit;


    while (true) {
        unites[0].tour(carte, unites, boutonFinTour);
        unites[1].tour(carte, unites, boutonFinTour
                       );
    }

    Imagine::endGraphics();
    return 0;
}

