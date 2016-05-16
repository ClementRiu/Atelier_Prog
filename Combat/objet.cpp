#include "objet.h"
#include "../Gestion/unite.h"


std::string Mere::getNom() {
    return nom;
}


Bouton Mere::creeBouton(Mere *obj, int xmin, int &ymin, int xmax, int &ymax) {
    // On teste l'égalité des types 2 Meres, pour ensuite dans une autre fonction voir si on veut afficher l'objet dans la catégorie ou pas
    if (typeid(*this) == typeid(*obj)) {
        Bouton b(xmin, ymin, xmax, ymax, Imagine::BLACK, this->getNom());
        ymin += EcartementLignesInventaire;
        ymax += EcartementLignesInventaire;
        return b;
    }
        // Si on n'a pas envie de créer de bouton, on crée un bouton vide
    else {
        Bouton b(0, 0, 0, 0, Imagine::BLACK, "");
        return b;
    }
}


void Mere::equiper(Heros *h, bool droite) {

}


Mere::Mere() {

}


Mere::Mere(std::string nom_) {
    nom = nom_;
}


Mere::Mere(const Mere &m) {
    nom = m.nom;
}


Mere *Mere::clone() const {
    return new Mere(*this);
}


Objet::Objet() : Mere() {

}


Objet::Objet(std::string nom_) : Mere(nom_) {

}


bool Objet::operator==(const Objet &B) const {
    if (nom.compare(B.nom) == 0) {
        return true;
    }
    return false;
}


Objet *Objet::clone() const {
    return new Objet(*this);
}


Inventaire::Inventaire() {

}


Inventaire::Inventaire(const Inventaire &inventaireACopier) {
    contenu.resize(inventaireACopier.contenu.size());
    for (int i = 0; i < inventaireACopier.contenu.size(); i++) {
        contenu[i] = inventaireACopier.contenu[i]->clone();
    }
}


int Inventaire::taille() {
    return contenu.size();
}


void Inventaire::ajoute(Mere *obj) {
    contenu.push_back(obj);
}


Mere *Inventaire::get(int i) {
    assert (i < this->taille());
    return contenu[i];
}


// Fonction a modifier
// faire vien plutot de Unite
void Inventaire::ouvreInventaire(std::vector<Bouton> boutonsCategories, Inventaire classeObjets, Ville* ville,
                                 Unite *unite, void (Unite::*faire)(Ville*, int, bool)) {
    Imagine::fillRect(0, 0, width, height, Imagine::WHITE);
    std::vector<Bouton> boutonUtile;
    std::vector<int> objetPresent;

    // Affichage des boutons pour scroller et pour fermer
    Bouton boutonStop(ZoneBoutonFerme, Imagine::BLACK, "Fermer");
    Bouton boutonUp(ZoneBoutonUp, Imagine::BLACK, "Up");
    Bouton boutonDown(ZoneBoutonDown, Imagine::BLACK, "Down");
    boutonStop.affiche();
    boutonUp.affiche();
    boutonDown.affiche();

    // Affichage des boutons des differentes categories
    for (int i = 0; i < boutonsCategories.size(); ++i) {
        boutonsCategories[i].affiche();
    }

    // Acrions possibles dans l'inventaire
    int x, y;
    int decalementVertical = 0; // Cette variable va servir a scroller
    clicSimple(x, y);
    while (!boutonStop.boutonActive(x, y)) {
        // Les entiers suivants vont savoir ou placer le bouton odulo le decalement vertical
        int xmin = BoutonMilieu[0], ymin = Police, xmax = BoutonMilieu[1], ymax = 2 * Police;

        // On regarde si on a clique sur une des categories
        for (int i = 0; i < boutonsCategories.size(); ++i) {
            if (boutonsCategories[i].boutonActive(x, y)) {
                // Quand on clique sur une categorie, tout se reinitialise
                decalementVertical = 0;
                boutonUtile.clear();
                objetPresent.clear();
                for (int j = 0; j < contenu.size(); ++j) {
                    // On cree les differents boutons de la categorie
                    Bouton b = contenu[j]->creeBouton(classeObjets.get(i), xmin, ymin, xmax, ymax);
                    // On regarde si le bouton es vide et si c'est n'est pas le cas, on  le stock ainsi que la position
                    // Dans l'inventaire qui lui est associee
                    if (!b.boutonVide()) {
                        boutonUtile.push_back(b);
                        objetPresent.push_back(j);
                    }
                }
            }
        }

        // On regarde si on a clique sur le bouton Up
        if (boutonUp.boutonActive(x, y)) {
            decalementVertical -= EcartementLignesInventaire;
        }

        // On regarde si on a clique sur le bouton down
        if (boutonDown.boutonActive(x, y)) {
            decalementVertical += EcartementLignesInventaire;
        }

        // On affiche les boutons de la categorie selectionnee
        for (int i = 0; i < boutonUtile.size(); ++i) {
            boutonUtile[i].affiche(decalementVertical);
        }

        // On regarde si on vient de cliquer sur un des boutons specifiques d'une categorie
        for (int i = 0; i < boutonUtile.size(); ++i) {
            if (boutonUtile[i].boutonActive(x, y, decalementVertical)) {
                // Applique une methode de Unite a travers le pointeur faire
                (*unite.*faire)(ville, objetPresent[i], true);
                // On change le nom du bouton et on le reaffiche
                boutonUtile[i].setNom(contenu[objetPresent[i]]->getNom());
                boutonUtile[i].affiche(decalementVertical);
            }
        }

        // On clique, et on efface les objets
        clicSimple(x, y);
        Imagine::fillRect(BoutonMilieu[0], 0, BoutonMilieu[1] - BoutonMilieu[0], height, Imagine::WHITE);
    }
}


void Inventaire::retire(int i){
    std::vector<Mere*>::iterator it;
    it = contenu.begin();
    contenu.erase(it + i);
}


Inventaire::~Inventaire() {
    for (int i = 0; i < contenu.size(); i++) {
        delete contenu[i];
        contenu[i] = 0;
    }
}


Equipement::Equipement() {

}


Equipement::Equipement(const Equipement &eq) : Objet(eq) {
    PV = eq.PV;
    mana = eq.mana;
    force = eq.force;
    defense = eq.defense;
    dexterite = eq.dexterite;
    initiative = eq.initiative;

    PDep = eq.PDep;
}


Equipement::Equipement(std::string nom_) : Objet(nom_) {

}


void Casque::equiper(Heros *h, bool droite) {
    *this = h->equipeCasque(*this);
}


Casque::Casque() {

}


Casque::Casque(std::string nom_) : Equipement(nom_) {

}


void Anneau::equiper(Heros *h, bool droite) {
    if (droite) {
        *this = h->equipeAnneauDroite(*this);
    }
    else {
        *this = h->equipeAnneauGauche(*this);
    }
}


Casque *Casque::clone() const {
    return new Casque(*this);
}


Anneau::Anneau() {

}


Anneau::Anneau(std::string nom_) : Equipement(nom_) {

}


Anneau *Anneau::clone() const {
    return new Anneau(*this);
}


void Gants::equiper(Heros *h, bool droite) {
    *this = h->equipeGants(*this);
}


Gants::Gants() {

}


Gants::Gants(std::string nom_) : Equipement(nom_) {

}


Gants *Gants::clone() const {
    return new Gants(*this);
}


void Jambes::equiper(Heros *h, bool droite) {
    *this = h->equipeJambes(*this);
}


Jambes::Jambes() {

}


Jambes::Jambes(std::string nom_) : Equipement(nom_) {

}


Jambes *Jambes::clone() const {
    return new Jambes(*this);
}


void Bottes::equiper(Heros *h, bool droite) {
    *this = h->equipeBottes(*this);
}


Bottes::Bottes() {

}


Bottes::Bottes(std::string nom_) : Equipement(nom_) {

}


Bottes *Bottes::clone() const {
    return new Bottes(*this);
}


void Arme::equiper(Heros *h, bool droite) {
    if (droite) {
        *this = h->equipeArmeDroite(*this);
    }
    else {
        *this = h->equipeArmeGauche(*this);
    }
}


Arme::Arme() {

}


Arme::Arme(std::string nom_) : Equipement(nom_) {

}


Arme *Arme::clone() const {
    return new Arme(*this);
}


void Torse::equiper(Heros *h, bool droite) {
    *this = h->equipeTorse(*this);
}


Torse::Torse() {

}


Torse::Torse(std::string nom_) : Equipement(nom_) {

}


Torse *Torse::clone() const {
    return new Torse(*this);
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





