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

//plusieurs portées possibles pour définir les portées de chaque attaque
const Imagine::Coords<2> portee10(1, 0);
const Imagine::Coords<2> portee_10(-1, 0);
const Imagine::Coords<2> portee20(2, 0);
const Imagine::Coords<2> portee_20(-2, 0);
const Imagine::Coords<2> portee01(0, 1);
const Imagine::Coords<2> portee02(0, 2);
const Imagine::Coords<2> portee0_2(0, -2);
const Imagine::Coords<2> portee0_1(0, -1);
const Imagine::Coords<2> portee30(3, 0);
const Imagine::Coords<2> portee_30(-3, 0);


class Attaque {
    std::vector<Imagine::Coords<2> > zoneInfluence;
    int puissance;
public:
    // Attaque par défaut
    Attaque();

    Attaque(const Attaque &att);

    Attaque(std::vector<Imagine::Coords<2> > zone, int power);

    // Affiche la zone d'influence de l'attaque
    void zone(Carte &carte, bool b, int caseUnite);

    int getPuissance() const;
};


// Cette classe n'est normalement jamais directement instanciée, elle est utilisée pour créer des fonctions virtuelles,
// pour la plu

/** Unite herite de Mere pour pouvoir acheter, vendre des unités et en créer des inventaires
 * Cette classe n'est normalement jamais directement instanciée, elle est utilisée pour créer des fonctions virtuelles,
 * pour la plupart vides dans la classe Unite.
 * La documentation sera uniquement présente dans Unite, pour ne pas polluer Heros et Sbire.
 */
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
    float initiativeTemporaire; //utilisée en combat pour gérer la file de priorité d'unités

    int IDjoueur;
    Joueur *joueur;

    int numcase;
    float PDep;
    float PDepMax;

    Attaque competences;

    int typeDegats; //Non utilisé pour l'instant : nous comptions mettre un système de types de de dégats, comme "tranchant", "contendant" etc.

public:
    Unite();

    Unite(const Unite &unit);

    Unite(int IDjoueur, float PVm, float dep, float depMax, int num, float init);

    Unite(float dep, int num);

    int getCase() const;

    float getPV() const; //pour tester uniquement

    virtual int getNombre() const;

    int getID() const;

    float getInit() const;

    void setCase(int &num, const Carte &carte);

    float getDep() const;

    void setDep(float dep);

    float getDepMax() const;

    virtual std::vector<Sbire *> getArmee();

    virtual void ajouteSbire(Sbire *s);

    /**
     * Actuellement, remplace l'attaque (unique) de l'unité par att
     * Destinée à ajouter une compétence à la liste des compétences de l'unité
     * @param att : nouvelle compétence qu'aura l'unité
     */
    void setAttaque(const Attaque &att);


    /**
    * Compare les initiatives temporaires des deux unités, pour pouvoir utiliser les files de priorité
    * @param u : unité avec laquelle on compare l'initiative temporaire de notre unité
    * @return true si initiative temporaire de notre unité < initiative temporaire de u
    *         false sinon
    */
    bool operator<(Unite u) const;


    /**
    *
    * @param carte : carte, générale ou carte combat
    * @param x1 : 1e coordonnee du clic demandé
    * @param y1 : 2e coordonnee du clic demandé
    * @param gestion : si true, alors on n'affiche pas le chemin qui sera emprunté,
     *                 si false, alors on affiche le chemin qui sera emprunté (points rouges)
    * @return
    */
    bool deplacement(Carte &carte, int x1, int y1, bool gestion);


    /**
     * Tue l'unité en mettant ses points de vie à zero.
     */
    virtual void tueUnite();


    /**
     * Fonction permettant d'afficher les cases disponibles pour le Heros, ou de les retirer
     * Elle appelle FastMarching
     * Appelée dans déplacement, elle actualise les points de déplacement restant à l'unité après déplacement.
     * @param carte :  carte générale du monde ;
     * @param b : bool permettant de choisir si on affiche ou enlève les cases disponibles ;
     * @param deplacement : déplacement restant au héros ;
     * @param case_a_atteindre : permet d'actualiser les points de déplacement restants à l'unité après le déplacement ;
     * @return differentsChemins : vecteur de vecteurs d'int stockant les chemins possibles vers une case (utilisé en combat)
     */
    std::vector<std::vector<int> > afficheCaseDisponibleOnOff(Carte &carte, bool b, float &deplacement,
                                                              int case_a_atteindre);


    /**
     * Place l'unité présente en caseDepart sur caseDestination
     */
    void deplaceVersCase(Case &caseDestination, Case &caseDepart);

    /**
     * Gère le tour d'une unité lors d'un combat
     * ATTENTION, cette fonction peut rencontrer des problemes lorsque l'on modifie la fonction boutonAction
     * @param carte : carte de combat (différente de la carte du monde)
     * @param boutonFinTour : bouton qui gère la fin de tour, on vérifie pendant la fonction si il a été activé
     * @param boutonAction : bouton qui active la phase d'action
     */
    void tourCombat(Carte &carte, Bouton boutonFinTour, Bouton boutonAction);

    /**
     * Lance la phase d'attaque, et si le joueur clique autre part que sur une unité à portée, annule la phase.
     * @param attq : attaque sélectionnée
     * @param carte : carte du combat
     * @return true si l'attaque a bien eu lieu
     *         false si le joueur a cliqué autre part que sur une unité à portée
     */
    bool attaque(const Attaque &attq, Carte &carte);

    /**
     * Gère la file de priorité en enlevant i à l'initiative temporaire
     * Destiné à être modifié car ce système est très sommaire
     * @param i : on va enlever i à l'initiative temporaire
     */
    void changeInitiativeTemporaire(int i);

    /**
     * On enlève valeurDegats aux PV de l'unité.
     * Cette fonction est destinée à prendre en compte la défense de l'unité et le type d'attaque pour calculer les dégats
     * @param valeurDegats
     */
    virtual void prendDommage(int valeurDegats);

    /**
     * Fonction permettant d'acheter le i-eme objet de l'inventaire de la ville
     * @param ville : dont on explore l'inventaire
     * @param i : numéro de l'objet acheté dans la ville
     * @param b : utilisé pour que la fonction prenne les mêmes arguments que la fonction Equipe
     * @param ressources : ressources du héros, pour l'instant l'or
     */
    virtual void achete(Ville *ville, int i, bool b, int &ressources);

    /**
     * Ouvre l'inventaire de la ville passée en argument
     * @param v : ville dont on ouvre l'inventaire
     */
    virtual void ouvreVille(Ville *v);

    /**
     * Fonction utilisée pour l'affichage des PV d'une unité, et de son nombre s'il s'agit d'un sbire dans le menu
     * de droite
     */
    virtual void affichePVNombre();

    //Fonction qui renvoie false quand appelé sur une Unité ou un Sbire, et true sur un Heros
    /**
     * Fonction utilisée lorsqu'on tue un héros en combat : pour chaque unité tuée, on regarde s'il s'agissait d'un
     * héros. Si c'est le cas, on tue tous les sbires du héros.
     * @return true si l'unité est un héros,
     *         false si l'unité est un sbire (a priori il n'y aura jamais de véritable "Unité")
     */
    virtual bool estHeros() const;

    /**
    * @return true si l'unité a des PV>=0 (et nombre >=1 si l'unité est un sbire)
    *         false sinon
    */
    virtual bool estVivant() const;


    /**
     * Pour l'instant, inflige les dégats de l'attaque att.
     * Destinée à pouvoir gérer des effets plus intéressants comme pouvoir repousser des ennemis, les empoisonner...
     *
     * Très sommaire pour l'instant !
     * @param att : compétence du héros
     * @param u : unité visée par l'action
     */
    void action(const Attaque &att, Unite *u);

    /**
     * Attaque de base au corps à corps que toutes les unités possèdent, bien moins puissante que les capacités
     * Pour l'instant, dépend uniquement de la force de l'unité
     *
     * On la déclanche en cliquant sur une unité présente au corps à corps de l'unité en cours
     * @param u : unité visée par l'attaque de base
     */
    void attaqueDeBase(Unite *u);


    /**
    * Fonction appelée dans tourGestion, lorsqu'une unité sélectionnée clique sur une unité (u) du camp opposé
    * @param u : unité attaquée qui sera désignée comme "ennemie" durant le combat
    * @return ID : l'ID du joueur perdant, qui sera utilisé pour réafficher les bonnes unités en retour dans gestion
    */
    virtual int declencheCombat(Unite *u);


    /**
     * Remet le nombre de déplacements restants au maximum et modifie l'initiative
     * @param ini : initiative passée en argument de changeInitiativeTemporaire
     */
    virtual void finTourCombat(int ini);

    /**
     * Appelle la fonction retire de l'inventaire du héros
     * @param i : numéro de l'objet à retirer
     */
    virtual void retire(int i);

    /**
     * Appelle la fonction ajoute de l'inventaire du héros sur obj
     * @param obj : objet qui sera rajouté dans l'inventaire
     */
    virtual void ramasse(Mere *obj);


    virtual void ouvreInventaire(int &ressources);

    /**
     * Fonction destinée à être passée en pointeur de fonction, il y a donc une ville et des ressources en paramètre
     * même si elles ne servent pas directement
     *
     * Appelle la fonction equipe de l'inventaire du héros
     * @param ville : utilisé pour que la fonction prenne les mêmes arguments que la fonction achete
     * @param i : on équipe l'objet numéro i dans l'inventaire
     * @param droite : non implémenté, destiné à choisir si on équipe à droite ou à gauche (une épée par exemple)
     * @param ressources : utilisé pour que la fonction prenne les mêmes arguments que la fonction achete
     */
    virtual void equipe(Ville *ville, int i, bool droite, int &ressources);

    virtual std::string getNomCasque();

    virtual ~Unite();
};


class Sbire : public Unite {
    int nombre;

public:
    Sbire();

    Sbire(int IDj, float PVm, float dep, float depMax, int num, float init, int nb);

    Sbire(const Sbire &s);

    virtual bool estVivant() const;

    virtual void prendDommage(int valeurDegats);

    virtual void tueUnite();

    virtual int getNombre() const;

    virtual void affichePVNombre();

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
    Heros(int ID, float PVm, float dep, float depMax, int num, float init, Joueur *jou);

    Heros(const Heros &h);

    Heros(const Unite &u);

    virtual void ajouteSbire(Sbire *s);

    //equipe appelle la méthode adéquate en fonction du type d'équipement

    virtual void equipe(Ville *ville, int i, bool droite, int &ressources);

    virtual std::vector<Sbire *> getArmee();

    // Lance l'unité dans un combat avec une autre unité
    virtual int declencheCombat(Unite *u);

    virtual bool estHeros() const;

    // Retire l'objet numéro i de l'inventaire
    virtual void retire(int i);

    // Fontion pour ouvrir la ville
    virtual void ouvreVille(Ville *v);

    //Fonction a modifier
    virtual void ouvreInventaire(int &ressources);

    // Fonction pour ajouter un objet a l'inventaire
    virtual void ramasse(Mere *obj);

    virtual void affichePVNombre();

    // Achète le i-ème objet dans la ville
    virtual void achete(Ville *ville, int i, bool b, int &ressources);

    // Equipe l'objet passé en argument à chaque fois et renvoie l'objet déséquipé
    Casque equipeCasque(const Casque &casque);

    Arme equipeArmeDroite(const Arme &arme);

    Arme equipeArmeGauche(const Arme &arme);

    Torse equipeTorse(const Torse &torse);

    Gants equipeGants(const Gants &gants);

    Jambes equipeJambes(const Jambes &jambes);

    Bottes equipeBottes(const Bottes &bottes);

    Anneau equipeAnneauDroite(const Anneau &anneau);

    Anneau equipeAnneauGauche(const Anneau &anneau);

    // Fonction renvoyant le nom du casque equipe. Utile pour un test
    virtual std::string getNomCasque();

    virtual ~Heros();
};

#endif




