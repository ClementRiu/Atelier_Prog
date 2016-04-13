// Author:   Charles AUGUSTE


#include"carte.h"


const float INF = 1.0f/0.0f; // Infini en float


int main(){
    Imagine::openWindow(NbCase*Taille + Separation + LargDroite, NbCase*Taille);
    // Initialisation des types de case
    TypeCase eau(INF, "De l'eau, sans vie, sans poisson, rien que de l'eau", Imagine::BLUE);
    TypeCase herbe(2, "C'est vert, les souris s'y cachent, c'est de l'herbe", Imagine::GREEN);
    TypeCase route(1, "Une case a moindre cout de deplacement", Imagine::YELLOW);
    // Initialisation de la carte
    Case carte[NbCase * NbCase];
    // Creation de la carte
    for (int i = 0; i < NbCase*Taille; i += Taille){
        for (int j = 0; j < NbCase*Taille; j += Taille){
            if ((i+1) % (j+1) == 0){
                Case c(i, j, eau);
                carte[NbCase * j / Taille + i / Taille] = c;
            }
            if ((i+1) % (j+1) == 1){
                Case c(i, j, herbe);
                carte[NbCase * j / Taille + i / Taille] = c;
            }
            if ((i+1) % (j+1) > 1){
                Case c(i, j, route);
                carte[NbCase * j / Taille + i / Taille] = c;
            }
        }
    }
    carte[30].Brillance();
    carte[50].Brillance();
    // Affichage des cases
    for (int i = 0; i < NbCase; i ++){
        for (int j = 0; j  <NbCase; j ++){
            carte[NbCase * j + i].Affiche();
        }
    }
    Imagine::endGraphics();
    return 0;
}

