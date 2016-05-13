#include "case_graph.h"

/*
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

    //Affichage dans la 'mmap'.
    Imagine::Color couleur = couleur_case(nom);
    Imagine::fillRect(x * taille_case_mmap + widthworld + (widthui - widthmmap) / 2,
                      y * taille_case_mmap + (widthui - widthmmap) / 2, taille_case_mmap,
                      taille_case_mmap, couleur);
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

    //Affichage dans la 'mmap'.
    Imagine::Color couleur = couleur_case(nom);
    Imagine::fillRect(x * taille_case_mmap + widthworld + (widthui - widthmmap) / 2,
                      y * taille_case_mmap + (widthui - widthmmap) / 2, taille_case_mmap,
                      taille_case_mmap, couleur);
}
*/