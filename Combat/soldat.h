/*
#include "objet.h"
#include <vector>

class Soldat{
    int PV;
    int attaque;
    int bonus_degat;
    int defense;
    Equipement arme;
    Equipement armure;
    int resistance [NB_RES];// fonctionne en pourcentage
public:
    // constructeurs
    Soldat();
    Soldat(int pv, int att, int bonus, int def, Equipement arm, Equipement armu, int res [NB_RES]);
    //accesseur
    int get_PV();
    int get_attaque();
    int get_bonus_degat();
    int get_defense();
    Equipement get_arme();
    Equipement get_armure();
    int get_resistance(int i);
    // les setteurs
    void set_PV(int pv);
    void set_attaque(int att);
    void set_bonus_degat(int bonus);
    void set_defense(int def);
    void set_arme(Equipement arm);
    void set_armure(Equipement armu);
    void set_resistance(int res [NB_RES]);

    //calcul des carac totales, avec les modificateurs
    int att_tot();
    int def_tot();
    int degat_tot();
    int res_tot(int i);
    // fonctions plus complexes
    bool frappe(Soldat s);
    int blesse(Soldat s);
    int est_blesse(int degat);
};
*/