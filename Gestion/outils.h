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

#ifndef OUTILS_H
#define OUTILS_H

#include <iostream>
#include "unite.h"

void sauvegarde(std::vector<Unite*> unites);
void charge(std::vector<Unite*> & unites, Carte& carte);

std::string intToString(int a);

// Fonction renvoyant en référence dans x et y la position d'un clic et affichant les cases survolees
/**
 * Fonction qui renvoie en référence dans x et y la position d'un clic et affiche les cases survolées
 * @param x position du clic
 * @param y position du clic
 * @param carte
 */
void clic(int &x, int &y, Carte& carte);

/**
 * Fonction qui renvoie en référence dans x et y la position d'un clic
 * @param x
 * @param y
 * @return
 */
int clicSimple(int &x, int &y);

/**
 * Renvoie en référence les coordonnées de la case survolée par la souris
 * @param x
 * @param y
 */
void survole(int &x, int &y);

/**
 * Affiche dans le menu de droite la case survolée et les renseignements sur l'unité survolée (PV)
 * @param x
 * @param y
 * @param carte
 */
void afficheCaseSurvole(int x, int y, Carte& carte);

/**
 * Affiche le numéro du tour dans le menu de droite
 * @param tour : numéro du tour en cours
 */
void afficheNombreTours(int tour);

/**
 * Affiche le nom du Joueur en train de jouer (permet de se répérer pour savoir qui joue...)
 * @param idJoueur
 */
void afficheTourJoueur(int idJoueur);


/**
 *
 * @param x : abcisse du clic effectué en amont
 * @param y : ordonnée du clic effectué en amont
 * @param carte
 * @param differentsChemins : un vecteur contenant des chemins (eux mêmes des vecteurs de numéros de case)
 * @param numcase : position du héros
 */
void afficheChemins(int x, int y, Carte& carte, std::vector< std::vector<int> > differentsChemins, int numcase);

#if 0
// Fonction pour choisir d'attaquer ou se deplacer (ou autre plus tard...). choix devient 0 pour le deplacement et 1 pour l'attaque
void choisir(int &choix, int &x, int &y);
#endif

#endif
