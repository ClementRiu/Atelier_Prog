#pragma once

#include "constante.h"


class Case_Graph {
private:
    const char *nom;  // Nom de la case.
    std::string description;  // Texte à afficher sur le côté.
    std::string nom_image;    // Nom de l'image.
    Imagine::Image<Imagine::Color> frame;   // Image de la case.
public:
    //Constructeur par défaut.
    Case_Graph();

    //Assesseur en lecture de l'attribut nom.
    const char *get_nom();

    //Assesseur en lecture de l'attribut description.
    std::string get_description();

    //Assesseur en lecture de l'attribut nom_image.
    std::string get_nom_image();

    //Assesseur en écriture de l'attribut nom.
    void set_nom(char *nom_voulu);

    //Assesseur en écriture de l'attribut description.
    void set_description(std::string description_voulue);

    //Assesseur en écriture de l'attribut nom_image.
    void set_nom_image(const char *nom_image_voulue);

    //Assesseur en écriture de l'attribut frame.
    void set_frame(const char *nom_image_voulue);

    //Méthode qui modifie l'intégralité des paramètres de la case.
    void set_Case_Graph(char *nom_voulu, std::string description_voulue, const char *name);
};