#ifndef JOUEURS_H
#define JOUEURS_H

#include "unite.h"
#include <iostream>

const int NB_HEROS_MAX=10;
const int NB_RESSOURCE=3;
const int population_max=75;
class Ville{};

class Joueur{
    int id;
    //bool humain;
    int ressources[NB_RESSOURCE];
    int score;
    int couleur;
    int population;
    int nb_heros_max_joueur;
    std::vector<Unite> herosJoueur; //ATTENTION herosJoueurs EST UN VECTEUR d'UNITES !!
    std::vector<Ville> villesJoueur;

public:
    Joueur(int num);
    //Joueur(std::vector<Unite*> unites, std::vector<Ville*> villes);
    Joueur(std::vector<Unite*> unites); //uniquement pour tester


    //gros tas de get
    int get_id();
    //bool get_humain();
    int get_ressources(int i);
    int get_score();
    int get_couleur();
    int get_population();
    int get_nb_heros_max_joueur();
    std::vector<Unite> get_herosJoueur(); //ATTENTION herosJoueurs EST UN VECTEUR d'UNITES !!
    std::vector<Ville> get_villesJoueur();

    //modifications des valeurs
    void modifie_ressources(int res, int valeur);
    void add_score(int points);
    void update_pop(int valeur);
    void tue_heros(Heros mort);
    void recrute_heros(Heros recrue);
    void conquiert_ville(Ville conquete);
    void perd_ville(Ville perte);


    void tourGestion(Carte &carte, std::vector<Unite *> unites, Bouton boutonFinTour, Bouton boutonSauvegarde, Bouton boutonAction, Bouton boutonInventaire, bool &save);
};



#endif
