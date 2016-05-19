#ifndef UNITE_H
#define UNITE_H


#include "../Combat/objet.h"
#include <Imagine/Graphics.h>
#include "carte.h"
#include "outils.h"

const int TAILLE_ARMEE = 6;
const int NB_MAX_ATTAQUES = 10;


class Ville;
class Sbire;
class Joueur;


const Imagine::Coords<2> portee10(1, 0);
const Imagine::Coords<2> portee_10(-1, 0);
const Imagine::Coords<2> portee20(2, 0);
const Imagine::Coords<2> portee_20(-2, 0);
const Imagine::Coords<2> portee01(0, 1);
const Imagine::Coords<2> portee02(0, 2);
const Imagine::Coords<2> portee0_2(0, -2);
const Imagine::Coords<2> portee0_1(0, -1);


/*
  *******************************************ATTENTION AUX CONTRUCTEURS PAR COPIE****************************
  Ils ont été créés principalement pour des tests sur les "deque" (voir documentation C++)
  Ils risquent de ne plus être parfaitement fonctionnels lors de la fin du projet, à vérifier donc lors du travail
  de Nathanael
 *
 ***********************************************************************************************************
 */


class Attaque {
    std::vector<Imagine::Coords<2> > zoneInfluence;
    int puissance;
public:
    Attaque();

    Attaque(const Attaque &att);

    Attaque(std::vector<Imagine::Coords<2> > zone, int power);

    // Affiche la zone d'influence de l'attaque
    void zone(Carte &carte, bool b, int caseUnite);

    int getPuissance();
};


// Unite herite d'objet pour pouvoir etre achetee, vendue et inventorisee aussi
class Unite : public Mere {
protected:
    //caractéristiques de l'unité
    float PV;
    float PVMax;
    float mana;
    float manaMax;
    float force;
    float defensePhy[NB_DEG_PHY];
    float defenseMag[NB_RES];
    float dexterite;
    float initiative;
    float initiativeTemporaire;
    bool tour;

    int IDjoueur;
    Joueur* joueur;

    int numcase;
    float PDep;
    float PDepMax;

    Attaque competences[NB_MAX_ATTAQUES];

    int orientation; //voir manuel, possible de changer

    int typeDegats; //Non utilisé pour l'instant : nous comptions mettre un système de types de de dégats, comme "tranchant", "contendant" etc.

public:
    Unite();

    Unite(const Unite &unit);

    Unite(int IDjoueur, float dep, float depMax, int num, float init);

    Unite(float dep, int num);

    bool operator<(Unite u) const;


    void deplacement(Carte &carte, int x1, int y1, bool gestion);

    // Permet à l'unité de choisir son action
    // A IMPLEMENTER
    void choixAction();

    virtual std::vector<Sbire *> getArmee();
    virtual void ajouteSbire(Sbire* s);

    virtual void tueUnite();

    // Fonction simple permettant d'afficher les cases disponibles pour le Heros, ou de les enlever
    std::vector<std::vector<int> > afficheCaseDisponibleOnOff(Carte &carte, bool b, float &deplacement,
                                                              int case_a_atteindre);

    void deplaceVersCase(Case &c2, Case &c1);

    // ATTENTION, cette fonction peut rencontrer des problemes lorsque l'on modifie la fonction boutonAction
    void tourCombat(Carte &carte, Bouton boutonFinTour, Bouton boutonAction);

    void attaque(Attaque attq, Carte &carte);

    void changeOrientation(int i);

    // FONCTION A MODIFIER ABSOLUMENT
    void changeInitiativeTemporaire(int i);

    int getCase() const;

    float getPV() const; //pour tester uniquement

    int getID() const;

    float getInit() const;

    void setCase(int num);

    float getDep() const;

    void setDep(float dep);

    float getDepMax() const;

    virtual void prendDommage(int att); //à implémenter avec formule adaptée

    void setAttaque(Attaque att, int i);

    // Achète le i-ème objet dans la ville
    virtual void achete(Ville* ville, int i, bool b, int &ressources);

    virtual void ouvreVille(Ville* v);

    //Fonction qui renvoie false quand appelé sur une Unité ou un Sbire, et true sur un Heros
    virtual bool estHeros();

    //renvoie vrai si l'unité a des PV supérieurs à 0
    virtual bool estVivant();

    // Action que fait l'attaque, A COMPLETER (enlève des points de vie, pousse des ennemis pour des sous classes d'attaques...)
    void action(Attaque a, Unite *u);

    // Attaque de base au corps à corps que toutes les unites posèdent A CHANGER
    void attaqueDeBase(Unite* u);

    // Cree les boutons pour que l'unite puisse effectuer son action
    // La fonction est a modifier niveau affichage et a organiser
//    std::vector<Bouton> boutonAction(Carte& carte);


    virtual void declencheCombat(Unite* u);

    //Termine le tour en combat
    virtual void finTourCombat(int ini);

    // Retire l'objet numéro i de l'inventaire
    virtual void retire(int i);

    // Fonction vide ici
    virtual void ramasse(Mere *obj);

    // Fonction vide ici
    virtual void ouvreInventaire();

    // Fonction vide ici
    virtual void equipe(Ville* ville, int i, bool droite, int& ressources);

    // Fonction vide ici
    virtual std::string getNomCasque();

    // Destructeur de la classe Unite (sert a creer celui de la classe Heros)
    virtual ~Unite();

    virtual void plop();
};


class Sbire : public Unite {
    int nombre;

public:
    Sbire();
    Sbire(int IDj, float dep, float depMax, int num, float init, int nb);
    Sbire(const Sbire &s);

    virtual bool estVivant();
    virtual void prendDommage(int valeurDegats);
    virtual void tueUnite();


    virtual ~Sbire();
};


class Heros : public Unite {
    std::vector<Sbire *> armeeHeros;

    int niveau;
    int exp;

    Inventaire inventaire;
    Casque equipementCasque;
    Arme equipementArmeDroite;
    Arme equipementArmeGauche;
    Torse equipementTorse;
    Gants equipementGants;
    Jambes equipementJambes;
    Bottes equipementBottes;
    Anneau equipementAnneauDroite;
    Anneau equipementAnneauGauche;

public:
    Heros(int ID, float dep, float depMax, int num, float init);
    Heros(const Heros &h);
    Heros(const Unite &u);

    virtual void ajouteSbire(Sbire* s);

    //equipe appelle la méthode adéquate en fonction du type d'équipement
    virtual void equipe(Ville* ville, int i, bool droite, int& ressources);

    virtual std::vector<Sbire *> getArmee();

    // Lance l'unité dans un combat avec une autre unité
    virtual void declencheCombat(Unite* u);

    virtual bool estHeros();

    // Retire l'objet numéro i de l'inventaire
    virtual void retire(int i);

    // Fontion pour ouvrir la ville
    virtual void ouvreVille(Ville* v);

    //Fonction a modifier
    virtual void ouvreInventaire();

    // Fonction pour ajouter un objet a l'inventaire
    virtual void ramasse(Mere *obj);


    virtual void plop();

    // Achète le i-ème objet dans la ville
    virtual void achete(Ville* ville, int i, bool b, int &ressources);

    Casque equipeCasque(Casque casque);
    Arme equipeArmeDroite(Arme arme);
    Arme equipeArmeGauche(Arme arme);
    Torse equipeTorse(Torse torse);
    Gants equipeGants(Gants gants);
    Jambes equipeJambes(Jambes jambes);
    Bottes equipeBottes(Bottes bottes);
    Anneau equipeAnneauDroite(Anneau anneau);
    Anneau equipeAnneauGauche(Anneau anneau);

    // Fonction renvoyant le nom du casque equipe. Utile pour un test
    virtual std::string getNomCasque();

    virtual ~Heros();
};

#endif




