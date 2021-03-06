#pragma once

#include "constante.h"

class Bouton_Graph {
private:
    std::string nom;    //Nom du bouton.
    int type;   //Type de bouton. Si type == 0 alors le bouton est en dur, si type == 1 le bouton est transparent.
    int zonebouton[4];  //Point en haut à gauche et en bas à droite du bouton. En pixel.
    Imagine::Image<Imagine::Color> image_bouton;   // Image du bouton.
public:
    //Constructeur par défaut.
    Bouton_Graph();

    //Méthode qui initialise tous les attributs.
    void set_Bouton_Graph(std::string nom_voulu, int type_voulue, int zonebouton_voulue[]);

    //Assesseur en lecture de l'attribut zonebouton.
    void get_zonebouton(int zonebout[]) const ;

    //Assesseur en lecture de l'attribut type.
    int get_type() const ;

    //Assesseur en écriture de l'attribut zonebouton.
    void set_zonebouton(int zonebout_voulue[]);

    //Assesseur en écriture de l'attribut type.
    void set_type(int type_voulue);

    //Méthode qui renvoie la largeur du bouton.
    int get_largeur() const ;

    //Méthode qui renvoie la largeur du bouton.
    int get_hauteur() const ;

    //Méthode qui crée l'image image_bouton en fonction de la zone où va s'afficher le bouton.
    void calcul_image();

    //Méthode qui affiche le bouton à sa position.
    void affiche_Bouton_Graph() const ;

    //Méthode qui affiche le bouton à sa position.
    void affiche_Bouton_Graph(int multiplicateur) const ;
};

class Bouton {
    int zoneDeDelimitation[4]; // Tableau de la forme [xmin, ymin, xmax, ymax]
    std::string nomBouton;
    int taillePolice;
    //PARTIE GRAPHIQUE SUPPLEMENTAIRE :
    Bouton_Graph boutonaff; //Objet d'affichage.
public:

    Bouton(int xmin, int ymin, int xmax, int ymax, std::string nom, int type);


    Bouton(const int zone[4], std::string nom, int type);

    // Renvoie la largeur du bouton
    int largeur() const ;

    // renvoie la la hauteur du bouton
    int hauteur() const ;

    //Met à jour l'image du bonton.
    void calcul_image();

    // Permet d'afficher le bouton avec la largeur maximale possible pour l'écriture
    void affiche_graph(int decalementVertical = 0) const ;

    // Renvoie un true si le point (x, y) est dans la zone de delimitation du bouton et false sinon.
    bool boutonActive(int x, int y, int decalementVertical = 0) const ;

    // Regarde si le bouton est vide
    bool boutonVide();

    void setNom(std::string nom);
};


