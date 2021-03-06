/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Heroes of Ponts&Chaussées                                                                                           *
 *                                                                                                                     *
 * Jeu développé dans le cadre du module Atelier de Programmation de première année de l'École des Ponts               *
 *                                                                                                                     *
 * AUTEURS :                                                                                                           *
 *      Charles    AUGUSTE                                                                                             *
 *      Nathanaël  GROSS-HUMBERT                                                                                       *
 *      Clément    RIU                                                                                                 *
 *      Anne       SPITZ                                                                                               *
 *                                                                                                                     *
 * Rendu le 27 Mai 2016                                                                                                *
 *                                                                                                                     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/

#include <sstream>
#include "outils.h"

void sauvegarde(std::vector<Unite *> unites) {
    std::ofstream fichier(srcPath("../Sauvegardes/Sauvegarde1/sauvegarde1.txt"), std::ios::out | std::ios::trunc);
    if (fichier) {
        fichier << unites.size() << std::endl;
        for (int i = 0; i < unites.size(); i++) {
            fichier << unites[i]->getID() << std::endl;
            fichier << unites[i]->getCase() << std::endl;
            fichier << unites[i]->getDep() << std::endl;
            fichier << unites[i]->getDepMax() << std::endl;
            fichier << unites[i]->getInit() << std::endl;
        }
        fichier.close();
    }
    else {
        std::cout << "Erreur à l'ouverture !" << std::endl;
    }
}


void charge(std::vector<Unite *> &unites, Carte &carte) {
    std::ifstream fichier(srcPath("../Sauvegardes/Sauvegarde1/sauvegarde1.txt"), std::ios::in);
    if (fichier) {
        std::string ligne;
        std::getline(fichier, ligne);
        int T = atoi(ligne.c_str());
        std::cout << T;

        for (int i = 0; i < T; i++) {
            std::getline(fichier, ligne);
            int ID = atoi(ligne.c_str());
            std::getline(fichier, ligne);
            int num = atoi(ligne.c_str());
            std::getline(fichier, ligne);
            float dep = atoi(ligne.c_str());
            std::getline(fichier, ligne);
            float depMax = atoi(ligne.c_str());
            std::cout << depMax << std::endl;
            std::getline(fichier, ligne);
            float init = atoi(ligne.c_str());
            //PVmax à 100 arbitraire, à modifier
            unites.push_back(new Unite(ID, 100, dep, depMax, num, init));
            carte[num].placeUnite(unites[unites.size()-1]);
        }
        fichier.close();
    }
    else {
        std::cerr << "Erreur à l'ouverture !" << std::endl;
    }
}

std::string intToString(int a){
    std::string result;
    std::ostringstream convert;
    convert << a;
    result = convert.str();

    return result;
}


void clic(int &x, int &y, Carte &carte, std::vector<std::vector<int> > differentsChemins, int numcase) {
    Imagine::enableMouseTracking(true);
    Imagine::Event e;
    x = -1;
    y = -1;

    do {
        getEvent(0, e);
        if (e.type == Imagine::EVT_BUT_ON) {
            x = e.pix[0];
            y = e.pix[1];
        }
        if (e.type == Imagine::EVT_MOTION) {
            // On affiche et on efface les chemins qui correspondent à l'emplacement de la souris
            afficheChemins(x, y, carte, differentsChemins, numcase);
            x = e.pix[0];
            y = e.pix[1];
            // On affiche la case que l'on survole
            afficheCaseSurvole(x, y, carte);
            afficheChemins(x, y, carte, differentsChemins, numcase);
        }
    } while (e.type != Imagine::EVT_BUT_OFF);
    Imagine::enableMouseTracking(false);
}


void clic(int &x, int &y, Carte &carte) {
    std::vector<std::vector<int> > differentsChemins;
    clic(x, y, carte, differentsChemins, 0);
}


int clicSimple(int &x, int &y) {
    Imagine::Event e;
    do {
        getEvent(0, e);
        if (e.type == Imagine::EVT_BUT_ON) {
            x = e.pix[0];
            y = e.pix[1];
        }
    } while (e.type != Imagine::EVT_BUT_OFF);
    return e.button;
}


void survole(int &x, int &y) {
    Imagine::Event e;
    getEvent(0, e);
    x = e.pix[0];
    y = e.pix[1];
}


void afficheCaseSurvole(int x, int y, Carte &carte) {
    // A MODIFIER
    Imagine::fillRect(LargGauche + Separation + NbCase * Taille, LargDroite + 10, LargDroite, LargDroite +70,
                      Imagine::WHITE);
    if (numeroCase(x, y) != -1) {
        Imagine::fillRect(LargGauche + Separation + NbCase * Taille, LargDroite + 10, Taille, Taille,
                          carte[numeroCase(x, y)].getImage());
        Imagine::drawString(LargGauche + Separation + NbCase * Taille, LargDroite + 30 + Taille,
                            carte[numeroCase(x, y)].getDescription(), Imagine::BLACK, 7);
        if (carte[numeroCase(x, y)].getOccupe()) {
            int PVaffiche = int(carte[numeroCase(x, y)].getPointeurUnite()->getPV());

            std::string result = intToString(PVaffiche);

            Imagine::drawString(LargGauche + Separation + NbCase * Taille, LargDroite + 50 + Taille,
                                "Unité", Imagine::BLACK, 9);
            Imagine::drawString(LargGauche + Separation + NbCase * Taille, LargDroite + 60 + Taille,
                                "survolée :", Imagine::BLACK, 9);
            Imagine::drawString(LargGauche + Separation + NbCase * Taille, LargDroite + 75 + Taille,
                                "PV = "+ result, Imagine::BLACK, 10);
        }
    }
}


void afficheChemins(int x, int y, Carte &carte, std::vector<std::vector<int> > differentsChemins, int numcase) {
    if (numeroCase(x, y) != -1) {
        // L'entier suivant correspont à la case la plus proche de (x,y) qui est en brillance. == -1 si aucune.
        int caseProche = carte[numeroCase(x, y)].plusProcheVoisineBrillante(x, y, carte, numeroCase(x, y));
        int num;
        // La dernière condition signifie que l'on est pas en train de regarder la position du Heros
        if (carte[numeroCase(x, y)].Brillance() ||
            (carte[numeroCase(x, y)].getOccupe() && caseProche != -1 &&
             numeroCase(x, y) != numcase)) {
            // On met dans num le numéro de la case où l'on veut aller
            if (carte[numeroCase(x, y)].Brillance()) {
                num = numeroCase(x, y);
            }
            else {
                num = caseProche;
            }
            // On met en place et on affiche le chemin
            for (int i = 0; i < differentsChemins.size(); ++i) {
                if (differentsChemins[i][differentsChemins[i].size() - 1] == num) {
                    for (int j = 0; j < differentsChemins[i].size(); ++j) {
                        carte[differentsChemins[i][j]].setChemin();
                        carte[differentsChemins[i][j]].affiche();
                    }
                }
            }
        }
    }
}


void afficheNombreTours(int tour){
    Imagine::fillRect(LargGauche + Separation + NbCase * Taille, LargDroite + 220 + Taille, LargDroite, LargDroite/5, Imagine::WHITE);

    std::string result=intToString(tour);

    Imagine::drawString(LargGauche + Separation + NbCase * Taille, LargDroite + 230 + Taille,
                        result+"e tour", Imagine::BLACK, 10);
}

void afficheTourJoueur(int idJoueur) {
    Imagine::fillRect(LargGauche + Separation + NbCase * Taille, LargDroite + 230 + Taille, LargDroite, 3 * LargDroite / 5,
                      Imagine::WHITE);

    if (idJoueur == 1) {
        Imagine::drawString(LargGauche + Separation + NbCase * Taille, LargDroite + 240 + Taille,
                            "Joueur", Imagine::BLUE, 10);
        Imagine::drawString(LargGauche + Separation + NbCase * Taille, LargDroite + 250 + Taille,
                            "Bleu", Imagine::BLUE, 10);
    }
    if (idJoueur == 2){
        Imagine::drawString(LargGauche + Separation + NbCase * Taille, LargDroite + 240 + Taille,
                            "Joueur", Imagine::RED, 10);
        Imagine::drawString(LargGauche + Separation + NbCase * Taille, LargDroite + 250 + Taille,
                            "Rouge", Imagine::RED, 10);
    }
}

#if 0
void choisir(int &choix, int &x, int &y) {
    choix = -1;
    x = -1;
    y = -1;
    int tailleEcriture = 9;
    // A MODIFIER
    Imagine::drawString(NbCase * Taille + Separation, LargDroite + tailleEcriture + 1, "0 : deplacement",
                        Imagine::BLACK, tailleEcriture);
    Imagine::drawString(NbCase * Taille + Separation, LargDroite + 2 * (tailleEcriture + 1), "1 : attaque",
                        Imagine::BLACK, tailleEcriture);
    Imagine::drawString(NbCase * Taille + Separation, LargDroite + 3 * (tailleEcriture + 1), "ESP: Fin de tour",
                        Imagine::BLACK, tailleEcriture);
    Imagine::Event e;
    do {
        getEvent(0, e);
        if (e.type == Imagine::EVT_KEY_ON) {
            choix = e.key;
        }
        if (e.type == Imagine::EVT_BUT_ON) {
            x = e.pix[0];
            y = e.pix[1];
        }
    } while (e.type != Imagine::EVT_KEY_OFF && e.type != Imagine::EVT_BUT_OFF);
    // A MODIFIER
    Imagine::fillRect(NbCase * Taille + Separation, LargDroite, LargDroite, 2 * (tailleEcriture + 2), Imagine::WHITE);
}
#endif
