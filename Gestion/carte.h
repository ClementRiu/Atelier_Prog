#ifndef CARTE_H
#define CARTE_H


#include <Imagine/Graphics.h>
#include <stdlib.h>
#include "priorite.h"


const float INF = 1.0f / 0.0f; // Infini en float
const int Taille = 20;
const int NbCase = 30;
const int LargDroite = 3 * NbCase;
const int LargGauche = 0;
const int Separation = 20; // Separation entre la carte et la mini map


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

    // Deplace et actualise la position du Heros sur la carte
    void deplaceHeros(Unite &h, Case &c);

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


int numeroCase(int x, int y);

// Fonction renvoyant en référence dans x et y la position d'un clic
void clic(int &x, int &y, Case *carte);

// Fonction simple permettant de deplacer le Heros
void deplaceHeros(Case *carte, Unite &h, int x1, int y1);

// Fonction simple permettant au joueur de deplacer n'impote quel Heros
void deplacement(Case *carte, Unite unit);

// Interroge si le joueur a cliqué sur la zone de fin de tour
bool finTourDemande(int x, int y);

//Termine la journée (=tour dans Gestion)
void finJournee(std::vector<Unite> &unites);

//Termine le tour en combat
void finTourCombat(std::vector<Unite> &unites);

// Fonction pour choisir d'attaquer ou se deplacer (ou autre plus tard...). Renvoie 0 pour le deplacement et 1 pour l'attaque
void choisir(int &choix);

// Renvoie les coordonnees de la case survolee
void survole(int &x, int &y);

// Affiche l'endroit survole par la souris
void afficheSurvole(int x, int y, Case *carte);

#endif // CARTE_H
