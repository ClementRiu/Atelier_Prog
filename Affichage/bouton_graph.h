#pragma once

#include "constante.h"
#include "../Gestion/boutons.h"


class Bouton_Graph {
private:
    std::string nom;    //Nom du bouton.
    int zonebouton[4];  //Point en haut à gauche et en bas à droite du bouton.
    Imagine::Image<Imagine::Color> image_bouton;   // Image du bouton.
public:
    //Constructeur par défaut.
    Bouton_Graph();

    //Assesseur en lecture de l'attribut zonebouton.
    void get_zonebouton(int zonebout[]);

    //Méthode qui crée l'image image_bouton en fonction de la zone où va s'afficher le bouton.
    void calcul_image ();

    //Méthode qui affiche le bouton à sa position.
    void affiche_Bouton_Graph();
};