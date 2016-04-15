#include "outilsaff.h"
#include <Imagine/Graphics.h>
#include <Imagine/Images.h>


// Fonction relative à Case.
Case::Case() {
    nom = "Vide";
    p_dep = INF;
}

//Constructeur qui met toute les variables comme il faut (et vérifie que l'image voulue existe).
Case::Case(std::string nom, float p_dep, std::string description, const char *nomfichier) {
    nom = nom;
    p_dep = p_dep;
    description = description;
    occupation = false;
    std::string nomfichierstr = nomfichier;
    if (!(Imagine::load(frame, stringSrcPath(nomfichierstr)))) {
        std::cout << "Image non trouvée." << std::endl;
    }
}

std::string Case::get_nom() {
    return nom;
}

float Case::get_poids() {
    return p_dep;
}

std::string Case::get_description() {
    return description;
}

bool Case::get_occupation() {
    return occupation;
}

void Case::set_nom(std::string nom_voulu) {
    nom = nom_voulu;
}

void Case::set_p_deb(float poids_voulu) {
    p_dep = poids_voulu;
}

void Case::set_description(std::string description_voulue) {
    description = description_voulue;
}

void Case::set_frame(const char *nomfichier) {
    std::string nomfichierstr = nomfichier;
    if (!Imagine::load(frame, stringSrcPath(nomfichierstr))) {
        std::cout << "Image non trouvée." << std::endl;
    }
}

void Case::set_occupation(bool occupation_voulue) {
    occupation = occupation_voulue;
}

void Case::affiche_case(int pos_casex, int pos_casey) {
    Imagine::display(frame, pos_casex * taille_case, pos_casey * taille_case);
}

// A TESTER : Supposée afficher la description dans une case sur le côté...
void Case::affiche_description() {
    Imagine::drawString(zonedescription, nom, Imagine::BLACK, 12, 0, false, true);
    Imagine::drawString(zonedescription + (0, 10), description, Imagine::BLACK);
}


// Fonction relative à CarteduMonde.
CarteduMonde::CarteduMonde() : listecase(widthmap, heightmap) {
    pos_centre = (widthmap / 2, heightmap / 2);
    // Pour le moment crée de manière simple la map.
    for (int i = 0; i < widthmap; i++) {
        for (int j = 0; j < heightmap; j++) {
            if (i == j) {
                listecase(i, j) = Case("Etendue d'Eau", INF, "De l'eau, sans vie, sans poisson, rien que de l'eau",
                                       "water_texture.jpg");
            }
            else {
                if (i < 5) {
                    listecase(i, j) = Case("Foret", 3, "C'est vert, les souris s'y cachent, c'est UNE FORET",
                                           "forest_texture.jpg");
                }
                else {
                    listecase(i, j) = Case("Lande", 1, "Les choses les plus chiantes du monde...", "moor_texture.jpg");
                }
            }

        }
    }
}

// A REGLER : n'affiche pas la première ligne...
void CarteduMonde::affiche() {
    for (int i = -widthmap / 2; i < widthmap / 2; i++) {
        for (int j = -heightmap / 2 + 1; j < heightmap / 2; j++) {
            listecase(pos_centre[0] + i, pos_centre[1] + j).affiche_case(pos_centre[0] + i, pos_centre[1] + j);
        }
    }
}