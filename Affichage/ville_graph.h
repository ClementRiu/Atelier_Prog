#include "constante.h"

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