#include "attaque.h"


int main() {
    Imagine::openWindow(NbCase * Taille + Separation + LargDroite, NbCase * Taille);
    // Initialisation d'une attaque
    std::vector<Imagine::Coords<2> > zoneInfl;
    Imagine::Coords<2> a1 (1, 0); zoneInfl.push_back(a1);
    Imagine::Coords<2> a2 (- 1, 0); zoneInfl.push_back(a2);
    Imagine::Coords<2> a3 (2, 0); zoneInfl.push_back(a3);
    Imagine::Coords<2> a4 (- 2, 0); zoneInfl.push_back(a4);
    Imagine::Coords<2> a5 (0, 1); zoneInfl.push_back(a5);
    Imagine::Coords<2> a6 (0, 2); zoneInfl.push_back(a6);
    Imagine::Coords<2> a7 (0, - 2); zoneInfl.push_back(a7);
    Imagine::Coords<2> a8 (0, -1); zoneInfl.push_back(a8);
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
    while (true) {
        int x, y, choix = -1;
        clic(x, y);
        int u = 0;
        if (x < Taille * NbCase && y < Taille * NbCase && carte[numeroCase(x, y)].getOccupe()) {
            while (unites[u].getCase() != numeroCase(x, y)) {
                u += 1;
            }
            choisir(choix);
        }
        if (choix == Imagine::KEY_NUMPAD0) {
            deplacement(carte, unites, u);
        }
        if (choix == Imagine::KEY_NUMPAD1){
            int x1, y1, u2 = 0;
            coinCoinOuille.zone(carte, unites[u], true);
            do {
                clic(x1,y1);
            } while(x1 > Taille * NbCase || y1 > Taille * NbCase || !carte[numeroCase(x1, y1)].Brillance());
            if (carte[numeroCase(x1, y1)].getOccupe()){
                while (unites[u2].getCase() != numeroCase(x1, y1)) {
                    u2 += 1;
                }
                coinCoinOuille.action(unites[u2]);
            }
            coinCoinOuille.zone(carte, unites[u], false);
        }
        finTour(unites, x, y);
    }
    Imagine::endGraphics();
    return 0;
}

