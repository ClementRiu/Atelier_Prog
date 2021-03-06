// C'est très bizarre/sale, tant pis
#include "../Gestion/joueurs.cpp"

#include "../Gestion/unite.h"
#include <Imagine/Graphics.h>
#include "../Gestion/carte.h"

int main() {
    Imagine::openWindow(width, height);

    Ville* v = new Ville();

    Bouton boutonFinTour(ZoneBoutonFinTour, Imagine::BLACK, "End turn");
    Bouton boutonAction(ZoneBoutonAction, Imagine::BLACK, "Action");
    Bouton boutonInventaire(ZoneBoutonInventaire, Imagine::BLACK, "Inventaire");
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

    Carte carte(v);

    // Initialisation des unites
    std::vector<Unite *> unites;
    unites.push_back(new Unite(1, 5, 5, 204, 120));
    unites.push_back(new Unite(1, 10, 10, 203, 100));
    carte[204].flagHeros(unites[0]);
    carte[203].flagHeros(unites[1]);

    // Affichage des cases
    for (int i = 0; i < NbCase; i++) {
        for (int j = 0; j < NbCase; j++) {
            carte[NbCase * j + i].affiche();
        }
    }

    FilePriorite<Unite> fileUnites;
    fileUnites.push(unites[0]);
    fileUnites.push(unites[1]);


    int i = 1; //numéro du tour, à remplacer

    while (true) {
        //règles d'initiative assez arbitraires, à modifier #Nathanael
        Unite* unitJouable = fileUnites.pop();
        unitJouable->tourCombat(carte, unites, boutonFinTour, boutonAction);
        unitJouable->changeInitiativeTemporaire();
        fileUnites.push(unitJouable);
        i += 1;
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

