#include"map_graph.h"

/*
//Constructeur par défaut.
CarteduMonde::CarteduMonde() : listecase(widthmap, heightmap) {
    pos_centre = (widthmap / 2, heightmap / 2);
    // Pour le moment crée de manière simple la map.
    for (int i = 0; i < widthmap; i++) {
        for (int j = 0; j < heightmap; j++) {
            if (i == j) {
                listecase(i, j).set_Case_Graph("Etendue d'Eau", INF,
                                               "De l'eau, sans vie, sans poisson, rien que de l'eau",
                                               "eau1", false);

            }
            else {
                if (i < 20) {
                    listecase(i, j).set_Case_Graph("Foret", 3.0f, "C'est vert, les souris s'y cachent, c'est UNE FORET",
                                                   "foret1", false);
                }
                else {
                    listecase(i, j).set_Case_Graph("Lande", 1.0f, "Les choses les plus chiantes du monde...",
                                                   "lande1", false);
                }
            }
        }
    }
}


//Assesseur en lecture de la position du centre.
void CarteduMonde::get_pos_centre(Imagine::Coords<2> &pos) {
    pos = pos_centre;
}

//Méthode qui affiche la carte dans le 'world'.
void CarteduMonde::affiche() {
    assert(pos_centre[0] * taille_case_graph + widthworld / 2 - widthmap * taille_case_graph <=
           0);   // le bord droit de l'écran est dans la map.
    assert(pos_centre[1] * taille_case_graph + heightworld / 2 - heightmap * taille_case_graph <=
           0);  // le bord bas de l'écran est dans la map.
    assert(pos_centre[0] * taille_case_graph - widthworld / 2 >= 0);    // le bord gauche de l'écran est dans la map.
    assert(pos_centre[1] * taille_case_graph - heightworld / 2 >= 0);   // le bord haut de l'écran est dans la map.
    for (int i = -width_nombre_case_graph / 2; i < width_nombre_case_graph / 2; i++) {
        for (int j = -height_nombre_case_graph / 2; j < height_nombre_case_graph / 2; j++) {
            listecase(pos_centre[0] + i, pos_centre[1] + j).affiche_Case_Graph(widthworld / taille_case_graph / 2 + i,
                                                                               heightworld / taille_case_graph / 2 + j);
        }
    }
}

//Méthode qui décale l'affichage selon la directio dir voulue.
void CarteduMonde::deplace(int dir) {
    if (dir == Imagine::KEY_UP && pos_centre[1] * taille_case_graph - heightworld / 2 > 0) {
        pos_centre[1] -= 1;
        affiche();
    }
    if (dir == Imagine::KEY_DOWN &&
        pos_centre[1] * taille_case_graph + heightworld / 2 - heightmap * taille_case_graph < 0) {
        pos_centre[1] += 1;
        affiche();
    }
    if (dir == Imagine::KEY_LEFT && pos_centre[0] * taille_case_graph - widthworld / 2 > 0) {
        pos_centre[0] -= 1;
        affiche();
    }
    if (dir == Imagine::KEY_RIGHT &&
        pos_centre[0] * taille_case_graph + heightworld / 2 - heightmap * taille_case_graph < 0) {
        pos_centre[0] += 1;
        affiche();
    }
}
*/