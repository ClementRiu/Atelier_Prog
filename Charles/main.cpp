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
                carte[NumeroCase(i, j)] = c;
            }
            if ((i+1) % (j+1) == 1){
                Case c(i, j, herbe);
                carte[NumeroCase(i, j)] = c;
            }
            if ((i+1) % (j+1) > 1){
                Case c(i, j, route);
                carte[NumeroCase(i, j)] = c;
            }
        }
    }
    carte[30].Brillance();
    Heros h;
    h.SetCase(0);;
    carte[0].FlagHeros();
    carte[50].Brillance();
    // Affichage des cases
    for (int i = 0; i < NbCase; i ++){
        for (int j = 0; j  <NbCase; j ++){
            carte[NbCase * j + i].Affiche();
        }
    }
    // On bouge le heros
    carte[h.GetCase()].DeplaceHeros(h,carte[35]);
    while (true){
        Imagine::Event e;
        int x, y;
        do{
            getEvent(0, e);
            if(e.type == Imagine::EVT_BUT_ON){
                x = e.pix[0];
                y = e.pix[1];
            }
        }while(e.type!=Imagine::EVT_BUT_OFF);
        if (x / Taille < NbCase && y / Taille < NbCase){
            carte[h.GetCase()].DeplaceHeros(h, carte[NumeroCase(x,y)]);
        }
    }
    Imagine::endGraphics();
    return 0;
}

