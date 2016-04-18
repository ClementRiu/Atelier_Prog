#include "objet.h"


Objet::Objet() {

}

Objet::Objet(std::string nom_) {
    nom = nom_;
}


bool Objet::operator==(const Objet &B) const {
    if (nom.compare(B.nom) == 0) {
        return true;
    }
    return false;
}

int Equipement::getType() {
    return type;
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





