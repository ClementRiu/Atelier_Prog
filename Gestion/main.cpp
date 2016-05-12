#include "carte.h"
#include "unite.h"


int main() {
    Imagine::openWindow(width, height);

    Carte carte;

    // Initialisation des unites
    bool load = false;
    std::vector<Unite *> unites;
    if (load) {
        charge(unites, carte);
    }
    else {
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
    unites[0]->ramasse(new Arme("hache"));
    unites[0]->ramasse(new Jambes("genouillères"));
    unites[0]->ramasse(new Gants("gants de cuir"));
    unites[0]->ramasse(new Objet("clafoutis"));
    unites[0]->ramasse(new Objet("concombre"));
    unites[0]->ramasse(new Objet("creme brulee"));
    unites[0]->ramasse(new Objet("pain"));
    unites[0]->ramasse(new Objet("confiture"));
    unites[0]->ramasse(new Objet("fromage"));
    unites[0]->ramasse(new Objet("zinzifruits"));
    unites[0]->ramasse(new Objet("roche"));
    unites[0]->ramasse(new Objet("cle"));
    unites[0]->ramasse(new Objet("rat mort"));
    unites[0]->ramasse(new Objet("boite a outils"));

    Inventaire i;
    i.ajoute(new Objet("merde"));
    i.ajoute(new Jambes("genouillères"));
    i.ajoute(new Casque("casque"));
    Inventaire j(i);

    // Ecran de menu
    Bouton nouvellePartie(width / 4, height / 2 - 20, 3 * width / 4, height / 2 + 20, Imagine::BLUE, "Nouvelle Partie");
    int x = 0, y = 0;
    nouvellePartie.affiche();
    while (!nouvellePartie.boutonActive(x, y)) {
        clicSimple(x, y);
    }

    // Affichage des cases
    for (int i = 0; i < NbCase; i++) {
        for (int j = 0; j < NbCase; j++) {
            carte[NbCase * j + i].affiche();
        }
    }

    // Creation et affichage des boutons
    Bouton boutonSauvegarde(ZoneBoutonSauvegarde, Imagine::BLUE, "Save & Quit");
    Bouton boutonFinTour(ZoneBoutonFinTour, Imagine::BLACK, "End turn");
    Bouton boutonAction(ZoneBoutonAction, Imagine::BLACK, "Action");
    Bouton boutonInventaire(ZoneBoutonInventaire, Imagine::BLACK, "Inventaire");
    boutonSauvegarde.affiche();
    boutonFinTour.affiche();
    boutonAction.affiche();
    boutonInventaire.affiche();

    // Deplacement des unites
    bool save = true;
    while (save) {
        int x = -1, y = -1, x1 = -1, y1 = -1;
        survole(x1, y1);
        clic(x, y, carte);
        int u = 0;

        // Le bouton sauvegarde estil active ?
        if (boutonFinTour.boutonActive(x, y)) {
            finJournee(unites);
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
                unites[u]->deplacement(carte, false, x, y);
            }

            boutonSauvegarde.affiche();
            boutonFinTour.affiche();

            unites[u]->afficheCaseDisponibleOnOff(carte, false, dep, 0);
            boutonAction.affiche();
            boutonInventaire.affiche();
        }
    }


    // Destruction des unités
    // EST CE QUE CA MARCHE VRAIMENT ????? FUITE ????
    for (int i = 0; i < unites.size(); ++i) {
        //delete unites[i];
        unites[i] = 0;
    }
    Imagine::endGraphics();
    return 0;
}

