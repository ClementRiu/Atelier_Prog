#include "ecran.h"

//Fonction qui affiche l'écran d'accueil du jeu et renvoie 1 si "Nouvelle Partie" est cliqué, 2 si "Charger Partie" est cliqué et 3 si "Quitter le Jeu" est cliqué.
int affiche_accueil() {
    Bouton nouvelle_partie_graph(200, 160, 520, 190, std::string("Nouvelle Partie"), 0);
    Bouton charger_partie_graph(200, 240, 520, 270, std::string("Charger Partie"), 0);
    Bouton quitter_jeu_graph(200, 320, 520, 350, std::string("Quitter le Jeu"), 0);
    Imagine::display(parchemin_acc, 0, 0);
    nouvelle_partie_graph.affiche_graph();
    charger_partie_graph.affiche_graph();
    quitter_jeu_graph.affiche_graph();
    int x = -1;
    int y = -1;
    while (!nouvelle_partie_graph.boutonActive(x, y) && !charger_partie_graph.boutonActive(x, y) &&
           !quitter_jeu_graph.boutonActive(x, y)) {
        Imagine::getMouse(x, y);
    }
    if (nouvelle_partie_graph.boutonActive(x, y)) {
        return 1;
    }
    if (charger_partie_graph.boutonActive(x, y)) {
        return 2;
    }
    if (quitter_jeu_graph.boutonActive(x, y)) {
        return 3;
    }
}

//Fonction qui affiche au milieu de l'écran un menu et renvoie 1 si "Retour au Jeu" est cliqué, 2 si "Sauvegarder" est cliqué et 3 si "Retour à l'Accueil" est cliqué.
int affiche_menu(){
    Bouton retour_jeu_graph(200, 160, 520, 190, std::string("Retour au Jeu"), 0);
    Bouton sauvegarder_graph(200, 240, 520, 270, std::string("Sauvegarder"), 0);
    Bouton retour_accueil_graph(200, 320, 520, 350, std::string("Retour à l'Acceuil"), 0);
    Imagine::display(parchemin_menu, 115, 108);
    retour_jeu_graph.affiche_graph();
    sauvegarder_graph.affiche_graph();
    retour_accueil_graph.affiche_graph();
    int x = -1;
    int y = -1;
    while (!retour_jeu_graph.boutonActive(x, y) && !sauvegarder_graph.boutonActive(x, y) &&
           !retour_accueil_graph.boutonActive(x, y)) {
        Imagine::getMouse(x, y);
    }
    if (retour_jeu_graph.boutonActive(x, y)) {
        return 1;
    }
    if (sauvegarder_graph.boutonActive(x, y)) {
        return 2;
    }
    if (retour_accueil_graph.boutonActive(x, y)) {
        return 3;
    }
}

void affiche_chargement() {
    Imagine::display(fond_ecran, 0, 0);
    Imagine::drawString(widthscreen / 2 - 11 * 6 * 1.2, heightscreen / 2 - 6, "Chargement en cours...", gris);
}