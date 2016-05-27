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

#ifndef JOUEURS_H
#define JOUEURS_H

#include "unite.h"
#include <stdlib.h>
#include <iostream>
#include <Imagine/Graphics.h>
#include "../Gestion/unite.h"

const int NB_HEROS_MAX = 10;
const int NB_RESSOURCES = 1;

const int NB_BATIMENTS = 10;
const int NB_AMELIORATIONS = 3;
const int nb_type_unite = 10;

class Ville {
    int id;
    int batiments[NB_BATIMENTS]; //Chaque élément du tableau représente un batiment, si batiment[i]=0 il n'est pas construit,
    std::vector<Sbire *> garnison;
    bool heros_present;
    int recrutables[nb_type_unite]; //recrutable[i] contient le nombre d'unite de type i que l'on peut recruter
    bool amelioration[NB_BATIMENTS]; //indiqe si le bâtiment est améliorable
    Inventaire achetable;               //liste d'objet disponible a l'achat
    int camp;                       //le joueur à qui appartient la ville

public:
    Ville();

    Ville(int num);

    Ville(int faction, int num);

    ~Ville();

    /**
     * Ouvre l'inventaire de la ville
     * @param h : héros qui ouvre la ville, utilisé pour savoir à qui ajouter les objets achetés par exemple
     */
    void ouvreVille(Unite *h);

    /**
     * Ajoute un objet dans l'inventaire de la ville
     * @param obj
     */
    void ajoute(Mere *obj);

    /**
     * @param i
     * @return le pointeur pointant vers l'objet à la position i dans l'inventaire de la ville
     */
    Mere *getPointeurMere(int i);

    int get_id() const;

    /**
     * @return l'inventaire du joueur en référence
     */
    Inventaire &getInventaire();


    //Fonctions inutilisées ou non implémentées pour l'instant
#if 0
    void update_recrutable();    //met a jour la liste des soldats recrutable
    void update_ameliorable();   //met a jour la liste des batiments ameliorable
    void update_achetable();     //met a jour la liste des objet achetable

    void ameliore(int i); //augment le niveau du batiment i
    void recrute(int i);    // recrute un soldat
    void achat(int i);          //achete un objet
    void set_heros_present(bool b);
    int get_lv_batiment(int i);   //renvoie le niveau du batiment i
    Armee get_garnison();
    int get_nb_recrue(int type);

    int get_camp();
    bool est_ameliorable(int i); //indique si le batiment i est ameliorable


    bool get_heros_present();

    void retire(int i);
#endif
};

class Joueur {
    int id;
    int ressources[NB_RESSOURCES]; //tableau de ressources du joueur, comme de l'or, du bois...
    float revenus[NB_RESSOURCES]; //tableau de revenus par tour des ressources
    int score; //non utilisé pour l'instant, avoir un score reste une tradition vidéoludique
    int nb_heros_max_joueur;
    std::vector<Unite *> herosJoueur;
    std::vector<Ville> villesJoueur;

    bool humain; //sera utilisé lors de l'ajout d'une intelligence artificielle controllant un ou plusieurs joueurs

public:
    Joueur(int num);

    Joueur(int id, std::vector<Unite *> unites, std::vector<Ville *> villes);

    Joueur(int id, std::vector<Unite *> unites); //uniquement pour tester

    // Renvoie les ressources du joueur en référence
    int &getRessources();

    // Ajoute les unités passées en argument aux unités du joueur
    // utilisé pour le recrutement dans les villes et au début du jeu
    int get_id() const;

    /**
     * Permet de déterminer si la partie est finie ou non en examinant le vecteur de héros du joueur
     * @return vrai herosJoueur est vide
     */
    bool aPerdu();

    /** Ajoute les unités passées en argument aux unités du joueur
     * Utilisé au début du jeu, et sera utilisé pour le recrutement dans les villes
     * @param unite : vecteur d'unites à ajouter aux unités du joueur
     */
    void ajouteUnite(std::vector<Unite *> unite);

    /** Ajoute les villes passées en arguement aux villes du joueur
     * Utilisé au début du jeu, et sera utilisée lorsque la conquète des villes sera possible
     * @param ville
     */
    void ajouteVille(std::vector<Ville *> ville);

    /**
     * Fonction gérant le tour d'un joueur : on sélectionne une unité, puis on peut a déplacer, déclancher un combat
     * en cliquant sur une unité ennemie adjacente...
     * La fonction se termine lorsqu'on clique sur le bouton FinDeTour
     * @param carte : carte du monde
     * @param boutonFinTour : bouton qui permet de terminer la fonction
     * @param boutonSauvegarde : bouton permettant de sauvegarder
     * @param boutonAction  : bouton permettant de lancer une action (inutile pour l'instant)
     * @param boutonInventaire : bouton permettant d'ouvrir l'inventaire
     * @param quit : modifié en true si le joueur clique sur boutonSauvegarde
     * @param nbTour : numéro du tour actuel (pour l'affichage dans le menu de droite)
     */
    void tourGestion(Carte &carte, Bouton boutonFinTour, Bouton boutonSauvegarde, Bouton boutonAction,
                     Bouton boutonInventaire, bool &save, int nbTour);

    // Fini le tour de Gestion du joueur en remettant les bons nombres de déplacement dans les unités
    /**
     * Restaure les points de déplacement des unités au maximum et en ajoutant aux réserves de ressources du joueur ses
     * revenus (pour l'instant uniquement l'or)
     */
    void finTourGestion();


//Fonctions inutilisées ou non implémentées pour l'instant
#if 0
    int get_ressources(int i);
    int get_score();
    int get_nb_heros_max_joueur();
    std::vector<Unite *> get_herosJoueur();
    std::vector<Ville> get_villesJoueur();
    //modifications des valeurs
    void modifie_ressources(int res, int valeur);
    void add_score(int points);
    void update_pop(int valeur);
    void tue_heros(Unite *mort);
    void recrute_heros(Unite *recrue);
    void conquiert_ville(Ville conquete);
    void perd_ville(Ville perte);
#endif
};


#endif
