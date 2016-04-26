#include "outilsaff.h"


// Fonction relative à Case.
Case::Case() {
    nom = "Vide";
    p_dep = INF;
}

const char *Case::get_nom() {
    return nom;
}

float Case::get_poids() {
    return p_dep;
}

const char *Case::get_description() {
    return description;
}

std::string Case::get_nom_image() {
    return nom_image;
}

bool Case::get_occupation() {
    return occupation;
}

void Case::set_nom(char *nom_voulu) {
    nom = nom_voulu;
}

void Case::set_p_deb(float poids_voulu) {
    p_dep = poids_voulu;
}

void Case::set_description(char *description_voulue) {
    description = description_voulue;
}

void Case::set_nom_image(const char *nom_image_voulue) {
    nom_image = std::string(nom_image_voulue);
}

void Case::set_frame(const char *nom_image_voulue) {
    if (std::string(nom_image_voulue) == std::string("foret1")) {
        frame = foret1;
    }
    if (std::string(nom_image_voulue) == std::string("eau1")) {
        frame = eau1;
    }
    if (std::string(nom_image_voulue) == std::string("lande1")) {
        frame = lande1;
    }
}

void Case::set_occupation(bool occupation_voulue) {
    occupation = occupation_voulue;
}

void Case::set_case(char *nom_voulu, float poids_voulu, char *description_voulue, const char *name,
                    bool occupation_voulue) {
    set_nom(nom_voulu);
    set_p_deb(poids_voulu);
    set_description(description_voulue);
    set_frame(name);
    set_occupation(occupation_voulue);
}

void Case::affiche_case(Imagine::Coords<2> pos_case) {
    Imagine::display(frame, pos_case[0] * taille_case, pos_case[1] * taille_case);
}

void Case::affiche_case(int x, int y) {
    Imagine::display(frame, x * taille_case, y * taille_case);
}

// A TESTER : Supposée afficher la description dans une case sur le côté...
/*void Case::affiche_description() {
    Imagine::drawString(zonedescription, nom, Imagine::BLACK, 12, 0, false, true);
    Imagine::drawString(zonedescription + (0, 10), description, Imagine::BLACK);
}*/


// Fonction relative à CarteduMonde.
CarteduMonde::CarteduMonde() : listecase(widthmap, heightmap) {
    pos_centre = (widthmap / 2, heightmap / 2);
    // Pour le moment crée de manière simple la map.
    for (int i = 0; i < widthmap; i++) {
        for (int j = 0; j < heightmap; j++) {
            if (i == j) {
                listecase(i, j).set_case("Etendue d'Eau", INF, "De l'eau, sans vie, sans poisson, rien que de l'eau",
                                         "eau1", false);

            }
            else {
                if (i < 20) {
                    listecase(i, j).set_case("Foret", 3.0f, "C'est vert, les souris s'y cachent, c'est UNE FORET",
                                             "foret1", false);
                }
                else {
                    listecase(i, j).set_case("Lande", 1.0f, "Les choses les plus chiantes du monde...",
                                             "lande1", false);
                }
            }
        }
    }
}

void CarteduMonde::get_pos_centre(Imagine::Coords<2> &pos) {
    pos = pos_centre;
}

void CarteduMonde::affiche() {
    assert(pos_centre[0] * taille_case + widthscreen / 2 - widthmap * taille_case <=
           0);   // le bord droit de l'écran est dans la map.
    assert(pos_centre[1] * taille_case + heightscreen / 2 - heightmap * taille_case <=
           0);  // le bord bas de l'écran est dans la map.
    assert(pos_centre[0] * taille_case - widthscreen / 2 >= 0);    // le bord gauche de l'écran est dans la map.
    assert(pos_centre[1] * taille_case - heightscreen / 2 >= 0);   // le bord haut de l'écran est dans la map.
    for (int i = -widthscreen / taille_case / 2; i < widthscreen / taille_case / 2; i++) {
        for (int j = -heightscreen / taille_case / 2; j < heightscreen / taille_case / 2; j++) {
            listecase(pos_centre[0] + i, pos_centre[1] + j).affiche_case(widthscreen / taille_case / 2 + i,
                                                                         heightscreen / taille_case / 2 + j);
        }
    }
}


void CarteduMonde::deplace(int dir) {
    if (dir == Imagine::KEY_UP && pos_centre[1] * taille_case - heightscreen / 2 > 0) {
        pos_centre[1] -= 1;
        affiche();
    }
    if (dir == Imagine::KEY_DOWN && pos_centre[1] * taille_case + heightscreen / 2 - heightmap * taille_case < 0) {
        pos_centre[1] += 1;
        affiche();
    }
    if (dir == Imagine::KEY_LEFT && pos_centre[0] * taille_case - widthscreen / 2 > 0) {
        pos_centre[0] -= 1;
        affiche();
    }
    if (dir == Imagine::KEY_RIGHT && pos_centre[0] * taille_case + heightscreen / 2 - heightmap * taille_case < 0) {
        pos_centre[0] += 1;
        affiche();
    }
}