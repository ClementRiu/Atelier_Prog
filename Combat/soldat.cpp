#include "soldat.h"


Soldat::Soldat(){

}

Soldat::Soldat(int pv, int att, int bonus, int def, Arme arm, Armure armu,  int res [nb_res]){
    PV =pv;
    attaque = att;
    bonus_degat = bonus;
    arme=arm;
    armure=armu;
    for (int i=0; i<nb_res;i++){
        resistance[i] = res[i];
    }
}

int Soldat::get_PV(){
    return PV;
}

int Soldat::get_attaque(){
    return attaque;
}

int Soldat::get_bonus_degat(){
    return bonus_degat;
}

int Soldat::get_defense(){
    return defense;
}

Arme Soldat::get_arme(){
    return arme;
}

Armure Soldat::get_armure(){
    return armure;
}

int Soldat::get_resistance(int i){
    return resistance[i];
}

void Soldat::set_PV(int pv){
    PV=pv;
}

void Soldat::set_attaque(int att){
    attaque = att;
}

void Soldat::set_bonus_degat(int bonus){
    bonus_degat = bonus;
}

void Soldat::set_defense(int def){
    defense = def;
}

void Soldat::set_arme(Arme arm){
    arme = arm;
}

void Soldat::set_armure(Armure armu){
    armure = armu;
}

void Soldat::set_resistance(int res [nb_res]){
    for (int i=0; i<nb_res;i++){
        resistance[i] = res[i];
    }
}

int Soldat::att_tot(){
    return attaque + arme.get_bonus_attaque();
}

int Soldat::def_tot(){
    return defense + arme.get_bonus_defense() + armure.get_defense();
}

int Soldat::degat_tot(){
    return bonus_degat + arme.get_degat();
}

int Soldat::res_tot(int i){
    return resistance[i] + armure.getbonus_resistance(i);
}

bool Soldat::frappe(Soldat s){
    int de = rand() % 100 + 1;
    int proba = att_tot() - s.def_tot();//attaque totale - defense totale = poucentage de chance de toucher
    return (de < proba);
}

int Soldat::blesse(Soldat s){
    int a = get_arme().get_degat() + get_bonus_degat();//degat = degat de l'arme + bonus de degat du personnage
    int d = s.res_tot(get_arme().get_type_de_degat());// les degat sont reduit du score de resistance
    return (a*(100-d)/100);
}

int Soldat::est_blesse(int degat){
    set_PV(get_PV() - degat);
}


