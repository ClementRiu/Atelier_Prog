#include "carte.h"
#include "unite.h"


const float INF = 1.0f / 0.0f; // Infini en float


// Fonction renvoyant en référence dans x et y la position d'un clic
void clic(int &x, int &y) {
    Imagine::Event e;
    do {
        getEvent(0, e);
        if (e.type == Imagine::EVT_BUT_ON) {
            x = e.pix[0];
            y = e.pix[1];
        }
    } while (e.type != Imagine::EVT_BUT_OFF);
}


// Fonction simple permettant de deplacer le Heros
void deplaceHeros(Case *carte, Unite &h, int x1, int y1) {
    carte[h.getCase()].deplaceHeros(h, carte[numeroCase(x1, y1)]);
}


// Fonction simple permettant d'afficher les cases disponibles pour le Heros, ou de les enlever
void afficheCaseDisponibleOnOff(Case * carte, Unite h, bool b) {
    carte[h.getCase()].fastMarching(h.getDep(), carte, b);
}


// Fonction simple permettant au joueur de deplacer n'impote quel Heros
void Deplacement(Case * carte, std::vector<Unite> &Unites) {
    int x, y, x1, y1, u = 0;
    clic(x, y);
    if (x < Taille * NbCase && y < Taille * NbCase && carte[numeroCase(x,y)].getOccupe()) {
        while (Unites[u].getCase() != numeroCase(x,y)) {
            u += 1;
        }
        afficheCaseDisponibleOnOff(carte, Unites[u], true);
        do {
            clic(x1,y1);
        } while(x1 > Taille * NbCase || y1 > Taille * NbCase || !carte[numeroCase(x1, y1)].Brillance());
        afficheCaseDisponibleOnOff(carte, Unites[u], false);
        deplaceHeros(carte, Unites[u], x1, y1);
    }
}


int main() {
    Imagine::openWindow(NbCase * Taille + Separation + LargDroite, NbCase * Taille);
    // Initialisation des types de case
    TypeCase eau(INF, "De l'eau, sans vie, sans poisson, rien que de l'eau", Imagine::BLUE);
    TypeCase herbe(2, "C'est vert, les souris s'y cachent, c'est de l'herbe", Imagine::GREEN);
    TypeCase route(1, "Une case a moindre cout de deplacement", Imagine::YELLOW);
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
    // Initialisation des unites
    std::vector<Unite> Unites;
    Unite h(5, 304);
    carte[304].flagHeros();
    Unite h2(10, 303);
    carte[303].flagHeros();
    Unites.push_back(h);
    Unites.push_back(h2);
    // Affichage des cases
    for (int i = 0; i < NbCase; i++) {
        for (int j = 0; j < NbCase; j++) {
            carte[NbCase * j + i].affiche();
        }
    }
    // Deplacement des unites
    while (true) {
        Deplacement(carte, Unites);
    }
    Imagine::endGraphics();
    return 0;
}

