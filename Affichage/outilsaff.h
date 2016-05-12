#pragma once

#include "constante.h"


class Case_Graph {
private:
    const char *nom;  // Nom de la case.
    float p_dep;    // Nombre de deplacements nécessaires pour aller sur cette case.
    const char *description;  // Texte à afficher sur le côté.
    std::string nom_image;    // Nom de l'image.
    Imagine::Image<Imagine::Color> frame;   // Image de la case.
    bool occupation; // Si la case est occupée : = true ; si la case n'est pas occupée : = false
public:
    //Constructeur par défaut.
    Case_Graph();

    //Assesseur en lecture de l'attribut nom.
    const char *get_nom();

    //Assesseur en lecture de l'attribut p_dep.
    float get_poids();

    //Assesseur en lecture de l'attribut description.
    const char *get_description();

    //Assesseur en lecture de l'attribut nom_image.
    std::string get_nom_image();

    //Assesseur en lecture de l'attribut occupation.
    bool get_occupation();

    //Assesseur en écriture de l'attribut nom.
    void set_nom(char *nom_voulu);

    //Assesseur en écriture de l'attribut p_dep.
    void set_p_deb(float poids_voulu);

    //Assesseur en écriture de l'attribut description.
    void set_description(char *description_voulue);

    //Assesseur en écriture de l'attribut nom_image.
    void set_nom_image(const char *nom_image_voulue);

    //Assesseur en écriture de l'attribut frame.
    void set_frame(const char *nom_image_voulue);

    //Assesseur en écriture de l'attribut occupation.
    void set_occupation(bool occupation_voulue);

    //Méthode qui modifie l'intégralité des paramètres de la case.
    void set_Case_Graph(char *nom_voulu, float poids_voulu, char *description_voulue, const char *name,
                        bool occupation_voulue);

    //Méthode qui affiche la case à sa position, encadré d'un carré de couleur 'gris'. Prend des Coords en argument pour déterminer sa position.
    void affiche_Case_Graph(Imagine::Coords<2> pos_case);

    //Méthode qui affiche la case à sa position, encadré d'un carré de couleur 'gris'. Prend des int en argument pour déterminer sa position.
    void affiche_Case_Graph(int x, int y);

};

class CarteduMonde {
private:
    Imagine::Coords<2> pos_centre;    // Position du point centrale de la map.
    Imagine::Image<Case_Graph> listecase; // Image contenant la liste des cases de la map.

public:
    //Constructeur par défaut.
    CarteduMonde();

    //Assesseur en lecture de la position du centre.
    void get_pos_centre(Imagine::Coords<2> &pos);

    //Méthode qui affiche la carte dans le 'world'.
    void affiche();

    //Méthode qui décale l'affichage selon la directio dir voulue.
    void deplace(int dir);
};