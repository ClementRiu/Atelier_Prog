#ifndef UNITE_H
#define UNITE_H



#include "../Combat/objet.h"
#include <Imagine/Graphics.h>
#include "carte.h"


const int TAILLE_ARMEE = 6;
const int NB_MAX_ATTAQUES = 10;


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
    void zone(Case *carte, bool b, int caseUnite);

    int getPuissance();
};


// Unite herite d'objet pour pouvoir etre achetee, vendue et inventorisee aussi
class Unite : public Objet{
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

    int numcase;
    float PDep;
    float PDepMax;

    Attaque competences[NB_MAX_ATTAQUES];

    int orientation; //voir manuel, possible de changer

    int typeDegats;

public:
    Unite();
    Unite(const Unite& unit);

    Unite(float dep, int num);

    Unite(float dep, float depMax, int num);

    void deplacement(Case *carte);

    // Fonction simple permettant d'afficher les cases disponibles pour le Heros, ou de les enlever
    void afficheCaseDisponibleOnOff(Case *carte, bool b, float &deplacement, int case_a_atteindre);

    void deplaceVersCase(Case &c2, Case &c1);

    // ATTENTION, cette fonction peut rencontrer des problemes lorsque l'on modifie la fonction boutonAction
    void tour(Case carte[NbCase * NbCase], std::vector<Unite*> unites, Bouton boutonFinTour);

    void attaque(Attaque attq, Case *carte, std::vector<Unite*> unites);

    void changeOrientation(int i);

    int getCase() const;

    void setCase(int num);

    float getDep() const;

    void setDep(float dep);

    float getDepMax() const;

    void setDepMax(float dep);

    void prendDommage(int att); //à implémenter avec formule adaptée

    void setAttaque(Attaque att, int i);

    bool estVivant();

    // Action que fait l'attaque, A COMPLETER (enlève des points de vie, pousse des ennemis pour des sous classes d'attaques...)
    void action(Attaque a, Unite *u);

    // Cree les boutons pour que l'unite puisse effectuer son action
    // La fonction est a modifier niveau affichage et a organiser
    std::vector<Bouton> boutonAction(Case *carte);

    // Fonction vide ici
    virtual void ramasse(Objet *obj);

    // Fonction vide ici
    virtual void ouvreInventaire();

    // Fonction vide ici
    virtual void equipe(int i, bool droite = true);

    // Fonction vide ici
    virtual std::string getNomCasque();

    // Destructeur de la classe Unite (sert a creer celui de la classe Heros)
    virtual ~Unite();
};


class Sbire : public Unite {
    int nombre;

public:
    Sbire();

    Sbire(const Sbire & s);
};


class Armee {
    Sbire sbireArmee[TAILLE_ARMEE];

public :
    Armee();

    Armee(std::vector<Sbire> sbires);

    Armee(const Armee &a);
};


class Heros : public Unite {
    Armee ArmeeHeros;

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
    Heros(float dep, int num);

    Heros(const Heros& h);

    Heros(const Unite& u);

    //equipe appelle la méthode adéquate en fonction du type d'équipement
    virtual void equipe(int i, bool droite = true);

    Casque equipeCasque(Casque casque);

    Arme equipeArmeDroite(Arme arme);

    Arme equipeArmeGauche(Arme arme);

    Torse equipeTorse(Torse torse);

    Gants equipeGants(Gants gants);

    Jambes equipeJambes(Jambes jambes);

    Bottes equipeBottes(Bottes bottes);

    Anneau equipeAnneauDroite(Anneau anneau);

    Anneau equipeAnneauGauche(Anneau anneau);

    //Fonction a modifier
    virtual void ouvreInventaire();

    // Fonction pour ajouter un objet a l'inventaire
    virtual void ramasse(Objet *obj);

    // Fonction renvoyant le nom du casque equipe. Utile pour un test
    virtual std::string getNomCasque();

    virtual ~Heros();
};

#endif




