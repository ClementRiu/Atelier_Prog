#include "joueurs.h"
#include <iterator>

Ville::Ville() {

}

Ville::Ville(int num) {
    id = num;
}

Ville::Ville(int faction, int num) {
    id = num;
    for (int i = 0; i < NB_BATIMENTS; i++) {
        batiments[i] = 0;
    }
    camp = faction;
    heros_present = false;
    achetable = Inventaire();
    update_ameliorable();
    update_recrutable();
    update_achetable();
}


Ville::~Ville() {
    achetable.~Inventaire();
}


void Ville::construction(int i) {
    batiments[i] += 1;
    update_ameliorable();
}


void Ville::recrute(int i) {     //on suppose que la fonction ne se lance pas si recrutable[i] = 0
    //ICI RAJOUTER FONCTION POUR RAJOUTER DES SOLDATS DANS L'ARMEE
    //ICI RAJOUTER FONCTION POUR DIMINUER LES RESSOURCES
    recrutables[i] -= 1;
}


void Ville::achat(int i) {
    //a faire
}


void Ville::update_recrutable() {
    // VA DEPENDRE DU CAMP ET DES BATIMENTS, A VOIR PLUS TARD AVEC LE GAMEPLAY
}


void Ville::update_ameliorable() {
    // VA DEPENDRE DU CAMP ET DES BATIMENTS, A VOIR PLUS TARD AVEC LE GAMEPLAY
}


void Ville::update_achetable() {
    // VA DEPENDRE DU CAMP ET DES BATIMENTS, A VOIR PLUS TARD AVEC LE GAMEPLAY
}


void Ville::set_heros_present(bool b) {
    heros_present = b;
}


int Ville::get_lv_batiment(int i) {
    return batiments[i];
}


Armee Ville::get_garnison() {
    return garnison;
}

int Ville::get_id() const {
    return id;
}


int Ville::get_nb_recrue(int type) {
    return recrutables[type];
}



int Ville::get_camp() {
    return camp;
}


bool Ville::est_ameliorable(int i) {
    return amelioration[i];
}


bool Ville::get_heros_present() {
    return heros_present;
}


void Ville::ouvreVille(Heros* h) {
    // Creation des differents boutons pour les differentes categories d'objets
    std::vector<Bouton> boutonsChoix;
    std::vector<std::string> nomBoutons;
    nomBoutons.push_back("Arme");
    nomBoutons.push_back("Anneau");
    nomBoutons.push_back("Bottes");
    nomBoutons.push_back("Gants");
    nomBoutons.push_back("Jambes");
    nomBoutons.push_back("Torse");
    nomBoutons.push_back("Casque");
    nomBoutons.push_back("Objets divers");
    for (int i = 0; i < nomBoutons.size(); ++i) {
        Bouton b(0, Police * i, 140, Police * (i + 1), Imagine::BLACK, nomBoutons[i]);
        boutonsChoix.push_back(b);
    }

    // Creation des differentes categories d'objets
    Inventaire categoriesObjets;
    categoriesObjets.ajoute(new Arme());
    categoriesObjets.ajoute(new Anneau());
    categoriesObjets.ajoute(new Bottes());
    categoriesObjets.ajoute(new Gants());
    categoriesObjets.ajoute(new Jambes());
    categoriesObjets.ajoute(new Torse());
    categoriesObjets.ajoute(new Casque());
    categoriesObjets.ajoute(new Objet());

    // Creation du pointeur vers la fonction equipe
    void (Unite::*pointeurFonction)(Ville*, int, bool) = &Unite::achete;

    achetable.ouvreInventaire(boutonsChoix, categoriesObjets, this, h, pointeurFonction);
    //inventaire.ouvreInventaire(boutonsChoix, categoriesObjets, this, pointeurFonction);
}


void Ville::retire(int i) {
    achetable.retire(i);
}


Mere* Ville::getObjet(int i) {
    return achetable.get(i);
}


Joueur::Joueur(int num) {
    id = num;
    for (int i = 0; i < NB_RESSOURCE; i++) {
        ressources[i] = 0;
    }
    score = 0;
    int couleur = num;
    population = 0;
    nb_heros_max_joueur = 1;

}


Joueur::Joueur(int idj, std::vector<Unite *> unite, std::vector<Ville *> villes) {
    id = idj;
    herosJoueur.resize(unite.size());
    for (int i = 0; i < unite.size(); i++) {
        herosJoueur[i] = *unite[i];
    }

    villesJoueur.resize(villes.size());
    for (int i = 0; i < villes.size(); i++) {
        villesJoueur[i] = *villes[i];
    }
}

Joueur::Joueur(int idj, std::vector<Unite *> unite) {
    id = idj;
    herosJoueur.resize(unite.size());
    for (int i = 0; i < unite.size(); i++) {
        herosJoueur[i] = *unite[i];
    }
    for (int i = 0; i < NB_RESSOURCE; i++) {
        ressources[i] = 0;
    }
    score = 0;
    int couleur = 0;
    population = 0;
    nb_heros_max_joueur = 1;
}


//gros tas de get
int Joueur::get_id() const {
    return id;
}

//bool get_humain();
int Joueur::get_ressources(int i) {
    return ressources[i];
}

int Joueur::get_score() {
    return score;
}

int Joueur::get_couleur() {
    return couleur;
}

int Joueur::get_population() {
    return population;
}

int Joueur::get_nb_heros_max_joueur() {
    return nb_heros_max_joueur;
}


std::vector<Unite> Joueur::get_herosJoueur() {
    return herosJoueur;
}

//ATTENTION herosJoueurs EST UN VECTEUR d'UNITES !!
std::vector<Ville> Joueur::get_villesJoueur() {
    return villesJoueur;
}


//modifications des valeurs
void Joueur::modifie_ressources(int res, int valeur) {
    ressources[res] += valeur;
}

void Joueur::add_score(int points) {
    score += points;
}

void Joueur::update_pop(int valeur) {
    population += valeur;
}

void Joueur::tue_heros(Heros mort) {
    //à faire dès que les héros ont une idée
}

void Joueur::recrute_heros(Heros recrue) {
    herosJoueur.push_back(recrue);
}


void Joueur::conquiert_ville(Ville conquete) {
    villesJoueur.push_back(conquete);
}

void Joueur::perd_ville(Ville perte) {
    int k = -1;
    int n = villesJoueur.size();
    for (int i = 0; i < n; i++) {
        if (villesJoueur[i].get_id() == perte.get_id()) {
            k = i;
        }
    }
    assert (k != -1);

    villesJoueur.erase(villesJoueur.begin() + k);
}


void Joueur::tourGestion(Carte &carte, std::vector<Unite *> unites, Bouton boutonFinTour, Bouton boutonSauvegarde,
                         Bouton boutonAction, Bouton boutonInventaire, bool &save) {
    Unite *unite = unites[0];

    LOOP:
    while (true) {
        int x = -1, y = -1, x1 = -1, y1 = -1;
        survole(x1, y1);

        clic(x, y, carte);

        // Le bouton sauvegarde estil active ?
        if (boutonFinTour.boutonActive(x, y)) {
            break;
        }

        // Le bouton FinTour est-il active ?
        if (boutonSauvegarde.boutonActive(x, y)) {
            sauvegarde(unites);
            save = false;
        }
        // Vient-on de cliquer sur une unite ?
        if (numeroCase(x, y) != -1 && carte[numeroCase(x, y)].getOccupe()) {
            unite = carte[numeroCase(x, y)].getUnite();

            if (get_id() != unite->getID()) {
                goto LOOP;
            }

            float dep = unite->getDep();

            unite->afficheCaseDisponibleOnOff(carte, true, dep, 0);
            boutonAction.affiche();
            boutonInventaire.affiche();

            clic(x, y, carte);

            // A modifier
            for (int i = 0; i < NbCase; ++i) {
                for (int j = 0; j < NbCase; ++j) {
                    carte[j * NbCase + i].affiche();
                }
            }
            // Bouton inventaire
            if (boutonInventaire.boutonActive(x, y)) {
                unite->ouvreInventaire();
                // unites[u]->equipe(1);
                // unites[u]->ouvreInventaire();
                // Reaffichage de la carte
                for (int i = 0; i < NbCase; i++) {
                    for (int j = 0; j < NbCase; j++) {
                        carte[NbCase * j + i].affiche();
                    }
                }
            }
            else {
                unite->deplacement(carte, x, y);
            }

            boutonSauvegarde.affiche();
            boutonFinTour.affiche();

            unite->afficheCaseDisponibleOnOff(carte, false, dep, 0);
        }
    }
}
