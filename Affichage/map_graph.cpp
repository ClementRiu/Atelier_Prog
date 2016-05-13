#include"map_graph.h"

//Constructeur par défaut.
CarteduMonde::CarteduMonde() : listecase(widthmap, heightmap) {
    pos_centre = (widthmap / 2, heightmap / 2);
    // Pour le moment crée de manière simple la map.
    for (int i = 0; i < widthmap; i++) {
        for (int j = 0; j < heightmap; j++) {
            if (i == j) {
                listecase(i, j).set_Case_Graph("Etendue d'Eau", "De l'eau, sans vie, sans poisson, rien que de l'eau",
                                               "eau1", false);

            }
            else {
                if (i < 20) {
                    listecase(i, j).set_Case_Graph("Foret", "C'est vert, les souris s'y cachent, c'est UNE FORET",
                                                   "foret1", false);
                }
                else {
                    listecase(i, j).set_Case_Graph("Lande", "Les choses les plus chiantes du monde...", "lande1",
                                                   false);
                }
            }
        }
    }
    listecase(widthmap / 2, heightmap / 2).set_Case_Graph("Foret",
                                                          "C'est vert, les souris s'y cachent, c'est UNE FORET",
                                                          "foret1", false);
}


//Assesseur en lecture de la position du centre.
void CarteduMonde::get_pos_centre(Imagine::Coords<2> &pos) {
    pos = pos_centre;
}

//Méthode qui affiche la carte dans le 'world' et la minimap sur la 'mmap'.
void CarteduMonde::affiche() {
    //Affichage du 'world'.
    assert(pos_centre[0] * taille_case_graph + widthworld / 2 - widthmap * taille_case_graph <=
           0);   // le bord droit de l'écran est dans la map.
    assert(pos_centre[1] * taille_case_graph + heightworld / 2 - heightmap * taille_case_graph <=
           0);  // le bord bas de l'écran est dans la map.
    assert(pos_centre[0] * taille_case_graph - widthworld / 2 >= 0);    // le bord gauche de l'écran est dans la map.
    assert(pos_centre[1] * taille_case_graph - heightworld / 2 >= 0);   // le bord haut de l'écran est dans la map.
    for (int i = -width_nombre_case_world / 2; i < width_nombre_case_world / 2; i++) {
        for (int j = -height_nombre_case_world / 2; j < height_nombre_case_world / 2; j++) {
            listecase(pos_centre[0] + i, pos_centre[1] + j).affiche_Case_Graph(widthworld / taille_case_graph / 2 + i,
                                                                               heightworld / taille_case_graph / 2 + j);
        }
    }
    //Affichage de la 'mmap'.
    for (int i = -width_nombre_case_mmap / 2; i < width_nombre_case_mmap / 2; i++) {
        for (int j = -height_nombre_case_mmap / 2; j < height_nombre_case_mmap / 2; j++) {
            if ((pos_centre[0] + i > 0) && (pos_centre[0] + i < widthmap) && (pos_centre[1] + j > 0) &&
                (pos_centre[1] + j < heightmap)) {
                listecase(pos_centre[0] + i, pos_centre[1] + j).affiche_mmap(widthmmap / 2 + i, heightmmap / 2 + j);
            }
            else {
                Case_Graph Black;
                Black.affiche_mmap(widthmmap / 2 + i, heightmmap / 2 + j);
            }
        }
    }
    //Encadrement de la zone correspondant au 'world' dans 'mmap'.
    Imagine::drawRect(
            widthworld + (widthui - widthmmap) / 2 + (widthmmap - width_nombre_case_world * taille_case_mmap) / 2 - 1,
            (widthui - widthmmap) / 2 + (widthmmap - width_nombre_case_world * taille_case_mmap) / 2 - 1,
            width_nombre_case_world * taille_case_mmap + 2, height_nombre_case_world * taille_case_mmap + 2,
            Imagine::BLACK);
}

//Méthode qui décale l'affichage selon la directio dir voulue.
void CarteduMonde::deplace_clavier(int dir) {
    if (dir == Imagine::KEY_UP && pos_centre[1] - height_nombre_case_world / 2 > 0) {
        pos_centre[1] -= 1;
        affiche();
    }
    if (dir == Imagine::KEY_DOWN &&
        pos_centre[1] + height_nombre_case_world / 2 - heightmap < 0) {
        pos_centre[1] += 1;
        affiche();
    }
    if (dir == Imagine::KEY_LEFT && pos_centre[0] - width_nombre_case_world / 2 > 0) {
        pos_centre[0] -= 1;
        affiche();
    }
    if (dir == Imagine::KEY_RIGHT &&
        pos_centre[0] + width_nombre_case_world / 2 - widthmap < 0) {
        pos_centre[0] += 1;
        affiche();
    }
}

//Méthode qui place pos_centre au coordonnée voulue et réaffiche le 'world' et la 'mmap'. Prend des Coords en argument pour déterminer la position voulue.
void CarteduMonde::deplace_souris(Imagine::Coords<2> pos_voulue) {
    deplace_souris(pos_voulue[0], pos_voulue[1]);
}

//Méthode qui place pos_centre au coordonnée voulue et réaffiche le 'world' et la 'mmap'. Prend des int en argument pour déterminer la position voulue.
void CarteduMonde::deplace_souris(int x, int y) {
    if (y - height_nombre_case_world / 2 < 0) {
        y = height_nombre_case_world / 2;
    }
    if (y + height_nombre_case_world / 2 - heightmap > 0) {
        y = heightmap - height_nombre_case_world / 2;
    }
    if (x - width_nombre_case_world / 2 < 0) {
        x = width_nombre_case_world / 2;
    }
    if (x + width_nombre_case_world / 2 - widthmap > 0) {
        x = widthmap - width_nombre_case_world / 2;
    }
    pos_centre[0] = x;
    pos_centre[1] = y;
    affiche();
}