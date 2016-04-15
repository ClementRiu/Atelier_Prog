#include <stdlib.h>
#include<cstdlib>
const int nb_res= 6 ;

class Objet{
public:
    Objet();
};


class Arme : public Objet{
    int degat;
    int bonus_attaque;
    int bonus_defense;
    int type_de_degat;
public:
    //constructeurs
    Arme();
    Arme(int deg, int att , int def, int type);
    //accesseur
    int get_degat();
    int get_bonus_attaque();
    int get_bonus_defense();
    int get_type_de_degat();
    //setteurs
    void set_degat(int deg);
    void set_attaque(int att);
    void set_defense(int def);
    void set_type_de_degat(int type);
};

class Armure: public Objet{
    int bonus_defense;
    int bonus_resistance [nb_res];// fonctionne en pourcentage
public:
    //constructeurs
    Armure();
    Armure(int def, int res [nb_res]);
    //accesseurs
    int get_defense();
    int getbonus_resistance(int i);
    //setteurs
    void set_defense(int def);
    void set_bonus_resistance(int res [nb_res]);
};
