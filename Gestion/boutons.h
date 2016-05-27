/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Heroes of Ponts&Chaussées                                                                                           *
 *                                                                                                                     *
 * Jeu développé dans le cadre du module Atelier de Programmation de première année de l'École des Ponts               *
 *                                                                                                                     *
 * AUTEURS :                                                                                                           *
 *      Charles    AUGUSTE                                                                                             *
 *      Nathanaël  GROSS-HUMBERT                                                                                       *
 *      Clément    RIU                                                                                                 *
 *      Anne       SPITZ                                                                                               *
 *                                                                                                                     *
 * Rendu le 27 Mai 2016                                                                                                *
 *                                                                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#ifndef BOUTONS_H
#define BOUTONS_H

#include "carte.h"

const int ZoneBoutonFinTour[4] =    {NbCase * Taille + Separation, Taille * (NbCase - 5),
                                     NbCase * Taille + Separation + LargDroite, NbCase * Taille};
const int ZoneBoutonSauvegarde[4] = {NbCase * Taille + Separation, Taille * (NbCase - 5) - LargDroite - 10,
                                     NbCase * Taille + Separation + LargDroite, Taille * (NbCase - 5)};
const int ZoneBoutonOui[4] =        {Taille * NbCase / 2, Taille * NbCase / 3, 3 * Taille * NbCase / 4,
                                     3 * Taille * NbCase / 4};
const int ZoneBoutonNon[4] =        {Taille * NbCase / 4, Taille * NbCase / 3, Taille * NbCase / 2, 3 * Taille * NbCase / 4};
const int ZoneBoutonQuestion[4] =   {Taille * NbCase / 4, Taille * NbCase / 4, 3 * Taille * NbCase / 4,
                                     3 * Taille * NbCase / 4,};
const int ZoneBoutonAction[4] =     {0, NbCase * Taille - Taille * 1, Taille * 3, NbCase * Taille};
const int ZoneBoutonInventaire[4] = {Taille * 3, NbCase * Taille - Taille * 1, Taille * 6, NbCase * Taille};


class Bouton {
    int zoneDeDelimitation[4]; // Tableau de la forme [xmin, ymin, xmax, ymax]
    Imagine::Color image; // A remplacer par une image
    std::string nomBouton;
    int taillePolice;
    //PARTIE GRAPHIQUE SUPPLEMENTAIRE :
    //Bouton_Graph boutonaff; //Objet d'affichage.
public:
    Bouton(int xmin, int ymin, int xmax, int ymax, Imagine::Color c, std::string nom);

    Bouton(const int zone[4], Imagine::Color c, std::string nom);

    /**
     * @return la largeur du bouton
     */
    int largeur() const;

    /**
     * @return la hauteur du bouton
     */
    int hauteur() const;

    /**
     * Permet d'afficher le bouton avec la police maximale possible pour l'écriture
     * @param decalementVertical : dans l'inventaire, détermine à quelle hauteur on doit afficher les boutons lorsqu'on
     *                             fait défiler des objets
     */
    void affiche(int decalementVertical = 0) const;

    /**
     * Permet de savoir si un bouton a été activé par le joueur ou non
     * @param x
     * @param y
     * @param decalementVertical : dans l'inventaire, détermine à quelle hauteur on doit afficher les boutons lorsqu'on
     *                             fait défiler les objets
     * @return true si le point de coordonnées (x, y) est dans la zone de délimination de bouton
     *         false sinon
     */
    bool boutonActive(int x, int y, int decalementVertical = 0) const;

    /**
     * @return true si le bouton est vide
     *         false
     */
    bool boutonVide() const;

    void setNom(std::string nom);
};

#endif
