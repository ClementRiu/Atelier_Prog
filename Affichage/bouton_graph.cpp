#include "bouton_graph.h"


//Constructeur par défaut.
Bouton_Graph::Bouton_Graph() {
    nom = "Vide";
    type = 2;
    for (int i = 0; i < 4; i++) {
        zonebouton[i] = 0;
    }

}

//Méthode qui initialise tous les attributs.
void Bouton_Graph::set_Bouton_Graph(std::string nom_voulu, int type_voulue, int zonebouton_voulue[]){
    nom = nom_voulu;
    type = type_voulue;
    for (int i = 0; i < 4; i++) {
        zonebouton[i] = zonebouton_voulue[i];
    }
    if (type == 0){
        calcul_image();
    }
}

//Assesseur en lecture de l'attribut type.
int Bouton_Graph::get_type() {
    return type;
}

//Assesseur en écriture de l'attribut zonebouton.
void Bouton_Graph::set_zonebouton(int zonebout_voulue[]) {
    for (int i = 0; i < 4; i++) {
        zonebouton[i] = zonebout_voulue[i];
    }
}

//Assesseur en écriture de l'attribut type.
void Bouton_Graph::set_type(int type_voulue) {
    type = type_voulue;
}

//Méthode qui renvoie la largeur du bouton.
int Bouton_Graph::get_largeur() {
    return zonebouton[2] - zonebouton[0];
}

//Méthode qui renvoie la largeur du bouton.
int Bouton_Graph::get_hauteur() {
    return zonebouton[3] - zonebouton[1];
}

//Méthode qui crée l'image image_bouton en fonction de la zone où va s'afficher le bouton.
void Bouton_Graph::calcul_image() {
    if (type == 0) {
        image_bouton = pierre_bouton.getSubImage(zonebouton[0], zonebouton[1], get_largeur(), get_hauteur());
    }
    if (type == 1) {
        Imagine::Color *window;
        int w, h;
        Imagine::captureWindow(window, w, h);
        w = get_largeur();
        h = get_hauteur();
        Imagine::Image<Imagine::Color> window_im(w, h);
        for (int i = zonebouton[0]; i < zonebouton[0] + w; i++) {
            for (int j = zonebouton[1]; j < zonebouton[1] + h; j++) {
                window_im(i, j) = window[i, j];
            }
        }
        delete window;
        for (int i = 0; i < w; i++){
            for (int j = 0; j < h; j++){
                for (int k=0; k<3;k++){
                    window_im(i,j)[k] = byte(window_im(i,j)[k] * 0.6);
                }
            }
        }
        image_bouton = window_im;
    }
}

//Méthode qui affiche le bouton à sa position.
void Bouton_Graph::affiche_Bouton_Graph() {
    Imagine::display(image_bouton,zonebouton[0],zonebouton[1]);
    Imagine::drawString(zonebouton[0]+100, zonebouton[1]+21, nom, Imagine::BLACK);
}


Bouton::Bouton(int xmin, int ymin, int xmax, int ymax, std::string nom, int type) {
    zoneDeDelimitation[0] = xmin;
    zoneDeDelimitation[1] = ymin;
    zoneDeDelimitation[2] = xmax;
    zoneDeDelimitation[3] = ymax;
    nomBouton = nom;
    taillePolice = 0;
    boutonaff.set_Bouton_Graph(nom, type, zoneDeDelimitation);
}


Bouton::Bouton(const int zone[4], std::string nom, int type) {
    zoneDeDelimitation[0] = zone[0];
    zoneDeDelimitation[1] = zone[1];
    zoneDeDelimitation[2] = zone[2];
    zoneDeDelimitation[3] = zone[3];
    nomBouton = nom;
    taillePolice = 0;
    boutonaff.set_Bouton_Graph(nom, type, zoneDeDelimitation);
}


int Bouton::largeur() {
    return zoneDeDelimitation[2] - zoneDeDelimitation[0];
}


int Bouton::hauteur() {
    return zoneDeDelimitation[3] - zoneDeDelimitation[1];
}


// Permet d'afficher le bouton avec la largeur maximale possible pour l'écriture
void Bouton::affiche_graph(int decalementVertical){
    boutonaff.affiche_Bouton_Graph();
}

bool Bouton::boutonActive(int x, int y, int decalementVertical) {
    if (x > zoneDeDelimitation[0] && y > zoneDeDelimitation[1] + decalementVertical &&
        x < zoneDeDelimitation[2] && y < zoneDeDelimitation[3] + decalementVertical) {
        return true;
    }
    return false;
}


bool Bouton::boutonVide() {
    return (largeur() == 0 || hauteur() == 0);
}


void Bouton::setNom(std::string nom) {
    nomBouton = nom;
}

