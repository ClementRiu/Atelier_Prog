// Author:   Charles AUGUSTE


#include"carte.h"


const float INF = 1.0f/0.0f; // Infini en float


// Met en surbrillance les cases autorisees au Heros
// A REMPLACER PAR DIJKASTRA
void CaseAutorisee(float dep, Case *carte, int num_case, bool brillance){
    float possibilite = dep - carte[num_case].NbDep();
    if (possibilite >= 0){
        carte[num_case].BrillanceOnOff(brillance);
        carte[num_case].Affiche();
        if ((num_case + 1) % NbCase != 0){
            CaseAutorisee(possibilite, carte, num_case + 1, brillance);
        }
        if ((num_case + 1) % NbCase != 1){
            CaseAutorisee(possibilite, carte, num_case - 1, brillance);
        }
        if (num_case >= NbCase){
            CaseAutorisee(possibilite, carte, num_case - NbCase, brillance);
        }
        if (num_case + 1 < NbCase * (NbCase - 1) ){
            CaseAutorisee(possibilite, carte, num_case + NbCase, brillance);
        }
    }
}


int main(){
    Imagine::openWindow(NbCase*Taille + Separation + LargDroite, NbCase*Taille);
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
            CaseAutorisee(h.GetDep() + carte[NumeroCase(x, y)].NbDep(), carte, NumeroCase(x, y), true);
            do{
                getEvent(0, e);
                if (e.type == Imagine::EVT_BUT_ON){
                    x1 = e.pix[0];
                    y1 = e.pix[1];
                }
            }while(e.type != Imagine::EVT_BUT_OFF || x > Taille * NbCase || y > Taille * NbCase || !carte[NumeroCase(x1, y1)].Brillance());
            carte[h.GetCase()].DeplaceHeros(h, carte[NumeroCase(x1, y1)]);
            CaseAutorisee(h.GetDep() + carte[NumeroCase(x, y)].NbDep(), carte, NumeroCase(x, y), false);
        }
    }
    Imagine::endGraphics();
    return 0;
}

