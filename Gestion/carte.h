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

#ifndef CARTE_H
#define CARTE_H


#include <Imagine/Graphics.h>
#include <stdlib.h>
#include "priorite.h"
#include <Imagine/Images.h>
#include <bits/stl_deque.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>

const float INF = 1.0f / 0.0f; // Infini en float
const int Taille = 30;
const int NbCase = 20;
const int LargDroite = 3 * NbCase;
const int LargGauche = 0;
const int Separation = 20; // Separation entre la carte et la mini map
const int width = NbCase * Taille + Separation + LargDroite;
const int height = NbCase * Taille;
const std::string descVille = "Ville"; // Descrption de la case ville. Variable a ne par retirer sans regarder la fonction boutonAction


class Heros;
class Unite;
class Ville;
class Carte;


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

    // Accesseur à l'image du type de la case
    Imagine::Color Image() const;

    // Accesseur au nombre de déplacement que coûte la case
    float NbDep() const;

    // Accesseur à la desctiprion de la case
    std::string Description() const;

    /**
     * Fonction qui crée une fenêtre pop up avec une question fermée et qui renvoie le résultat
     * @param question : question posée au joueur
     * @return true si le joueur a répondu "Oui"
     *         false sinon
     */
    bool popUp(std::string question) const;

    /**
     * Pour l'instant, n'est utile que pour ouvrir une ville quand on clique dessus
     * @param h : unité concernée par l'action (ex : le héros qui ouvre la ville)
     */
    virtual void action(Unite* h);

    virtual TypeCase *clone() const;

    /**
     * Appelle la fonction pop, crée des boutons où on peut choisir si l'on veut effectuer l'action de la case ou non
     * @return true si on clique sur "oui"
     *         false sinon
     */
    virtual bool boutonChoix();
};


class CaseVille : public TypeCase {
    Ville* ville;
public:
    CaseVille(std::string desc, Imagine::Color img, Ville* v);

    CaseVille();

    virtual void action(Unite* h);

    virtual CaseVille *clone() const;

    virtual bool boutonChoix();
};


class CaseCombat : public TypeCase {
public:
    CaseCombat(std::string desc, Imagine::Color img);

    CaseCombat();

    virtual CaseCombat *clone() const;

    virtual bool boutonChoix();
};


class CaseNormale : public TypeCase {
public:
    CaseNormale(float dep, std::string desc, Imagine::Color img);

    CaseNormale();

    virtual CaseNormale *clone() const;
};


// Classe definissant les cases de la carte
class Case {
    int x, y; // Position effective du coin haut gauche de la case
    int taille;
    Unite* pointeurUnite;
    bool brillance; // Variable indiquant si la case est en surbrillance
    bool utileChemin; // Variable indiquant si la case sert actuellement a montrer un chemin pour le Heros
    TypeCase *type;

public:
    // Constructeur de la classe Case
    Case(int x1, int y1, TypeCase* tc);

    // Constructeur vide de la classe Case
    Case();

    Case(const Case &tuile);

    /**
    * Place l'unité u sur la case en actualisant pointeurUnite
    * @param u
    */
    void placeUnite(Unite* u);

    /**
     * Retire l'unité qui était présente sur la case
     */
    void retireUnite();

    /**
     * @return true si il y a une unité présente sur la case
     *         false sinon
     */
    bool getOccupe() const;

    /**
     * @return le pointeur de l'unité sur la case
     */
    Unite* getPointeurUnite();

    /**
     * Get temporaire utilisé uniquement dans deplaceVersCase
     */
    int get(int i) const;

    /**
     * Place la case en surbrillance, ou enlève la surbrillance en fonction du booléen placé en argument
     * @param flag : si flag = true, on place en surbrillance
     */
    void brillanceOnOff(bool flag);

    void affiche() const;

    // Accesseur au nombre de déplacement que coûte la case
    float NbDep() const;

    // Accesseur a la brillance de la case
    bool Brillance() const;

    // Change le booleen utileChemin
    void setChemin();

    bool getChemin() const;

    /**
     *
     * @param x1 : abcisse de clic
     * @param y1 : ordonnée du clic
     * @param carte
     * @param numcase : numéro de la case du héros qui appelle cette focntion
     * @return l'entier qui correspond à la case brillante la plus proche du point (x1, y1)
     */
    int plusProcheVoisineBrillante(int x1, int y1, Carte &carte, int numcase) const;

    /**
     *
     * @param x1 : abcisse du clic donc on examine les cases voisines
     * @param y1 : ordonnée du clic
     * @return les numéros des cases voisines (attention il peut n'y en avoir que 3 ou 2) dans l'ordre du plus proche du
     *          point (x, y) au plus éloigné
     */
    std::vector<int> casesVoisines(int x1, int y1) const;

    /**
     * @param dep : déplacement nécessaire pour parcourir la case
     * @param carte
     * @param brillance : si true, on veut afficher les cases en surbrillance, et si false, on veut retirer la surbrillance
     * @param dep_restant : déplacements restants du héros
     * @param case_a_atteindre : case où on souhaite aller, dans le cas où on souhaite se déplacer
     * @param vecCaseBrillante : vecteur des cases brillantes
     * @return
     */
    std::vector<std::vector<int> > fastMarching(float dep, Carte &carte, bool brillance, float &dep_restant,
                                                int case_a_atteindre, std::vector< Imagine::Coords<2> > &vecCaseBrillante);

    // Renvoie l'image correspondant a la case (type a changer pour l'affichage)
    Imagine::Color getImage() const;

    // Renvoie le texte correspondant a la case
    std::string getDescription() const;

    // Permet de choisir si l'on veut effectuer l'action relative à la case
    bool boutonChoix() const;

    // Fais l'action sur la case s'il y en a une A CHANGER
    void action(Unite* u);

    ~Case();
};


class Carte {
    Case carte[NbCase * NbCase];
public:
    /**
     * Construit une carte aléatoire
     * @param inutilePourLInstant : là uniquement pour différencier les constructeurs (pour l'instant)
     */
    Carte(int inutilePourLInstant);

    // Construit une carte de base
    Carte(Ville* v);

    // affiche la carte
    void affiche() const;

    // Permer d'accéder à carte[i]
    Case &operator[](int i);

    // Permet d'accéder à carte[i] en const
    Case get(int i) const;
};


/**
 *
 * @param x : abcisse du pixel examiné
 * @param y : ordonnee du pixel examiné
 * @return le numéro de la case associée au pixel de coordonnées (x,y) et renvoie -1 si aucune case n'est associée
 */
int numeroCase(int x, int y);


void clic(int &x, int &y, Carte &carte, std::vector<std::vector<int> > differentsChemins, int numcase);


#endif // CARTE_H
