#include "../Gestion/unite.h"
#include <Imagine/Graphics.h>
#include "../Gestion/carte.h"

int main() {
    Imagine::openWindow(width, height);

    Bouton boutonSauvegarde(ZoneBoutonSauvegarde, Imagine::BLUE, "Save & Quit");
    Bouton boutonFinTour(ZoneBoutonFinTour, Imagine::BLACK, "End turn");
    Bouton boutonAction(ZoneBoutonAction, Imagine::BLACK, "Action");
    Bouton boutonInventaire(ZoneBoutonInventaire, Imagine::BLACK, "Inventaire");
    boutonSauvegarde.affiche();
    boutonFinTour.affiche();
    boutonAction.affiche();
    boutonInventaire.affiche();

    // Initialisation d'une attaque
    std::vector<Imagine::Coords<2> > zoneInfl;
    zoneInfl.push_back(portee10);
    zoneInfl.push_back(portee_10);
    zoneInfl.push_back(portee20);
    zoneInfl.push_back(portee_20);
    zoneInfl.push_back(portee01);
    zoneInfl.push_back(portee02);
    zoneInfl.push_back(portee0_2);
    zoneInfl.push_back(portee0_1);
    Attaque coinCoinOuille(zoneInfl, 10);

    Carte carte;

    // Initialisation des unites
    std::vector<Unite *> unites;
    carte[204].flagHeros();
    carte[203].flagHeros();
    unites.push_back(new Unite(5, 204));
    unites.push_back(new Unite(10, 203));

    // Affichage des cases
    for (int i = 0; i < NbCase; i++) {
        for (int j = 0; j < NbCase; j++) {
            carte[NbCase * j + i].affiche();
        }
    }


    Unite unit;


    while (true) {
        unites[0]->tourCombat(carte, unites, boutonFinTour, boutonAction);
        unites[1]->tourCombat(carte, unites, boutonFinTour, boutonAction
        );
    }

    Imagine::endGraphics();

    // Destruction des unités
    for (int i = 0; i < unites.size(); ++i) {
        unites[i]->~Unite();
        delete unites[i];
        unites[i] = 0;
    }
    return 0;
}

