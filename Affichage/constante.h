#pragma once

#include <Imagine/Graphics.h>
#include <Imagine/Images.h>
#include <iostream>




//Le 'Screen' est l'ensemble de l'affichage.
const int widthscreen = 720;    //En pixel. Largeur de l'écran de jeu.
const int heightscreen = 540;   //En pixel. Hauteur de l'écran de jeu.


//Le 'world' désigne la zone de jeu où évolue le Héros, à l'écran.
const int widthworld = 600;     //En pixel. Largeur du 'world'.
const int heightworld = 520;    //En pixel. Hauteur du 'world'.


//Divers constante annexe, utile dans la suite.
const int widthui = widthscreen - widthworld;   //En pixel. Largeur de la barre latérale.
const int heightmenu = heightscreen - heightworld;  //En pixel. Hauteur de la barre inférieure.


//Définition de la taille des cases dans le world et de leur nombre.
const int taille_case_graph = 20; //En pixel. Taille des cases dans le 'world'.
const int width_nombre_case_world = widthworld / taille_case_graph;   //En case. Nombre de case du 'world' en largeur.
const int height_nombre_case_world = heightworld / taille_case_graph; //En case. Nombre de case du 'world' en hauteur.


//La mmap désigne la minimap.
const int taille_case_mmap = 1; //En pixel. Taille des cases dans la 'mmap'
const int widthmmap = widthui - 4;  //En pixel. Largeur de la 'mmap'.
const int heightmmap = (widthmmap - width_nombre_case_world * taille_case_mmap) +
                       taille_case_mmap * height_nombre_case_world;   //En pixel. Hauteur de la 'mmap'.
const int width_nombre_case_mmap = widthmmap / taille_case_mmap;   //En case. Nombre de case de la 'mmap' en largeur.
const int height_nombre_case_mmap = heightmmap / taille_case_mmap; //En case. Nombre de case de la 'mmap' en hauteur.



//La 'map' désigne la carte totale, et l'ensemble du monde. (Le 'world' n'est que la partie actuellement affichée de la 'map').
const int widthmap = 300;   //En case. Largeur de la 'map'.
const int heightmap = 300;  //En case. Hauteur de la 'map'


//Partie image.
const Imagine::RGB<double> gris(100, 100, 100); //Couleur de l'encadré gris des cases.

extern Imagine::Image<Imagine::Color> fond_ecran;   //Frame de fond d'écran.
extern Imagine::Image<Imagine::Color> parchemin;    //Frame du parchemin d'écran d'accueil.

extern Imagine::Image<Imagine::Color> foret1;   //Première frame de forêt.
extern Imagine::Image<Imagine::Color> eau1; //Première frame d'eau.
extern Imagine::Image<Imagine::Color> lande1;   //Première frame de lande.

bool charge_image();    //Fonction qui charge toutes les frames dans leur variables et vérifie qu'il n'y a pas d'erreur. Adapte également l'image à taille_case_graph.

Imagine::Image<Imagine::Color> entre_image_case(
        std::string nom_image_voulue);  //Fonction qui renvoie la frame assossiée au nom, pour les cases de 'map'.

Imagine::Color entre_couleur_case(
        std::string nom_image_voulue);    //Fonction qui renvoie la couleur assossiée au nom, pour les cases de 'mmap'.
