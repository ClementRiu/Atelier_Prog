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

    void ouvreVille(Unite *h);
    void ajoute(Mere *obj);
    Mere *getObjet(int i);
    int get_id() const;

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

    bool humain; //sera utilisé lors de l'implémentation d'une intelligence artificielle

public:
    Joueur(int num);

    Joueur(int id, std::vector<Unite *> unites, std::vector<Ville *> villes);

    Joueur(int id, std::vector<Unite *> unites); //uniquement pour tester

    int& getRessources();

    void ajouteUnite(std::vector<Unite *> unite);

    void ajouteVille(std::vector<Ville *> ville);

    int get_id() const;

    void tourGestion(Carte &carte, Bouton boutonFinTour, Bouton boutonSauvegarde, Bouton boutonAction,
                     Bouton boutonInventaire, bool &save);
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
