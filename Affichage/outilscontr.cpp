#include "outilscontr.h"

//Translate un point sur la 'mmap', en pixel à une coordonnée sur la 'map'.
Imagine::Coords<2> translate(Imagine::Coords<2> positiondep, Imagine::Coords<2> pos_centre) {
    positiondep[0] = positiondep[0] - widthworld - 2 - widthmmap / 2;
    positiondep[1] = positiondep[1] - 2 - heightmmap / 2;
    positiondep = positiondep / taille_case_mmap;
    positiondep = pos_centre + positiondep;
    return positiondep;
}


//Permet de déplacer l'écran au clavier ou par clique sur la minimap.
void mouvement_ecran(CarteduMonde &carte) {
    int directiondem = 0;
    Imagine::Event e;
    getEvent(0, e);
    //Gestion du déplacement au clavier.
    if (e.type == Imagine::EVT_KEY_ON) {
        directiondem = e.key;
        carte.deplace_clavier(directiondem);
    }
    //Gestion du déplacement à la souris.
    if (e.type == Imagine::EVT_BUT_ON) {
        if (e.button = 1) {
            Imagine::Coords<2> pos_centrelu;
            carte.get_pos_centre(pos_centrelu);
            carte.deplace_souris(translate(e.pix, pos_centrelu));
        }

    }
}