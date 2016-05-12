#include "camp.h"

Camp::Camp(){
}

Camp::Camp(std::vector<Unite*> unite, std::vector<Ville*> villes){
    herosCamp.resize(unite.size());
    for (int i = 0; i < unite.size(); i++) {
        herosCamp[i] = *unite[i];
    }

    villesCamp.resize(villes.size());
    for (int i = 0; i < villes.size(); i++) {
        villesCamp[i] = *villes[i];
    }
}

Camp::Camp(std::vector<Unite*> unite){
    herosCamp.resize(unite.size());
    for (int i = 0; i < unite.size(); i++) {
        herosCamp[i] = *unite[i];
    }
}

void Camp::tourGestion(Carte &carte, std::vector<Unite *> unites, Bouton boutonFinTour, Bouton boutonSauvegarde, Bouton boutonAction, Bouton boutonInventaire, bool &save) {
    int x = 0, y = 0;

    while (true) {
        int x = -1, y = -1, x1 = -1, y1 = -1;
        survole(x1, y1);
        clic(x, y, carte);
        int u = 0;

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
            while (unites[u]->getCase() != numeroCase(x, y)) {
                u += 1;
            }

            float dep = unites[u]->getDep();

            unites[u]->afficheCaseDisponibleOnOff(carte, true, dep, 0);
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
                unites[u]->ouvreInventaire();
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
                unites[u]->deplacement(carte, x, y);
            }

            boutonSauvegarde.affiche();
            boutonFinTour.affiche();

            unites[u]->afficheCaseDisponibleOnOff(carte, false, dep, 0);
        }
    }
}
