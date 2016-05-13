#pragma once

#include "constante.h"
#include "outilsaff.h"
#include "map_graph.h"
#include "case_graph.h"


//Translate un point sur la 'mmap', en pixel à une coordonnée sur la 'map'.
Imagine::Coords<2> translate(Imagine::Coords<2> position, Imagine::Coords<2> pos_centre);

//Permet de déplacer l'écran au clavier ou par clique sur la minimap.
void mouvement_ecran(CarteduMonde &carte);