#include "case_graph.h"


/*
//Constructeur par défaut.
Case_Graph::Case_Graph() {
    nom = "Vide";
}

//Assesseur en lecture de l'attribut nom.
const char *Case_Graph::get_nom() {
    return nom;
}

//Assesseur en lecture de l'attribut description.
std::string Case_Graph::get_description() {
    return description;
}

//Assesseur en lecture de l'attribut nom_image.
std::string Case_Graph::get_nom_image() {
    return nom_image;
}

//Assesseur en écriture de l'attribut nom.
void Case_Graph::set_nom(char *nom_voulu) {
    nom = nom_voulu;
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

//Méthode qui modifie l'intégralité des paramètres de la case.
void Case_Graph::set_Case_Graph(char *nom_voulu, std::string description_voulue, const char *nom_image_voulue) {
    set_nom(nom_voulu);
    set_description(description_voulue);
    set_nom_image(nom_image_voulue);
    set_frame(nom_image_voulue);
}

void Case_Graph::affiche(int x, int y, CarteduMonde carte) const{
    int xp = x - carte.get_pos_centre()[0] + widthworld / 2;
    int yp = y - carte.get_pos_centre()[1] + heightworld / 2;
    Imagine::display(frame, xp, yp);
    Imagine::drawRect(xp, yp, taille_case_graph, taille_case_graph, gris, 1);
}*/