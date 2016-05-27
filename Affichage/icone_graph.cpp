#include "icone_graph.h"

//Fonction qui renvoie la couleur liée au camp.
Imagine::Color camp_color(int camp) {
    if (camp == 1) {
        return Imagine::BLUE;
    }
    if (camp == 2) {
        return Imagine::RED;
    }
}


//Constructeur par défaut.
Heros_Graph::Heros_Graph() {
    nom = "Vide";
    position[0] = -1;
    position[1] = -1;
    camp = -1;
}

//Assesseur en lecture de l'attribut nom.
const char *Heros_Graph::get_nom() {
    return nom;
}

//Assesseur en lecture de l'attribut nom_image.
std::string Heros_Graph::get_nom_image() {
    return nom_image;
}

//Assesseur en lecture de l'attribut occupation.
Imagine::Coords<2> Heros_Graph::get_position() {
    return position;
}

//Assesseur en lecture de l'attribut camp.
int Heros_Graph::get_camp() {
    return camp;
}

//Assesseur en écriture de l'attribut nom.
void Heros_Graph::set_nom(char *nom_voulu) {
    nom = nom_voulu;
}

//Assesseur en écriture de l'attribut nom_image.
void Heros_Graph::set_nom_image(const char *nom_image_voulue) {
    nom_image = nom_image_voulue;
}

//Assesseur en écriture de l'attribut frame.
void Heros_Graph::set_frame(const char *nom_image_voulue) {
    if (nom_image_voulue == std::string("Heros_bleu")) {
        frame = heros1;
        double dim = 0.9 * double(taille_case_graph) / double(std::max(frame.height(), frame.width()));
        frame = Imagine::reduce(frame, 1 / dim);
    }
    if (nom_image_voulue == std::string("Heros_rouge")) {
        frame = heros2;
        double dim = 0.9 * double(taille_case_graph) / double(std::max(frame.height(), frame.width()));
        frame = Imagine::reduce(frame, 1 / dim);
    }

}

//Assesseur en écriture de l'attribut occupation. Prend des Coords en argument pour déterminer la position voulue.
void Heros_Graph::set_position(Imagine::Coords<2> position_voulue) {
    set_position(position_voulue[0], position_voulue[1]);
}

//Assesseur en écriture de l'attribut occupation. Prend des int en argument pour déterminer la position voulue.
void Heros_Graph::set_position(int posx, int posy) {
    position[0] = posx;
    position[1] = posy;
}

//Assesseur en écriture de l'attribut camp.
void Heros_Graph::set_camp(int camp_voulu) {
    camp = camp_voulu;
}

//Méthode qui modifie l'intégralité des paramètres du héros. Prend des Coords en argument pour déterminer la position voulue.
void Heros_Graph::set_Heros_Graph(char *nom_voulu, const char *name, Imagine::Coords<2> position_voulue,
                                  int camp_voulu) {
    set_Heros_Graph(nom_voulu, name, position_voulue[0], position_voulue[1], camp_voulu);
}

//Méthode qui modifie l'intégralité des paramètres du héros. Prend des int en argument pour déterminer la position voulue.
void Heros_Graph::set_Heros_Graph(char *nom_voulu, const char *name, int posx, int posy, int camp_voulu) {
    set_nom(nom_voulu);
    set_nom_image(name);
    set_frame(name);
    set_position(posx, posy);
    set_camp(camp_voulu);
}

//Méthode qui affiche le héros à sa position.
void Heros_Graph::affiche_heros(CarteduMonde carte) {
    Imagine::Coords<2> pos_heros = position - carte.get_pos_centre();
    Imagine::display(frame, pos_heros[0] * taille_case_graph + widthworld / 2 + 1 , pos_heros[1] * taille_case_graph + heightworld / 2 + 2);
    Imagine::drawRect(widthworld + 2 + pos_heros[0] * taille_case_mmap + widthmmap / 2, 2 + pos_heros[1] * taille_case_mmap + heightmmap / 2,
                      taille_case_mmap, taille_case_mmap, camp_color(camp));
}

//Méthode qui affiche les boutons relatifs au héros.
void Heros_Graph::affiche_interface_heros(){
    personnage.affiche_graph();
    action.affiche_graph();
}

//Méthode qui affiche les cases disponibles au héros.
void Heros_Graph::affiche_case_dispo(){

}
