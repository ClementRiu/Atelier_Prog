#include "outilscontr.h"

//Fonction qui affiche l'écran de gestion et gère le jeu.
int gestion(CarteduMonde &carte, Heros_Graph heros1, Heros_Graph heros2){
    Bouton fin_tour(widthworld + 2, heightworld + 2 - taille_case_graph, widthscreen - 2, heightscreen - 2, std::string("Fin de Tour"), 0);
    Bouton menu(2, heightworld + 2, 70, heightscreen - 2, std::string("Menu"), 0);
    interface(fin_tour, menu);
    carte.affiche();
    heros1.affiche_heros(carte);
    heros2.affiche_heros(carte);
    heros1.affiche_interface_heros();
    return evenement(carte, fin_tour, menu);
}

//Fonction qui attend un évènement.
int evenement(CarteduMonde &carte, Bouton bouton_fin_tour, Bouton bouton_menu) {
    int x = 0, y = 0;
    int directiondem = 0;
    Imagine::Event e;
    while (true) {
        getEvent(0, e);
        if (e.type == Imagine::EVT_BUT_ON) {
            x=e.pix[0];
            y=e.pix[1];
            Imagine::getMouse(x, y);
            //Le bouton de fin de tour est-il actif :
            if (bouton_fin_tour.boutonActive(x, y)) {
                Imagine::flushEvents();
                break;
            }

            //Le bouton de menu est-il actif :
            if (bouton_menu.boutonActive(x, y)) {
                Imagine::flushEvents();
                int choix = affiche_menu();
                if (choix ==1){
                    carte.affiche();
                    break;
                }
                if (choix == 2){
                    return 2;
                }
                if (choix == 3){
                    affiche_accueil();
                    return 0;
                }
            }

            if (dans_mmap(x, y)) {
                Imagine::Coords<2> pos_centrelu = carte.get_pos_centre();
                Imagine::Coords<2> pos_clique = translate(e.pix, pos_centrelu);
                Imagine::flushEvents();
                carte.deplace_souris(pos_clique);
            }
        }
        if (e.type == Imagine::EVT_KEY_ON){
            directiondem = e.key;
            Imagine::flushEvents();
            carte.deplace_clavier(directiondem);
        }
    }
}


//Translate un point sur la 'mmap', en pixel à une coordonnée sur la 'map'.
Imagine::Coords<2> translate(Imagine::Coords<2> positiondep, Imagine::Coords<2> pos_centre) {
    positiondep[0] = positiondep[0] - widthworld - 2 - widthmmap / 2;
    positiondep[1] = positiondep[1] - 2 - heightmmap / 2;
    positiondep = positiondep / taille_case_mmap;
    positiondep = pos_centre + positiondep;
    return positiondep;
}

/*
//Permet de déplacer l'écran au clavier ou par clique sur la minimap.
void mouvement_ecran(CarteduMonde &carte) {
    int directiondem = 0;
    Imagine::Event e;
    getEvent(0, e);
    //Gestion du déplacement au clavier.
    if (e.type == Imagine::EVT_KEY_ON) {
        directiondem = e.key;
        Imagine::flushEvents();
        carte.deplace_clavier(directiondem);
    }
    //Gestion du déplacement à la souris.
    if (e.type == Imagine::EVT_BUT_ON) {
        if (e.button = 1) {
            if (dans_mmap(e.pix)) {
                Imagine::Coords<2> pos_centrelu;
                carte.get_pos_centre(pos_centrelu);
                Imagine::Coords<2> pos_clique = translate(e.pix, pos_centrelu);
                Imagine::flushEvents();
                carte.deplace_souris(pos_clique);
            }
            else {
                Imagine::flushEvents();
            }
        }
    }
}
*/