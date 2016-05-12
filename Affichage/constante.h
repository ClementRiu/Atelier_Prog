#pragma once

#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include <iostream>

const float INF = 1.0f / 0.0f;  // Infini en float.


const int widthscreen = 720;    //En pixel. Largeur de l'écran de jeu.
const int heightscreen = 540;   //En pixel. Hauteur de l'écran de jeu.
//Le 'world' désigne la zone de jeu où évolue le Héros, à l'écran.
const int widthworld = 600;     //En pixel. Largeur du 'world'.
const int heightworld = 530;    //En pixel. Hauteur du 'world'.

const int taille_case_graph = 18; //En pixel. Taille des cases dans le 'world'.

//La 'map' désigne la carte totale, et l'ensemble du monde. (Le 'world' n'est que la partie actuellement affichée de la 'map').
const int widthmap = 300;   //En case. Largeur de la 'map'.
const int heightmap = 300;  //En case. Hauteur de la 'map'

const Imagine::RGB<double> gris(100, 100, 100); //Couleur de l'encadré gris des cases.

extern Imagine::Image<Imagine::Color> foret1;   //Première frame de forêt.
extern Imagine::Image<Imagine::Color> eau1; //Première frame d'eau.
extern Imagine::Image<Imagine::Color> lande1;   //Première frame de lande.

bool charge_image();    //Fonction qui charge toutes les frames dans leur variables et vérifie qu'il n'y a pas d'erreur. Adapte également l'image à taille_case_graph.
