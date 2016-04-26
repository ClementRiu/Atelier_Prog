#pragma once

#include "constante.h"


class Case {
private:
    const char *nom;  // Nom de la case.
    float p_dep;    // Nombre de deplacements nécessaires pour aller sur cette case.
    const char *description;  // Texte à afficher sur le côté.
    std::string nom_image;    // Nom de l'image.
    Imagine::Image<Imagine::Color> frame;   // Image de la case.
    bool occupation; // Si la case est occupée : = true ; si la case n'est pas occupée : = false
public:
    Case();

    //Case(std::string nom, float p_dep, std::string description, const char *nomfichier);

    const char *get_nom();

    float get_poids();

    const char *get_description();

    std::string get_nom_image();

    bool get_occupation();

    void set_nom(char *nom_voulu);

    void set_p_deb(float poids_voulu);

    void set_description(char *description_voulue);

    void set_nom_image(const char *nom_image_voulue);

    void set_frame(const char *nom_image_voulue);

    void set_occupation(bool occupation_voulue);

    void set_case(char *nom_voulu, float poids_voulu, char *description_voulue, const char *name,
                  bool occupation_voulue);

    void affiche_case(Imagine::Coords<2> pos_case);

    void affiche_case(int x, int y);

    //void affiche_description();
};

class CarteduMonde {
private:
    Imagine::Coords<2> pos_centre;    // Position du point centrale de la map.
    Imagine::Image<Case> listecase; // Image contenant la liste des cases de la map.

public:
    CarteduMonde();

    void get_pos_centre(Imagine::Coords<2> &pos);

    void affiche();

    void deplace(int dir);
};