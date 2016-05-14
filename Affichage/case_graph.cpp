#include "case_graph.h"
#include "outilsaff.h"



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

//Assesseur en lecture de l'attribut occupation.
bool Case_Graph::get_occupation() {
    return occupation;
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

//Assesseur en écriture de l'attribut occupation.
void Case_Graph::set_occupation(bool occupation_voulue) {
    occupation = occupation_voulue;
}

//Méthode qui modifie l'intégralité des paramètres de la case.
void Case_Graph::set_Case_Graph(char *nom_voulu, std::string description_voulue, const char *nom_image_voulue,
                                bool occupation_voulue) {
    set_nom(nom_voulu);
    set_description(description_voulue);
    set_nom_image(nom_image_voulue);
    set_frame(nom_image_voulue);
    set_occupation(occupation_voulue);
}