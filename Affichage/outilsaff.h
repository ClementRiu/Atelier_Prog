#pragma once

#include <Imagine/Graphics.h>
#include <Imagine/Images.h>

const int widthmap = 30;
const int heightmap = widthmap * 3 / 4;
const int widthdesc = 100;
const int taille_case = 32;
const Imagine::Coords<2> zonedescription = (widthmap * taille_case, heightmap * taille_case - widthdesc);
const float INF = 1.0f / 0.0f; // Infini en float



class Case {
private:
    std::string nom; // Nom de la case.
    float p_dep;   // Nombre de deplacements nécessaires pour aller sur cette case.
    std::string description;    // Texte à afficher sur le côté.
    Imagine::Image<Imagine::Color> frame;   // Image de la case.
    bool occupation; // Si la case est occupée : = true ; si la case n'est pas occupée : = false
public:
    Case();

    Case(std::string nom, float p_dep, std::string description, const char *nomfichier);

    std::string get_nom();

    float get_poids();

    std::string get_description();

    bool get_occupation();

    void set_nom(std::string nom_voulu);

    void set_p_deb(float poids_voulu);

    void set_description(std::string description_voulue);

    void set_frame(const char *name);

    void set_occupation(bool occupation_voulue);

    void affiche_case(int pos_casex, int pos_casey);

    void affiche_description();
};

class CarteduMonde {
private:
    Imagine::Coords<2> pos_centre;  // Position du point centrale de la map.
    Imagine::Image<Case> listecase; // Image contenant la liste des cases de la map.

public:
    CarteduMonde();

    void affiche();
};