
#include "objet.h"
#include <vector>

class Soldat{
    int PV;
    int attaque;
    int bonus_degat;
    int defense;
    Arme arme;
    Armure armure;
    int resistance [nb_res];// fonctionne en pourcentage
public:
    // constrcteurs
    Soldat();
    Soldat(int pv, int att, int bonus, int def, Arme arm, Armure armu, int res [nb_res]);
    //accesseur
    int get_PV();
    int get_attaque();
    int get_bonus_degat();
    int get_defense();
    Arme get_arme();
    Armure get_armure();
    int get_resistance(int i);
    // les setteurs
    void set_PV(int pv);
    void set_attaque(int att);
    void set_bonus_degat(int bonus);
    void set_defense(int def);
    void set_arme(Arme arm);
    void set_armure(Armure armu);
    void set_resistance(int res [nb_res]);

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
