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
void afficheCaseDisponibleOnOff(Case * carte, Unite h, bool b, float &deplacement, int case_a_atteindre) {
    carte[h.getCase()].fastMarching(h.getDep(), carte, b, deplacement, case_a_atteindre);
}


// Fonction simple permettant au joueur de deplacer n'impote quel Heros
void deplacement(Case * carte, std::vector<Unite> &unites, int x, int y) {
    int x1, y1, u = 0;
    if (x < Taille * NbCase && y < Taille * NbCase && carte[numeroCase(x,y)].getOccupe()) {
        while (unites[u].getCase() != numeroCase(x,y)) {
            u += 1;
        }
        float deplacement = unites[u].getDep();
        if (deplacement > 0) {
            // On met la variable deplacement juste parce qu'on est oblige, elle n'est pas modifiee ici
            afficheCaseDisponibleOnOff(carte, unites[u], true, deplacement, 0);
            do {
                clic(x1,y1);
            } while(x1 > Taille * NbCase || y1 > Taille * NbCase || !carte[numeroCase(x1, y1)].Brillance());
            afficheCaseDisponibleOnOff(carte, unites[u], false, deplacement, numeroCase(x1, y1));
            deplaceHeros(carte, unites[u], x1, y1);
            unites[u].setDep(deplacement);
        }
    }
}


void finTour(std::vector<Unite> &unites, int x, int y){
    // CONDITON A CHANGER EN FONCTION DU TRACE DE L'ENDROIT DE FIN DU TOUR #CLEMENT
    if(x > NbCase * Taille + Separation && y > Taille * (NbCase - 5)){
        for (int i=0; i<unites.size(); ++i){
            unites[i].setDep(unites[i].getDepMax());
        }
    }
}


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
    Imagine::drawRect(NbCase * Taille + Separation,Taille * (NbCase - 5), LargDroite-1, LargDroite-1, Imagine::BLACK);
    std::string s = "FIN DE TOUR BANDE DE PAYSANS";
    Imagine::drawString(NbCase * Taille + Separation,Taille * (NbCase - 5), s, Imagine::BLACK, 4);
    // Deplacement des unites
    while (true) {
        int x, y;
        clic(x, y);
        deplacement(carte, unites, x, y);
        finTour(unites, x, y);

    }
    Imagine::endGraphics();
    return 0;
}

