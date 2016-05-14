#ifndef BOUTONS_H
#define BOUTONS_H

#include "carte.h"
#include "../Affichage/include_graph.h"

const int ZoneBoutonFinTour[4] = {NbCase * Taille + Separation, Taille * (NbCase - 5),
                                  NbCase * Taille + Separation + LargDroite, NbCase * Taille};
const int ZoneBoutonSauvegarde[4] = {NbCase * Taille + Separation, Taille * (NbCase - 5) - LargDroite - 10,
                                     NbCase * Taille + Separation + LargDroite, Taille * (NbCase - 5)};
const int ZoneBoutonOui[4] = {Taille * NbCase / 2, Taille * NbCase / 3, 3 * Taille * NbCase / 4,
                              3 * Taille * NbCase / 4};
const int ZoneBoutonNon[4] = {Taille * NbCase / 4, Taille * NbCase / 3, Taille * NbCase / 2, 3 * Taille * NbCase / 4};
const int ZoneBoutonQuestion[4] = {Taille * NbCase / 4, Taille * NbCase / 4, 3 * Taille * NbCase / 4,
                                   3 * Taille * NbCase / 4,};
const int ZoneBoutonAction[4] = {0, NbCase * Taille - Taille * 1, Taille * 3, NbCase * Taille};
const int ZoneBoutonInventaire[4] = {Taille * 3, NbCase * Taille - Taille * 1, Taille * 6, NbCase * Taille};


class Bouton {
    int zoneDeDelimitation[4]; // Tableau de la forme [xmin, ymin, xmax, ymax]
    Imagine::Color image; // A remplacer par une image #Clement
    std::string nomBouton;
    int taillePolice;
    //PARTIE GRAPHIQUE SUPPLEMENTAIRE :
    //Bouton_Graph boutonaff; //Objet d'affichage.
public:
    Bouton(int xmin, int ymin, int xmax, int ymax, Imagine::Color c, std::string nom);

    Bouton(const int zone[4], Imagine::Color c, std::string nom);

    // Renvoie la largeur du bouton
    int largeur();

    // renvoie la la hauteur du bouton
    int hauteur();

    // A changer
    // Permet d'afficher le bouton avec la largeur maximale possible pour l'écriture
    void affiche(int decalementVertical = 0);

    // Renvoie un true si le point (x, y) est dans la zone de delimitation du bouton et false sinon
    bool boutonActive(int x, int y, int decalementVertical = 0);

    // Regarde si le bouton est vide
    bool boutonVide();

    void setNom(std::string nom);
};

#endif