#include "ville.h"



Ville::Ville(int faction){
    for (int i=0; i<NB_BATIMENTS; i++){
        batiments[i] = 0;
    }
    camp = faction;
    heros_present = false;
    achetable = new Objet[0];
    update_ameliorable();
    update_recrutable();
    update_achetable();
}


Ville::~Ville(){
    delete [] achetable;
}


void Ville::construction(int i){
    batiments[i] += 1;
    update_ameliorable();
}


void Ville::recrute(int i){     //on suppose que la fonction ne se lance pas si recrutable[i] = 0
    //ICI RAJOUTER FONCTION POUR RAJOUTER DES SOLDATS DANS L'ARMEE
    //ICI RAJOUTER FONCTION POUR DIMINUER LES RESSOURCES
    recrutables[i] -= 1;
}


void Ville::achat(int i){
    //a faire
}


void Ville::update_recrutable(){
    // VA DEPENDRE DU CAMP ET DES BATIMENTS, A VOIR PLUS TARD AVEC LE GAMEPLAY
}


void Ville::update_ameliorable(){
    // VA DEPENDRE DU CAMP ET DES BATIMENTS, A VOIR PLUS TARD AVEC LE GAMEPLAY
}


void Ville::update_achetable(){
    // VA DEPENDRE DU CAMP ET DES BATIMENTS, A VOIR PLUS TARD AVEC LE GAMEPLAY
}


void Ville::set_heros_present(bool b){
    heros_present = b;
}


int Ville::get_lv_batiment(int i){
    return batiments[i];
}


Armee Ville::get_garnison(){
    return garnison;
}


int Ville::get_nb_recrue(int type){
    return recrutables[type];
}


Objet* Ville::get_magasin(){
    return achetable;
}


int Ville::get_camp(){
    return camp;
}


bool Ville::est_ameliorable(int i){
    return amelioration[i];
}


bool Ville::get_heros_present(){
    return heros_present;
}
