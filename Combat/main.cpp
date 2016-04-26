#include "../Gestion/unite.h"
#include <Imagine/Graphics.h>
#include "../Gestion/carte.h"

int main() {
    Imagine::openWindow(NbCase * Taille + Separation + LargDroite, NbCase * Taille);
    // Initialisation d'une attaque
    std::vector<Imagine::Coords<2> > zoneInfl;
    zoneInfl.push_back(a10);
    zoneInfl.push_back(a_10);
    zoneInfl.push_back(a20);
    zoneInfl.push_back(a_20);
    zoneInfl.push_back(a01);
    zoneInfl.push_back(a02);
    zoneInfl.push_back(a0_2);
    zoneInfl.push_back(a0_1);
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
    Unite h(5, 304);
    carte[304].flagHeros();
    Unite h2(10, 303);
    carte[303].flagHeros();
    unites.push_back(h);
    unites.push_back(h2);
    // Affichage des cases
    for (int i = 0; i < NbCase; i++) {
        for (int j = 0; j < NbCase; j++) {
            carte[NbCase * j + i].affiche();
        }
    }
    // Trace de l'endroit fin du tour A CHANGER #CLEMENT
    Imagine::drawRect(NbCase * Taille + Separation, Taille * (NbCase - 5), LargDroite - 1, LargDroite - 1,
                      Imagine::BLACK);
    std::string s = "FIN DE TOUR BANDE DE PAYSANS";
    Imagine::drawString(NbCase * Taille + Separation, Taille * (NbCase - 5), s, Imagine::BLACK, 4);
    // Deplacement des unites

    Unite unit;

    //Je ne sais pas encore quel type entre liste/vector/queue/deque je vais utiliser, à revenir
    std::list<Unite> unites_bis;
    unites_bis.push_front(h);
    unites_bis.push_front(h2);


    while (true) {
        unites[0].tour(carte, unites);
        unites[1].tour(carte, unites);
    }

    Imagine::endGraphics();
    return 0;
}

