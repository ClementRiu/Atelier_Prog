#include "carte.h"
#include "unite.h"
#include "joueurs.h"


int main() {
    Imagine::openWindow(width, height);

    Ville *v = new Ville();
    v->ajoute(new Objet("essai"));
    v->ajoute(new Objet("poup"));

    Carte carte(v);

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
        unitesAlliees.push_back(new Heros(1, 5, 5, 20, 120));
        unitesAlliees.push_back(new Heros(1, 10, 10, 303, 100));
        carte[20].flagHeros(unitesAlliees[0]);
        carte[303].flagHeros(unitesAlliees[1]);
    }

    unitesEnnemies.push_back(new Heros(2, 6, 6, 308, 120));
    unitesEnnemies.push_back(new Heros(2, 7, 7, 312, 100));
    carte[308].flagHeros(unitesEnnemies[0]);
    carte[312].flagHeros(unitesEnnemies[1]);
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


    carte.affiche();

    // Creation et affichage des boutons
    Bouton boutonSauvegarde(ZoneBoutonSauvegarde, Imagine::BLUE, "Save & Quit");
    Bouton boutonFinTour(ZoneBoutonFinTour, Imagine::BLACK, "End turn");
    Bouton boutonAction(ZoneBoutonAction, Imagine::BLACK, "Action");
    Bouton boutonInventaire(ZoneBoutonInventaire, Imagine::BLACK, "Inventaire");
    boutonSauvegarde.affiche();
    boutonFinTour.affiche();


    Joueur allie(1, unitesAlliees);
    Joueur ennemi(2, unitesEnnemies);

    // Deplacement des unites
    bool quit = false;

    int nbTour = 1;

    while (!quit) {
        //Clement à toi de jouer
        //affiche(tour)
        std::cout << "Tour joueur 1" << std::endl;
        allie.tourGestion(carte, boutonFinTour, boutonSauvegarde, boutonAction, boutonInventaire, quit);
        if (quit) {
            break;
        }
        std::cout << " Tour joueur 2" << std::endl;
        ennemi.tourGestion(carte, boutonFinTour, boutonSauvegarde, boutonAction, boutonInventaire,
                           quit);

        nbTour += 1;
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

