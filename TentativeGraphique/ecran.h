#pragma once

#include "constante.h"
#include "bouton_graph.h"

//Fonction qui affiche l'écran d'accueil du jeu et renvoie 1 si "Nouvelle Partie" est cliqué, 2 si "Charger Partie" est cliqué et 3 si "Quitter le Jeu" est cliqué.
int affiche_accueil();

//Fonction qui affiche au milieu de l'écran un menu et renvoie 1 si "Retour au Jeu" est cliqué, 2 si "Sauvegarder" est cliqué et 3 si "Retour à l'Accueil" est cliqué.
int affiche_menu();

void affiche_chargement();