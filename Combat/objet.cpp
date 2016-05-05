#include "objet.h"
#include "../Gestion/unite.h"


Objet::Objet() {

}


Objet::Objet(std::string nom_) {
    nom = nom_;
}


Objet::Objet(const Objet& o){
    nom = o.nom;
    type = o.type;
}


bool Objet::operator==(const Objet &B) const {
    if (nom.compare(B.nom) == 0) {
        return true;
    }
    return false;
}


std::string Objet::getNom(){
    return nom;
}


void Objet::equiper(Heros *h, bool droite){

}


// Existe-t-il un moyen propre de coder cette fonction ?
Bouton Objet::creeBouton(Objet *obj, int xmin, int &ymin, int xmax, int &ymax){
    if (typeid(*this) == typeid(*obj)){
        Bouton b(xmin, ymin, xmax, ymax, Imagine::BLACK, this->getNom());
        ymin += 2 * Police;
        ymax += 2 * Police;
        return b;
    }
    else{
        Bouton b(0, 0, 0, 0, Imagine::BLACK, "");
        return b;
    }
}


Equipement::Equipement(){

}


Equipement::Equipement(const Equipement &eq) : Objet(eq){
    type=eq.type;

    PV=eq.type;
    mana=eq.mana;
    force=eq.force;
    defense=eq.defense;
    dexterite=eq.dexterite;
    initiative=eq.initiative;

    PDep=eq.PDep;
}


Equipement::Equipement(std::string nom_) : Objet(nom_){

}


int Equipement::getType() {
    return type;
}


void Casque::equiper(Heros *h, bool droite){
    *this = h->equipeCasque(*this);
}


Casque::Casque(){

}


Casque::Casque(std::string nom_) : Equipement(nom_){

}


void Anneau::equiper(Heros *h, bool droite){
    if (droite){
        *this = h->equipeAnneauDroite(*this);
    }
    else{
        *this = h->equipeAnneauGauche(*this);
    }
}


void Gants::equiper(Heros *h, bool droite){
    *this = h->equipeGants(*this);
}


void Jambes::equiper(Heros *h, bool droite){
    *this = h->equipeJambes(*this);
}


void Bottes::equiper(Heros *h, bool droite){
    *this = h->equipeBottes(*this);
}


void Arme::equiper(Heros *h, bool droite){
    if (droite){
        *this = h->equipeArmeDroite(*this);
    }
    else{
        *this = h->equipeArmeGauche(*this);
    }
}


void Torse::equiper(Heros *h, bool droite){
    *this = h->equipeTorse(*this);
}


/*
Arme::Arme() {

}

Arme::Arme(int deg, int att, int def, int type) {
    degat = deg;
    bonus_attaque = att;
    bonus_defense = def;
    type_de_degat = type;
}

int Arme::get_degat() {
    return degat;
}

int Arme::get_bonus_attaque() {
    return bonus_attaque;
}

int Arme::get_bonus_defense() {
    return bonus_defense;
}

int Arme::get_type_de_degat() {
    return type_de_degat;
}

void Arme::set_degat(int deg) {
    degat = deg;
}

void Arme::set_attaque(int att) {
    bonus_attaque = att;
}

void Arme::set_defense(int def) {
    bonus_defense = def;
}

void Arme::set_type_de_degat(int type) {
    type_de_degat = type;
}


Armure::Armure() {

}

Armure::Armure(int def, int res[nb_res]) {
    bonus_defense = def;
    for (int i = 0; i < nb_res; i++) {
        bonus_resistance[i] = res[i];
    }
}


int Armure::get_defense() {
    return bonus_defense;
}

int Armure::getbonus_resistance(int i) {
    return bonus_resistance[i];
}

void Armure::set_defense(int def) {
    bonus_defense = def;
}

void Armure::set_bonus_resistance(int res[nb_res]) {
    for (int i = 0; i < nb_res; i++) {
        bonus_resistance[i] = res[i];
    }
}
*/





