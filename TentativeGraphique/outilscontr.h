#pragma once

#include "constante.h"
#include "outilsaff.h"
#include "map_graph.h"
#include "case_graph.h"
#include "bouton_graph.h"
#include "ecran.h"
#include "icone_graph.h"


//Fonction qui affiche l'écran de gestion et gère le jeu.
int gestion(CarteduMonde &carte, Heros_Graph heros1, Heros_Graph heros2);

//Fonction qui attend un évènement.
int evenement(CarteduMonde &carte, Bouton bouton_fin_tour, Bouton bouton_menu);

//Translate un point sur la 'mmap', en pixel à une coordonnée sur la 'map'.
Imagine::Coords<2> translate(Imagine::Coords<2> position, Imagine::Coords<2> pos_centre);

Imagine::Coords<2> translate(int positiondepx, int positiondepy, int pos_centrex, int pos_centrey);
/*
//Permet de déplacer l'écran au clavier ou par clique sur la minimap.
void mouvement_ecran(CarteduMonde &carte);
*/