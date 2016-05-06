#ifndef CARTE_H
#define CARTE_H


#include <Imagine/Graphics.h>
#include <stdlib.h>
#include "priorite.h"
#include <bits/stl_deque.h>
#include <iostream>
#include <fstream>


const float INF = 1.0f / 0.0f; // Infini en float
const int Taille = 20;
const int NbCase = 30;
const int LargDroite = 3 * NbCase;
const int LargGauche = 0;
const int Separation = 20; // Separation entre la carte et la mini map
const int width = NbCase * Taille + Separation + LargDroite;
const int height = NbCase * Taille;
const int ZoneBoutonFinTour[4] = {NbCase * Taille + Separation, Taille * (NbCase - 5),
                                  NbCase * Taille + Separation + LargDroite, NbCase * Taille};
const int ZoneBoutonSauvegarde[4] = {NbCase * Taille + Separation, Taille * (NbCase - 5) - LargDroite - 10,
                                     NbCase * Taille + Separation + LargDroite, Taille * (NbCase - 5)};
const std::string descVille = "La ville, le doux foyer"; // Descrption de la case ville. Variable a ne par retirer sans regarder la fonction boutonAction



class Unite;

// Classe definissant les différents types de cases que l'on peut trouver
class TypeCase {
    float PDep; // Nombre de deplacements nécessaires pour aller sur cette case
    std::string description;
    Imagine::Color image; // Sera remplace par une image ulterieurement
public:
    // Constructeur de la classe TypeCase
    TypeCase(float dep, std::string desc, Imagine::Color img);

    // Constructeur vide de la classe TypeCase
    TypeCase();

    // Accesseur a l'image du type de la case
    Imagine::Color Image();

    // Accesseur au nombre de déplacement que coûte la case
    float NbDep() const;

    // Accesseur à la desctiprion de la case
    std::string Description();
};


// Classe definissant les cases de la carte
class Case {
    int x, y; // Position effective du coin haut gauche de la case
    int taille;
    bool occupe; // Variable indiquant si le heros est sur la case
    bool brillance; // Variable indiquant si la case est en surbrillance
    TypeCase type;

public:
    // Constructeur de la classe Case
    Case(int x1, int y1, TypeCase tc);

    // Constructeur vide de la classe Case
    Case();

    // Place le heros sur cette case s'il n'y etait pas et l'enleve s'il y etait
    void flagHeros();

    bool getOccupe() const;

    //get temporaire à se débarasser !!
    int get(int i);

    // Place la case en surbrillance, ou enleve la surbrillance selon le booleen et affiche la case
    void brillanceOnOff(bool flag);

    // Affiche la case
    void affiche(); // Cette methode devrait être const mais je n'arrive pas a le faire !!!!!

    // Accesseur au nombre de déplacement que coûte la case
    float NbDep() const;

    // Accesseur a la brillance de la case
    bool Brillance() const;

    // Algorithme de FastMarching pour mettre en surbrillance les cases autorisées au Heros
    void fastMarching(float dep, Case *carte, bool brillance, float &dep_restant, int case_a_atteindre);

    // Renvoie l'image correspondant a la case (type a changer pour l'affichage)
    Imagine::Color getImage();

    // Renvoie le texte correspondant a la case
    std::string getDescription();
};


class Bouton{
    int zoneDeDelimitation[4]; // Tableau de la forme [xmin, ymin, xmax, ymax]
    Imagine::Color image; // A remplacer par une image #Clement
    std::string nomBouton;
    int taillePolice;
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


// Renvoie le numero de la case associee au pixel (x, y) et renvoie -1 si aucune case n'est associee
int numeroCase(int x, int y);

// Fonction renvoyant en référence dans x et y la position d'un clic et affichant les cases survolees
void clic(int &x, int &y, Case *carte);

// Fonction renvoyant en référence dans x et y la position d'un clic
void clicSimple(int &x, int &y);

//Termine la journée (=tour dans Gestion)
void finJournee(std::vector<Unite*> unites);

//Termine le tour en combat
void finTourCombat(std::vector<Unite*> unites);

// Fonction pour choisir d'attaquer ou se deplacer (ou autre plus tard...). choix devient 0 pour le deplacement et 1 pour l'attaque
void choisir(int &choix, int &x, int &y);

// Renvoie les coordonnees de la case survolee
void survole(int &x, int &y);

// Affiche l'endroit survole par la souris
void afficheSurvole(int x, int y, Case *carte);

void sauvegarde(std::vector<Unite*> unites);
void charge(std::vector<Unite*> unites, Case *carte);

#endif // CARTE_H
