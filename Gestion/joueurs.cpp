#include "joueurs.h"
#include <iterator>
#include <sstream>

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

#if 0
    update_ameliorable();
    update_recrutable();
    update_achetable();
#endif
}


Ville::~Ville() {
    achetable.~Inventaire();
}


int Ville::get_id() const {
    return id;
}


void Ville::ouvreVille(Unite *h) {
    h->ouvreVille(this);
}


void Ville::ajoute(Mere *obj) {
    achetable.ajoute(obj);
}


Mere *Ville::getObjet(int i) {
    return achetable.get(i);
}

Inventaire &Ville::getInventaire() {
    return achetable;
}

Joueur::Joueur(int num) {
    id = num;
    for (int i = 0; i < NB_RESSOURCES; i++) {
        ressources[i] = 0;
    }
    score = 0;
    nb_heros_max_joueur = 1;

}


Joueur::Joueur(int idj, std::vector<Unite *> unite, std::vector<Ville *> villes) {
    id = idj;
    herosJoueur.resize(unite.size());
    for (int i = 0; i < unite.size(); i++) {
        herosJoueur[i] = unite[i];
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
        herosJoueur[i] = unite[i];
    }
    for (int i = 0; i < NB_RESSOURCES; i++) {
        ressources[i] = 0;
    }
    score = 0;
    nb_heros_max_joueur = 1;
}


//gros tas de get
int Joueur::get_id() const {
    return id;
}


void Joueur::finTourGestion() {
    for (int i = 0; i < herosJoueur.size(); ++i) {
        herosJoueur[i]->setDep(herosJoueur[i]->getDepMax());
    }

    for (int i = 0; i < herosJoueur.size(); ++i) {
        std::cout << herosJoueur[i]->getDep() << std::endl;
    }

    for (int i = 0; i < NB_RESSOURCES; i++) {
        ressources[i] += revenus[i];
    }
}


void Joueur::tourGestion(Carte &carte, Bouton boutonFinTour, Bouton boutonSauvegarde,
                         Bouton boutonAction, Bouton boutonInventaire, bool &quit) {
    Unite *unite;

    ///////////////////ATTENTION AFFICHAGE CLEMENT/////////////////////////////////////
    //affiche(ressources)

    LOOP: //sorte de "point de repère" : avec un "goto LOOP" on peut retourner au début de la boucle
    while (true) {
        int x = -1, y = -1, x1 = -1, y1 = -1;
        survole(x1, y1);

        clic(x, y, carte);

        // Le bouton sauvegarde estil active ?
        if (boutonFinTour.boutonActive(x, y)) {
            finTourGestion();
            break;
        }

        // Le bouton FinTour est-il active ?
        if (boutonSauvegarde.boutonActive(x, y)) {
            sauvegarde(herosJoueur);
            quit = true;
            break;
        }
        // Vient-on de cliquer sur une unite ?
        if (numeroCase(x, y) != -1 && carte[numeroCase(x, y)].getOccupe()) {
            unite = carte[numeroCase(x, y)].getUnite();

            //Si l'unité sur laquelle on vient de cliquer n'est pas au joueur concerné, on retourne au début de la boucle
            if (get_id() != unite->getID()) {
                goto LOOP;
            }

            float dep = unite->getDep();

            //On affiche les cases accessibles en déplacement
            unite->afficheCaseDisponibleOnOff(carte, true, dep, 0);
            boutonAction.affiche();
            boutonInventaire.affiche();

            clic(x, y, carte);

            carte.affiche();

            // Bouton inventaire
            if (boutonInventaire.boutonActive(x, y)) {
                unite->ouvreInventaire();
                // unites[u]->equipe(1);
                // unites[u]->ouvreInventaire();
                // Reaffichage de la carte
                carte.affiche();
            }


            else {
                //On regarde si l'utilisateur a cliqué sur une case adjacente, pour éventuellement déclancher un évènement
                if ((abs(unite->getCase() - numeroCase(x, y)) == 1 ||
                     abs(unite->getCase() - numeroCase(x, y)) == NbCase) && numeroCase(x, y) != -1) {
                    //On déclanche un évènement (ex : ouvrir une ville) si on a affaire à une case spéciale
                    carte[numeroCase(x, y)].action(unite);
                    carte.affiche();

                    //S'il y a un héros, on déclanche un combat
                    if (carte[numeroCase(x, y)].getOccupe()) {
                        Unite *uniteCliquee = carte[numeroCase(x, y)].getUnite();

                        //Si l'unité n'est pas à nous, on déclenche effectivement le combat
                        if (unite->getID() != uniteCliquee->getID()) {
                            float PDepGestion = unite->getDep();
                            unite->setDep(unite->getDepMax());
                            unite->declencheCombat(uniteCliquee);
                            carte.affiche();
                            unite->setDep(PDepGestion);
                        }
                    }
                }
                //Si rien de tout cela n'a été fait, on lance la phase de déplacement
                unite->deplacement(carte, x, y, true);
            }

            boutonSauvegarde.affiche();
            boutonFinTour.affiche();

            //on enlève la surbrillance des cases disponibles au déplacement
            unite->afficheCaseDisponibleOnOff(carte, false, dep, 0);
        }
    }
}

#if 0
void Ville::update_recrutable() {
    // VA DEPENDRE DU CAMP ET DES BATIMENTS, A VOIR PLUS TARD AVEC LE GAMEPLAY
}

void Ville::update_ameliorable() {
    // VA DEPENDRE DU CAMP ET DES BATIMENTS, A VOIR PLUS TARD AVEC LE GAMEPLAY
}

void Ville::update_achetable() {
    // VA DEPENDRE DU CAMP ET DES BATIMENTS, A VOIR PLUS TARD AVEC LE GAMEPLAY
}

void Ville::ameliore(int i) {
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

void Ville::set_heros_present(bool b) {
    heros_present = b;
}

int Ville::get_lv_batiment(int i) {
    return batiments[i];
}

Armee Ville::get_garnison() {
    return garnison;
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

int Joueur::get_ressources(int i) {
    return ressources[i];
}

int Joueur::get_score() {
    return score;
}

int Joueur::get_nb_heros_max_joueur() {
    return nb_heros_max_joueur;
}


std::vector<Unite*> Joueur::get_herosJoueur() {
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

void Joueur::tue_heros(Unite* mort) {
    //à faire dès que les héros ont une idée
}

void Joueur::recrute_heros(Unite* recrue) {
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

void Ville::retire(int i) {
    achetable.retire(i);
}
#endif
