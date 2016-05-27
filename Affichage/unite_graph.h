#include "constante.h"
#include "bouton_graph.h"
#include "ville_graph.h"
#include "map_graph.h"

class Attaque {
    std::vector<Imagine::Coords<2> > zoneInfluence;
    int puissance;
public:
    Attaque();

    Attaque(const Attaque &att);

    Attaque(std::vector<Imagine::Coords<2> > zone, int power);

    // Affiche la zone d'influence de l'attaque
    void zone(CarteduMonde &carte, bool b, int caseUnite);

    int getPuissance();
};

class Mere {
    int prix; // A CHANGER
    std::string nom;
public:

    Mere();

    Mere(std::string nom_);

    Mere(const Mere &m);

    std::string getNom();

    // Fonction creeant un bouton vide si les 2 objets ne sont pas du meme type et
    // Creant un bouton au nom de l'objet sur lequel la methode est effectuee sinon
    Bouton creeBouton(Mere *obj, int xmin, int &ymin, int xmax, int &ymax);

    // Fonction vide utile uniquement pour les equipements
    virtual void equiper(Heros *h, bool droite);

    virtual Mere *clone() const;
};


class Objet : public Mere {
    std::string nom;
    std::string type;
public:
    Objet();

    Objet(std::string nom_);

    bool operator==(const Objet &B) const;

    virtual Objet *clone() const;
};


// Fonction a modifier
// faire vien plutot de Unite
class Inventaire {
    std::vector<Mere *> contenu;
public:
    int taille();

    Inventaire();

    Inventaire(const Inventaire &inventaire);

    // Ajoute un objet dans l'inventaire
    void ajoute(Mere *obj);

    // renvoie le pointeur sur l'objet numero i
    Mere *get(int i);

    // Cette fonction ouvre un inventaire et sert a effectuer differentes actions dedans.
    // Voir unite.h pour avoir un exemple
    void ouvreInventaire(std::vector<Bouton> boutonsCategories, Inventaire classeObjets, Ville* ville,
                         Unite *unite, void (Unite::*faire)(Ville*, int, bool));

    // Retire le i-ème objet de l'nventaire
    void retire(int i);

    ~Inventaire();
};


const Objet nul("NUL");


class Equipement : public Objet {
    int PV;
    int mana;
    int force;
    int defense;
    int dexterite;
    int initiative;

    float PDep;

public:
    Equipement();

    Equipement(const Equipement &eq);

    Equipement(std::string nom_);
};


class Casque : public Equipement {
public:
    Casque();

    Casque(std::string nom_);

    virtual void equiper(Heros *h, bool droite);

    virtual Casque *clone() const;
};


class Anneau : public Equipement {
public:
    Anneau();

    Anneau(std::string nom_);

    virtual void equiper(Heros *h, bool droite);

    virtual Anneau *clone() const;
};


class Gants : public Equipement {
public:
    Gants();

    Gants(std::string nom_);

    virtual void equiper(Heros *h, bool droite);

    virtual Gants *clone() const;
};


class Jambes : public Equipement {
public:
    Jambes();

    Jambes(std::string nom_);

    virtual void equiper(Heros *h, bool droite);

    virtual Jambes *clone() const;
};


class Bottes : public Equipement {
public:
    Bottes();

    Bottes(std::string nom_);

    virtual void equiper(Heros *h, bool droite);

    virtual Bottes *clone() const;
};


class Arme : public Equipement {
public:
    Arme();

    Arme(std::string nom_);

    virtual void equiper(Heros *h, bool droite);

    virtual Arme *clone() const;
};


class Torse : public Equipement {
public:
    Torse();

    Torse(std::string nom_);

    virtual void equiper(Heros *h, bool droite);

    virtual Torse *clone() const;
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


    void deplacement(CarteduMonde &carte, int x1, int y1, bool gestion);

    // Permet à l'unité de choisir son action
    // A IMPLEMENTER
    void choixAction();

    virtual std::vector<Sbire *> getArmee();
    virtual void ajouteSbire(Sbire* s);

    virtual void tueUnite();

    // Fonction simple permettant d'afficher les cases disponibles pour le Heros, ou de les enlever
    std::vector<std::vector<int> > afficheCaseDisponibleOnOff(CarteduMonde &carte, bool b, float &deplacement,
                                                              int case_a_atteindre);

    void deplaceVersCase(Case &c2, Case &c1);

    // ATTENTION, cette fonction peut rencontrer des problemes lorsque l'on modifie la fonction boutonAction
    void tourCombat(CarteduMonde &carte, Bouton boutonFinTour, Bouton boutonAction);

    void attaque(Attaque attq, CarteduMonde &carte);

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
    virtual void achete(Ville* ville, int i, bool b);

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
//    std::vector<Bouton> boutonAction(CarteduMonde& carte);


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
    virtual void equipe(Ville* ville, int i, bool droite = true);

    // Fonction vide ici
    virtual std::string getNomCasque();

    // Destructeur de la classe Unite (sert a creer celui de la classe Heros)
    virtual ~Unite();
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
    virtual void equipe(Ville* ville, int i, bool droite = true);

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

    // Achète le i-ème objet dans la ville
    virtual void achete(Ville* ville, int i, bool b);

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