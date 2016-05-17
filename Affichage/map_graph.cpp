#include"map_graph.h"

//Fonction qui renvoie true si le point est dans la 'mmap' et false sinon.
bool dans_mmap(Imagine::Coords<2> point) {
    return dans_mmap(point[0], point[1]);
}

//Fonction qui renvoie true si le point est dans la 'mmap' et false sinon.
bool dans_mmap(int x, int y) {
    if (x > widthworld + 2 && x < widthworld + widthmmap && y > 2 && y < heightmmap + 2) {
        return true;
    }
    else {
        return false;
    }
}

//Constructeur par défaut.
CarteduMonde::CarteduMonde() : listecase(widthmap, heightmap),
                               image_map(widthmap * taille_case_graph, heightmap * taille_case_graph),
                               image_mmap(widthmap * taille_case_mmap +
                                          (width_nombre_case_mmap - width_nombre_case_world),
                                          heightmap * taille_case_mmap +
                                          (height_nombre_case_mmap - height_nombre_case_world)) {
    pos_centre = (widthmap / 2, heightmap / 2);
    generation();
    cree_map_mmap();
}

//Générateur de 'map'. Rempli listecase.
void CarteduMonde::generation() {
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

//Rempli image_map et image mmap en fonction de la listecase.
void CarteduMonde::cree_map_mmap() {
    image_mmap.fill(Imagine::BLACK);

    std::string nom_image_voulue;   //Nom de l'image courant.
    std::string nom_voulue; //Nom de la case courant.
    Imagine::Image<Imagine::Color> frame_voulue;    //Frame courante.
    Imagine::Color couleur_voulue;  //Couleur courante.

    for (int i = 0; i < widthmap; i++) {
        for (int j = 0; j < heightmap; j++) {

            nom_image_voulue = listecase(i, j).get_nom_image();
            frame_voulue = entre_image_case(nom_image_voulue);
            nom_voulue = listecase(i, j).get_nom();
            couleur_voulue = entre_couleur_case(nom_voulue);
            //Travail sur 'map'.
            for (int k = 0; k < taille_case_graph; k++) {
                for (int l = 0; l < taille_case_graph; l++) {
                    image_map(i * taille_case_graph + k, j * taille_case_graph + l) = frame_voulue(k, l);
                }
            }
            //Travail sur 'mmap'.
            for (int k = 0; k < taille_case_mmap; k++) {
                for (int l = 0; l < taille_case_mmap; l++) {
                    image_mmap(i * taille_case_mmap + k + (width_nombre_case_mmap - width_nombre_case_world) / 2,
                               j * taille_case_mmap + l +
                               (height_nombre_case_mmap - height_nombre_case_world) / 2) = couleur_voulue;
                }
            }

        }
    }

}


//Assesseur en lecture de la position du centre.
void CarteduMonde::get_pos_centre(Imagine::Coords<2> &pos) {
    pos = pos_centre;
}

//Méthode qui affiche la carte dans le 'world' et la minimap sur la 'mmap'.
void CarteduMonde::affiche() {
    int bord_gauche = pos_centre[0] - width_nombre_case_world / 2;    //En case. Défini le bord gauche du 'world'.
    int bord_droit = pos_centre[0] + width_nombre_case_world / 2;    //En case. Défini le bord droite du 'world'.
    int bord_haut = pos_centre[1] - height_nombre_case_world / 2;    //En case. Défini le bord gauche du 'world'.
    int bord_bas = pos_centre[1] + height_nombre_case_world / 2;    //En case. Défini le bord gauche du 'world'.

    int bord_gauche_graph = bord_gauche * taille_case_graph;    //En pixel. Défini le bord gauche du 'world'.
    int bord_droit_graph = bord_droit * taille_case_graph;    //En pixel. Défini le bord droite du 'world'.
    int bord_haut_graph = bord_haut * taille_case_graph;    //En pixel. Défini le bord gauche du 'world'.
    int bord_bas_graph = bord_bas * taille_case_graph;    //En pixel. Défini le bord gauche du 'world'.

    int bord_gauche_mmap = bord_gauche * taille_case_mmap;    //En pixel. Défini le bord gauche du 'world'.
    int bord_droit_mmap = bord_droit * taille_case_mmap;    //En pixel. Défini le bord droite du 'world'.
    int bord_haut_mmap = bord_haut * taille_case_mmap;    //En pixel. Défini le bord gauche du 'world'.
    int bord_bas_mmap = bord_bas * taille_case_mmap;    //En pixel. Défini le bord gauche du 'world'.

    //Affichage du 'world'.
    assert(bord_droit - widthmap <= 0);   //Le bord droit du 'world' est dans la 'map'.
    assert(bord_bas - heightmap <= 0);  //Le bord bas du 'world' est dans la 'map'.
    assert(bord_gauche >= 0);    //Le bord gauche du 'world' est dans la 'map'.
    assert(bord_haut >= 0);   //Le bord haut du 'world' est dans la 'map'.

    //Affichage du 'world'.
    Imagine::Image<Imagine::Color> world_affiche;
    world_affiche = image_map.getSubImage(bord_gauche_graph, bord_haut_graph, widthworld, heightworld);
    Imagine::display(world_affiche, 0, 0);

    //Affichage de l'encadrement des cases.
    for (int j = 0; j < height_nombre_case_world; j++) {
        Imagine::drawLine(0, j * taille_case_graph, widthworld, j * taille_case_graph, gris);
    }
    for (int i = 0; i < width_nombre_case_world; i++) {
        Imagine::drawLine(i * taille_case_graph, 0, i * taille_case_graph, heightworld, gris);
    }


    //Affichage de la 'mmap'.
    Imagine::Image<Imagine::Color> mmap_affiche;
    mmap_affiche = image_mmap.getSubImage(bord_gauche_mmap, bord_haut_mmap, widthmmap, heightmmap);
    Imagine::display(mmap_affiche, widthworld + (widthui - widthmmap) / 2, (widthui - widthmmap) / 2);

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