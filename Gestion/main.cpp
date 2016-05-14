#include "carte.h"
#include "unite.h"
#include "joueurs.h"


int main() {
    Imagine::openWindow(width, height);

    Carte carte;

    // Initialisation des unites
    // Ecran de menu
    std::vector<Unite *> unitesAlliees;
    std::vector<Unite *> unitesEnnemies;

    Bouton nouvellePartie(width / 4, height / 2 - 40, 3 * width / 4, height / 2, Imagine::BLUE, "Nouvelle Partie");
    Bouton chargePartie(width / 4, height / 2 + 50, 3 * width / 4, height / 2 + 90, Imagine::BLUE, "Charge Partie");
    int x = 0, y = 0;
    nouvellePartie.affiche();
    chargePartie.affiche();
    while (!nouvellePartie.boutonActive(x, y) && !chargePartie.boutonActive(x, y)) {
        clicSimple(x, y);
    }

    bool load = true;

    if (nouvellePartie.boutonActive(x, y)) {
        load = false;
    }

    if (load) {
        charge(unitesAlliees, carte);
    }
    else {
        carte[304].flagHeros();
        carte[303].flagHeros();
        unitesAlliees.push_back(new Heros(5, 5, 304, 100));
        unitesAlliees.push_back(new Heros(10, 10, 303, 100));
    }

    carte[308].flagHeros();
    carte[312].flagHeros();
    unitesEnnemies.push_back(new Heros(6, 6, 308, 100));
    unitesEnnemies.push_back(new Heros(7, 7, 312, 100));
    // Remplissage de l'inventaire de la première unité qui est bien un héros
    unitesAlliees[0]->ramasse(new Objet("merde"));
    unitesAlliees[0]->ramasse(new Casque("casque"));
    unitesAlliees[0]->ramasse(new Objet("merde"));
    unitesAlliees[0]->ramasse(new Objet("merde"));
    unitesAlliees[0]->ramasse(new Arme("hache"));
    unitesAlliees[0]->ramasse(new Jambes("genouillères"));
    unitesAlliees[0]->ramasse(new Gants("gants de cuir"));
    unitesAlliees[0]->ramasse(new Objet("clafoutis"));
    unitesAlliees[0]->ramasse(new Objet("concombre"));
    unitesAlliees[0]->ramasse(new Objet("creme brulee"));
    unitesAlliees[0]->ramasse(new Objet("pain"));
    unitesAlliees[0]->ramasse(new Objet("confiture"));
    unitesAlliees[0]->ramasse(new Objet("fromage"));
    unitesAlliees[0]->ramasse(new Objet("zinzifruits"));
    unitesAlliees[0]->ramasse(new Objet("roche"));
    unitesAlliees[0]->ramasse(new Objet("cle"));
    unitesAlliees[0]->ramasse(new Objet("rat mort"));
    unitesAlliees[0]->ramasse(new Objet("boite a outils"));

    Inventaire i;
    i.ajoute(new Objet("merde"));
    i.ajoute(new Jambes("genouillères"));
    i.ajoute(new Casque("casque"));
    Inventaire j(i);


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


    Joueur allie(unitesAlliees);
    Joueur ennemi(unitesEnnemies);

    // Deplacement des unites
    bool quit = false;

    while (!quit) {
        allie.tourGestion(carte, unitesAlliees, boutonFinTour, boutonSauvegarde, boutonAction, boutonInventaire, quit);
        finJournee(unitesAlliees);
        if (quit) {
            break;
        }
        ennemi.tourGestion(carte, unitesEnnemies, boutonFinTour, boutonSauvegarde, boutonAction, boutonInventaire,
                           quit);
        finJournee(unitesEnnemies);
    }



    // Destruction des unités
    // EST CE QUE CA MARCHE VRAIMENT ????? FUITE ????
    for (int i = 0; i < unitesAlliees.size(); ++i) {
        //delete unitesAlliees[i];
        unitesAlliees[i] = 0;
    }
    Imagine::endGraphics();
    return 0;
}

