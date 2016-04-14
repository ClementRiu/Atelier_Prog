// Author:   Charles AUGUSTE


#include "carte.h"
#include "priorite.h"


const float INF = 1.0f/0.0f; // Infini en float


// Algorithme de FastMarching pour mettre en surbrillance les cases autorisées au Heros
void FastMarching(float dep, Case *carte, int num_case, bool brillance){
    FilePriorite F;
    CaseDist depart(num_case, dep);
    F.push(depart);
    while (!F.empty()){
        CaseDist c = F.pop();
        for (int i = -1; i <= 1; i = i + 2){
            for (int j = 1; j <= NbCase; j = j + NbCase - 1){
                if (c.GetNum() + i * j >= 0 && c.GetNum() + i * j < NbCase * NbCase &&
                    ((c.GetNum() + i * j) % NbCase != 0 || c.GetNum() % NbCase != NbCase - 1) &&
                    ((c.GetNum() + i * j) % NbCase != NbCase - 1 || c.GetNum() % NbCase != 0) &&
                     c.GetDep() - carte[c.GetNum() + i * j].NbDep() >= 0 &&
                     carte[c.GetNum() + i * j].Brillance() != brillance){
                        carte[c.GetNum() + i * j].BrillanceOnOff(brillance);
                        CaseDist c2(c.GetNum() + i * j, c.GetDep() - carte[c.GetNum() + i * j].NbDep());
                        F.push(c2);
                }
            }
        }
    }
}


int main(){
    Imagine::openWindow(NbCase * Taille + Separation + LargDroite, NbCase * Taille);
    // Initialisation du Heros
    Heros h(5);
    // Initialisation des types de case
    TypeCase eau(INF, "De l'eau, sans vie, sans poisson, rien que de l'eau", Imagine::BLUE);
    TypeCase herbe(2, "C'est vert, les souris s'y cachent, c'est de l'herbe", Imagine::GREEN);
    TypeCase route(1, "Une case a moindre cout de deplacement", Imagine::YELLOW);
    // Initialisation de la carte
    Case carte[NbCase * NbCase];
    // Creation de la carte
    for (int i = 0; i < NbCase*Taille; i += Taille){
        for (int j = 0; j < NbCase*Taille; j += Taille){
            if ((i + 1) % (j + 1) == 0){
                Case c(i, j, eau);
                carte[NumeroCase(i, j)] = c;
            }
            if ((i + 1) % (j + 1) == 1){
                Case c(i, j, herbe);
                carte[NumeroCase(i, j)] = c;
            }
            if ((i + 1) % (j + 1) > 1){
                Case c(i, j, route);
                carte[NumeroCase(i, j)] = c;
            }
        }
    }
    // Placement du Heros
    carte[0].FlagHeros();
    // Affichage des cases
    for (int i = 0; i < NbCase; i ++){
        for (int j = 0; j  <NbCase; j ++){
            carte[NbCase * j + i].Affiche();
        }
    }
    // On bouge le heros
    carte[h.GetCase()].DeplaceHeros(h,carte[50]);
    while (true){
        Imagine::Event e;
        int x, y, x1, y1;
        do{
            getEvent(0, e);
            if(e.type == Imagine::EVT_BUT_ON){
                x = e.pix[0];
                y = e.pix[1];
            }
        }while(e.type != Imagine::EVT_BUT_OFF);
        if (NumeroCase(x,y) == h.GetCase()){
            FastMarching(h.GetDep(), carte, NumeroCase(x, y), true);
            do{
                getEvent(0, e);
                if (e.type == Imagine::EVT_BUT_ON){
                    x1 = e.pix[0];
                    y1 = e.pix[1];
                }
            }while(e.type != Imagine::EVT_BUT_OFF || x > Taille * NbCase || y > Taille * NbCase || !carte[NumeroCase(x1, y1)].Brillance());
            carte[h.GetCase()].DeplaceHeros(h, carte[NumeroCase(x1, y1)]);
            FastMarching(h.GetDep(), carte, NumeroCase(x, y), false);
        }
    }
    Imagine::endGraphics();
    return 0;
}

