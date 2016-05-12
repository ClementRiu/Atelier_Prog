#include "outilsaff.h"


//Cette fonction trace l'interface graphique.
void interface() {
    Imagine::display(fond_ecran, 0, 0);
    Imagine::drawRect(widthworld + (widthui - widthmmap) / 2 - 1, (widthui - widthmmap) / 2 - 1, widthmmap + 1,
                      heightmmap + 1, Imagine::BLACK, 1);
}

//Renvoi la couleur pour la 'mmap' en fonction du type de la case.
Imagine::Color couleur_case(std::string nom) {
    if (nom == std::string("Etendue d'Eau")) {
        return Imagine::BLUE;
    }
    if (nom == std::string("Foret")) {
        return Imagine::GREEN;
    }
    if (nom == std::string("Lande")) {
        return Imagine::YELLOW;
    }
    if (nom == std::string("Vide")) {
        return Imagine::BLACK;
    }
}


//Constructeur par défaut.
Case_Graph::Case_Graph() {
    nom = "Vide";
    p_dep = INF;
}

//Assesseur en lecture de l'attribut nom.
const char *Case_Graph::get_nom() {
    return nom;
}

//Assesseur en lecture de l'attribut p_dep.
float Case_Graph::get_poids() {
    return p_dep;
}

//Assesseur en lecture de l'attribut description.
std::string Case_Graph::get_description() {
    return description;
}

//Assesseur en lecture de l'attribut nom_image.
std::string Case_Graph::get_nom_image() {
    return nom_image;
}

//Assesseur en lecture de l'attribut occupation.
bool Case_Graph::get_occupation() {
    return occupation;
}

//Assesseur en écriture de l'attribut nom.
void Case_Graph::set_nom(char *nom_voulu) {
    nom = nom_voulu;
}

//Assesseur en écriture de l'attribut p_dep.
void Case_Graph::set_p_deb(float poids_voulu) {
    p_dep = poids_voulu;
}

//Assesseur en écriture de l'attribut description.
void Case_Graph::set_description(std::string description_voulue) {
    description = description_voulue;
}

//Assesseur en écriture de l'attribut nom_image.
void Case_Graph::set_nom_image(const char *nom_image_voulue) {
    nom_image = std::string(nom_image_voulue);
}

//Assesseur en écriture de l'attribut frame.
void Case_Graph::set_frame(const char *nom_image_voulue) {
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

//Assesseur en écriture de l'attribut occupation.
void Case_Graph::set_occupation(bool occupation_voulue) {
    occupation = occupation_voulue;
}

//Méthode qui modifie l'intégralité des paramètres de la case.
void Case_Graph::set_Case_Graph(char *nom_voulu, float poids_voulu, std::string description_voulue, const char *name,
                                bool occupation_voulue) {
    set_nom(nom_voulu);
    set_p_deb(poids_voulu);
    set_description(description_voulue);
    set_frame(name);
    set_occupation(occupation_voulue);
}

//Méthode qui affiche la case à sa position, encadré d'un carré de couleur 'gris'. Prend des Coords en argument pour déterminer sa position.
void Case_Graph::affiche_Case_Graph(Imagine::Coords<2> pos_case) {
    affiche_Case_Graph(pos_case[0], pos_case[1]);
}

//Méthode qui affiche la case à sa position, encadré d'un carré de couleur 'gris'. Prend des int en argument pour déterminer sa position.
void Case_Graph::affiche_Case_Graph(int x, int y) {
    //Affichage dans le 'world'.
    Imagine::display(frame, x * taille_case_graph, y * taille_case_graph);
    Imagine::drawRect(x * taille_case_graph, y * taille_case_graph, taille_case_graph - 1, taille_case_graph - 1, gris,
                      1);
}

//Méthode qui affiche la case dans la 'mmap'. Prend des Coords en argument pour déterminer sa position.
void Case_Graph::affiche_mmap(Imagine::Coords<2> pos_case) {
    affiche_mmap(pos_case[0], pos_case[1]);
}

//Méthode qui affiche la case dans la 'mmap'. Prend des int en argument pour déterminer sa position.
void Case_Graph::affiche_mmap(int x, int y) {
    Imagine::Color couleur = couleur_case(nom);
    Imagine::fillRect(x * taille_case_mmap + widthworld + (widthui - widthmmap) / 2,
                      y * taille_case_mmap + (widthui - widthmmap) / 2, taille_case_mmap, taille_case_mmap, couleur);
}


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
    listecase(widthmap / 2, heightmap / 2).set_Case_Graph("Foret", 3.0f,
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