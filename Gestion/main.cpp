#include "carte.h"
#include "unite.h"


int main() {
    Imagine::openWindow(width, height);

    // Initialisation des types de case
    TypeCase eau(INF, "De l'eau, sans vie, sans poisson, rien que de l'eau", Imagine::BLUE);
    TypeCase herbe(2, "C'est vert, les souris s'y cachent, c'est de l'herbe", Imagine::GREEN);
    TypeCase route(1, "Une case a moindre cout de deplacement", Imagine::YELLOW);
    TypeCase ville(1, descVille, Imagine::MAGENTA);

    // Initialisation de la carte
    Case carte[NbCase * NbCase];

    // Creation de la carte
    for (int i = 0; i < NbCase * Taille; i += Taille) {
        for (int j = 0; j < NbCase * Taille; j += Taille) {
            if ((i + 1) % (j + 1) == 0) {
                Case c(i, j, eau);
                carte[numeroCase(i, j)] = c;
            }
            if ((i + 1) % (j + 1) == 1) {
                Case c(i, j, herbe);
                carte[numeroCase(i, j)] = c;
            }
            if ((i + 1) % (j + 1) > 1) {
                Case c(i, j, route);
                carte[numeroCase(i, j)] = c;
            }
        }
    }
    Case c(0, 0, ville);
    carte[0] = c;

    // Initialisation des unites
    bool load = false;
    std::vector<Unite*> unites;
    if (load) {
        charge(unites, carte);
    }
    else{
        carte[304].flagHeros();
        carte[303].flagHeros();
        unites.push_back(new Heros(5, 304));
        unites.push_back(new Unite(10, 303));
    }

    // Remplissage de l'inventaire de la première unité qui est bien un héros
    unites[0]->ramasse(new Objet("merde"));
    unites[0]->ramasse(new Casque("casque"));
    unites[0]->ramasse(new Objet("merde"));
    unites[0]->ramasse(new Objet("merde"));
    unites[0]->ramasse(new Objet("merde"));

    // Ecran de menu
    Bouton nouvellePartie(width/4, height/2-20, 3*width/4, height/2+20, Imagine::BLUE, "Nouvelle Partie");
    int x = 0, y = 0;
    nouvellePartie.affiche();
    while (!nouvellePartie.boutonActive(x, y)){
        clicSimple(x, y);
    }

    // Affichage des cases
    for (int i = 0; i < NbCase; i++) {
        for (int j = 0; j < NbCase; j++) {
            carte[NbCase * j + i].affiche();
        }
    }

    // Creation et affichage des boutons
    Bouton boutonSauvegarde(NbCase * Taille + Separation, Taille * (NbCase - 5) - LargDroite - 10,
                            NbCase * Taille + Separation + LargDroite, Taille * (NbCase - 5), Imagine::BLUE,
                            "Save & Quit");
    Bouton boutonFinTour(NbCase * Taille + Separation, Taille * (NbCase - 5),
                         NbCase * Taille + Separation + LargDroite, NbCase * Taille, Imagine::BLACK,
                         "End turn");
    boutonSauvegarde.affiche();
    boutonFinTour.affiche();

    // Deplacement des unites
    bool save = true;
    while (save) {
        int x = -1, y = -1, x1 = -1, y1 = -1;
        survole(x1, y1);
        clic(x, y, carte);
        int u = 0;        
        if (boutonFinTour.boutonActive(x, y)) {
            finJournee(unites);
        }
        if (boutonSauvegarde.boutonActive(x, y)) {
            sauvegarde(unites);
            save = false;
        }
        if (numeroCase(x, y) != -1 && carte[numeroCase(x, y)].getOccupe()) {
            while (unites[u]->getCase() != numeroCase(x, y)) {
                u += 1;
            }
            std::vector<Bouton> boutons = unites[u]->boutonAction(carte);
            for (int i=0; i < boutons.size(); ++i){
                boutons[i].affiche();
            }

            clic(x, y, carte);

            // A modifier
            for (int i = 0; i < NbCase; ++i){
                for (int j = 0; j < NbCase; ++j){
                    carte[j * NbCase + i].affiche();
                }
            }
            // Bouton deplacement
            if (boutons[2].boutonActive(x, y)) {
                unites[u]->deplacement(carte);
            }
            // Bouton inventaire
            if (boutons[1].boutonActive(x, y)) {
                unites[u]->ouvreInventaire();
                // unites[u]->equipe(1);
                // unites[u]->ouvreInventaire();
                // Reaffichage de la carte
                for (int i = 0; i < NbCase; i++) {
                    for (int j = 0; j < NbCase; j++) {
                        carte[NbCase * j + i].affiche();
                    }
                }
                boutonSauvegarde.affiche();
                boutonFinTour.affiche();
            }
        }
    }

    // Destruction des unités
    for (int i = 0; i < unites.size(); ++i){
        unites[i]->~Unite();
        delete unites[i];
        unites[i] = 0;
    }
    Imagine::endGraphics();
    return 0;
}

