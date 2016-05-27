#pragma once

#include "constante.h"
#include "ecran.h"
#include "map_graph.h"

//Fonction qui renvoie la couleur liée au camp.
Imagine::Color camp_color(int camp);

const Bouton personnage(widthworld + 2, heightmmap + 4, widthscreen - 2, heightmmap + 20, std::string("Personnage"), 1);
const Bouton action(widthworld + 2, heightmmap + 22, widthscreen - 2, heightmmap + 38, std::string("Action"), 1);

class Heros_Graph {
private:
    const char *nom;    // Nom du héros.
    std::string nom_image;  // Nom de l'image.
    Imagine::Image<Imagine::Color> frame;   // Image du pion.
    Imagine::Coords<2> position;    // Position du pion sur la 'map'. En case.
    int camp;   // Camp du héros.
public:
    //Constructeur par défaut.
    Heros_Graph();

    //Assesseur en lecture de l'attribut nom.
    const char *get_nom();

    //Assesseur en lecture de l'attribut nom_image.
    std::string get_nom_image();

    //Assesseur en lecture de l'attribut occupation.
    Imagine::Coords<2> get_position();

    //Assesseur en lecture de l'attribut camp.
    int get_camp();

    //Assesseur en écriture de l'attribut nom.
    void set_nom(char *nom_voulu);

    //Assesseur en écriture de l'attribut nom_image.
    void set_nom_image(const char *nom_image_voulue);

    //Assesseur en écriture de l'attribut frame.
    void set_frame(const char *nom_image_voulue);

    //Assesseur en écriture de l'attribut occupation. Prend des Coords en argument pour déterminer la position voulue.
    void set_position(Imagine::Coords<2> position_voulue);

    //Assesseur en écriture de l'attribut occupation. Prend des int en argument pour déterminer la position voulue.
    void set_position(int posx, int poxy);

    //Assesseur en écriture de l'attribut camp.
    void set_camp(int camp_voulu);

    //Méthode qui modifie l'intégralité des paramètres du héros. Prend des Coords en argument pour déterminer la position voulue.
    void set_Heros_Graph(char *nom_voulu, const char *name, Imagine::Coords<2> position_voulue, int camp_voulu);

    //Méthode qui modifie l'intégralité des paramètres du héros. Prend des int en argument pour déterminer la position voulue.
    void set_Heros_Graph(char *nom_voulu, const char *name, int posx, int posy, int camp_voulu);

    //Méthode qui affiche le héros à sa position.
    void affiche_heros(CarteduMonde carte);

    //Méthode qui affiche les boutons relatifs au héros.
    void affiche_interface_heros();

    //Méthode qui affiche les cases disponibles au héros.
    void affiche_case_dispo();
};

