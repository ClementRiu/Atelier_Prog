#include "carte.h"
#include "unite.h"
#include "joueurs.h"


int main() {
    Imagine::openWindow(width, height);

    Ville *v = new Ville();
    v->ajoute(new Arme("Fusil", 1000));
    v->ajoute(new Arme("Epée", 40));
    v->ajoute(new Torse("Cotte de maille", 100));
    v->ajoute(new Bottes("Chaussures en tissu", 30));
    v->ajoute(new Objet("Potion faible", 10));
    v->ajoute(new Objet("Potion", 20));
    v->ajoute(new Objet("Potion forte", 40));

    Carte carte(v);

    // Définition des joueurs
    Joueur *allie = new Joueur(1);
    Joueur *ennemi = new Joueur(2);


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
        Heros *heros1 = new Heros(1, 100, 5, 5, 20, 120, allie);
        Heros *heros2 = new Heros(1, 100, 10, 10, 303, 100, allie);
        unitesAlliees.push_back(heros1);
        unitesAlliees.push_back(heros2);

        carte[20].placeUnite(unitesAlliees[0]);
        carte[303].placeUnite(unitesAlliees[1]);
    }
    Sbire *sbire1 = new Sbire(1, 100, 5, 5, 35, 105, 2);
    Sbire *sbire2 = new Sbire(1, 100, 5, 5, 20, 117, 2);
    Sbire *sbire3 = new Sbire(2, 100, 5, 5, 35, 115, 2);
    Sbire *sbire4 = new Sbire(2, 100, 5, 5, 20, 110, 2);

    unitesAlliees[0]->ajouteSbire(sbire1);
    unitesAlliees[1]->ajouteSbire(sbire2);

    Heros *heros3 = new Heros(2, 100, 6, 6, 308, 120, ennemi);
    Heros *heros4 = new Heros(2, 100, 7, 7, 312, 100, ennemi);

    unitesEnnemies.push_back(heros3);
    unitesEnnemies.push_back(heros4);
    carte[308].placeUnite(unitesEnnemies[0]);
    carte[312].placeUnite(unitesEnnemies[1]);

    unitesEnnemies[0]->ajouteSbire(sbire3);
    unitesEnnemies[1]->ajouteSbire(sbire4);


    // Remplissage de l'inventaire de la première unité qui est bien un héros
    unitesAlliees[0]->ramasse(new Objet("Gateau", 10));
    unitesAlliees[0]->ramasse(new Casque("casque", 10));
    unitesAlliees[0]->ramasse(new Objet("Gateau", 10));
    unitesAlliees[0]->ramasse(new Objet("Tarte", 10));
    unitesAlliees[0]->ramasse(new Arme("hache", 10));
    unitesAlliees[0]->ramasse(new Jambes("genouillères", 10));
    unitesAlliees[0]->ramasse(new Gants("gants de cuir", 10));
    unitesAlliees[0]->ramasse(new Objet("clafoutis", 10));
    unitesAlliees[0]->ramasse(new Objet("concombre", 10));
    unitesAlliees[0]->ramasse(new Objet("creme brulee", 10));
    unitesAlliees[0]->ramasse(new Objet("pain", 10));
    unitesAlliees[0]->ramasse(new Objet("confiture", 10));
    unitesAlliees[0]->ramasse(new Objet("fromage", 10));
    unitesAlliees[0]->ramasse(new Objet("zinzifruits", 10));
    unitesAlliees[0]->ramasse(new Objet("roche", 10));
    unitesAlliees[0]->ramasse(new Objet("cle", 10));
    unitesAlliees[0]->ramasse(new Objet("rat mort", 10));
    unitesAlliees[0]->ramasse(new Objet("boite a outils", 10));

    unitesEnnemies[0]->ramasse(new Arme("Arc", 20));
    unitesEnnemies[0]->ramasse(new Arme("Epée", 20));
    unitesEnnemies[0]->ramasse(new Arme("Lance", 20));
    unitesEnnemies[0]->ramasse(new Bottes("Bottes de cuir", 20));
    unitesEnnemies[0]->ramasse(new Gants("Gants de cuir", 20));
    unitesEnnemies[0]->ramasse(new Casque("Casque de fer", 20));
    unitesEnnemies[0]->ramasse(new Torse("Plastron de cuir", 20));
    unitesEnnemies[0]->ramasse(new Anneau("Anneau simple", 20));
    unitesEnnemies[0]->ramasse(new Objet("Potion", 20));

    unitesEnnemies[1]->ramasse(new Arme("Arc composé", 40));
    unitesEnnemies[1]->ramasse(new Arme("Epée", 20));
    unitesEnnemies[1]->ramasse(new Arme("Lance cassée", 0));
    unitesEnnemies[1]->ramasse(new Bottes("Bottes de cuir renforcées", 25));
    unitesEnnemies[1]->ramasse(new Bottes("Bottes de cuir", 20));
    unitesEnnemies[1]->ramasse(new Gants("Gants de cuir", 20));
    unitesEnnemies[1]->ramasse(new Casque("Casque de fer doré", 50));
    unitesEnnemies[1]->ramasse(new Torse("Cotte de mailles", 37));
    unitesEnnemies[1]->ramasse(new Anneau("Anneau magique", 80));
    unitesEnnemies[1]->ramasse(new Objet("Potion faible", 10));


    unitesAlliees[1]->ramasse(new Arme("Arc composé cassé", 5));
    unitesAlliees[1]->ramasse(new Arme("Epée double", 40));
    unitesAlliees[1]->ramasse(new Arme("Lance cassée", 0));
    unitesAlliees[1]->ramasse(new Bottes("Bottes de cuir renforcées avec des pics", 42));
    unitesAlliees[1]->ramasse(new Bottes("Bottes de cuir", 20));
    unitesAlliees[1]->ramasse(new Gants("Gants de cuir troués", 11));
    unitesAlliees[1]->ramasse(new Casque("Casque de fer", 20));
    unitesAlliees[1]->ramasse(new Torse("Cotte de mailles", 37));
    unitesAlliees[1]->ramasse(new Anneau("Anneau magique", 100));
    unitesAlliees[1]->ramasse(new Objet("Potion faible", 10));

    // Initialisation d'une attaque
    std::vector<Imagine::Coords<2> > zoneInfl;
    zoneInfl.push_back(portee10);
    zoneInfl.push_back(portee_10);
    zoneInfl.push_back(portee01);
    zoneInfl.push_back(portee0_1);

    std::vector<Imagine::Coords<2> > zoneInfl2;
    zoneInfl2.push_back(portee20);
    zoneInfl2.push_back(portee_20);
    zoneInfl2.push_back(portee02);
    zoneInfl2.push_back(portee0_2);

    std::vector<Imagine::Coords<2> > zoneInfl3;
    zoneInfl3.push_back(portee10);
    zoneInfl3.push_back(portee_10);
    zoneInfl3.push_back(portee20);
    zoneInfl3.push_back(portee_20);
    zoneInfl3.push_back(portee30);
    zoneInfl3.push_back(portee_30);


    Attaque attq1(zoneInfl, 30);
    Attaque attq2(zoneInfl2, 40);
    Attaque attq3(zoneInfl3, 50);
    unitesAlliees[0]->setAttaque(attq1);
    unitesAlliees[1]->setAttaque(attq2);


    unitesEnnemies[0]->setAttaque(attq3);
    unitesEnnemies[1]->setAttaque(attq3);


    carte.affiche();

    // Creation et affichage des boutons
    Bouton boutonSauvegarde(ZoneBoutonSauvegarde, Imagine::BLUE, "Save & Quit");
    Bouton boutonFinTour(ZoneBoutonFinTour, Imagine::BLACK, "End turn");
    Bouton boutonAction(ZoneBoutonAction, Imagine::BLACK, "Action");
    Bouton boutonInventaire(ZoneBoutonInventaire, Imagine::BLACK, "Inventaire");
    boutonSauvegarde.affiche();
    boutonFinTour.affiche();


    allie->ajouteUnite(unitesAlliees);
    ennemi->ajouteUnite(unitesEnnemies);

    // Deplacement des unites
    bool quit = false;

    int nbTour = 1;

    while (!quit) {
        //Clement à toi de jouer

        std::cout << "Tour joueur 1" << std::endl;
        allie->tourGestion(carte, boutonFinTour, boutonSauvegarde, boutonAction, boutonInventaire, quit, nbTour);
        if (quit) {
            break;
        }
        if (allie->aPerdu()) {
            break;
        }
        std::cout << " Tour joueur 2" << std::endl;
        ennemi->tourGestion(carte, boutonFinTour, boutonSauvegarde, boutonAction, boutonInventaire,
                            quit, nbTour);
        if (ennemi->aPerdu()) {
            break;
        }
        nbTour += 1;
    }

    if (allie->aPerdu()) {
        Imagine::fillRect(0, 0, width, height, Imagine::WHITE);
        Imagine::drawString(width / 2, height / 2, "Le joueur 1 a gagné", Imagine::BLUE);
    }


    if (ennemi->aPerdu()) {
        Imagine::fillRect(0, 0, width, height, Imagine::WHITE);
        Imagine::drawString(width / 2, height / 2, "Le joueur 2 a gagné", Imagine::RED);
    }



    // Destruction des unités
    // EST CE QUE CA MARCHE VRAIMENT ????? FUITE ????
    for (int i = 0; i < unitesAlliees.size(); ++i) {
        //delete unitesAlliees[i];
        unitesAlliees[i] = 0;
    }
    //Imagine::endGraphics();
    return 0;
}

