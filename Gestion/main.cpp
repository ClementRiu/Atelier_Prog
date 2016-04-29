#include "carte.h"
#include "unite.h"


int main() {
    Imagine::openWindow(NbCase * Taille + Separation + LargDroite, NbCase * Taille);

    // Initialisation des types de case
    TypeCase eau(INF, "De l'eau, sans vie, sans poisson, rien que de l'eau", Imagine::BLUE);
    TypeCase herbe(2, "C'est vert, les souris s'y cachent, c'est de l'herbe", Imagine::GREEN);
    TypeCase route(1, "Une case a moindre cout de deplacement", Imagine::YELLOW);
    TypeCase ville(1, "La ville, le doux foyer", Imagine::MAGENTA);
    // Initialisation de la carte
    Case carte[NbCase * NbCase];
    // Creation de la carte
    for (int i = 0; i < NbCase * Taille; i += Taille) {
        for (int j = 0; j < NbCase * Taille; j += Taille) {
            if ((i + 1) % (j + 1) == 0) {
                Case c(i, j, eau);
                carte[numeroCase(i, j)] = c;
            }
            if ((i + 1) % (j + 1) == 1) {
                Case c(i, j, herbe);
                carte[numeroCase(i, j)] = c;
            }
            if ((i + 1) % (j + 1) > 1) {
                Case c(i, j, route);
                carte[numeroCase(i, j)] = c;
            }
        }
    }
    Case c(0, 0, ville);
    carte[0] = c;
    // Initialisation des unites
    bool load = false;
    std::vector<Unite> unites;
    if (load) {
        charge(unites, carte);
    }
    else{
        Unite h(5, 304);
        carte[304].flagHeros();
        Unite h2(10, 303);
        carte[303].flagHeros();
        unites.push_back(h);
        unites.push_back(h2);
    }
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
    // Trace de l'endroit pour sauvegarder et quitter A CHANGER
    Imagine::drawRect(NbCase * Taille + Separation, Taille * (NbCase - 5)-LargDroite-10, LargDroite - 1, LargDroite - 1,
                      Imagine::BLACK);
    Imagine::drawString(NbCase * Taille + Separation, Taille * (NbCase - 5)-LargDroite, "SAVE & QUIT", Imagine::BLACK, 10);
    // Deplacement des unites
    bool save = true;
    while (save) {
        int x = -1, y = -1, x1 = -1, y1 = -1;
        survole(x1, y1);
        clic(x, y, carte);
        std::cout << numeroCase(x, y) << std::endl;
        int u = 0;
        if (numeroCase(x, y) != -1 && carte[numeroCase(x, y)].getOccupe()) {
            while (unites[u].getCase() != numeroCase(x, y)) {
                u += 1;
            }
            unites[u].deplacement(carte);
        }
        if (finTourDemande(x, y)) {
            finJournee(unites);
        }
        if (sauvegardeDemande(x,y)) {
            sauvegarde(unites);
            save = false;
        }

    }
    Imagine::endGraphics();
    return 0;
}

