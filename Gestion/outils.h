#ifndef OUTILS_H
#define OUTILS_H

#include <iostream>
#include "unite.h"

void sauvegarde(std::vector<Unite*> unites);
void charge(std::vector<Unite*> & unites, Carte& carte);

// Fonction renvoyant en référence dans x et y la position d'un clic et affichant les cases survolees
void clic(int &x, int &y, Carte& carte);

// Fonction renvoyant en référence dans x et y la position d'un clic
int clicSimple(int &x, int &y);

// Fonction pour choisir d'attaquer ou se deplacer (ou autre plus tard...). choix devient 0 pour le deplacement et 1 pour l'attaque
void choisir(int &choix, int &x, int &y);

// Renvoie les coordonnees de la case survolee
void survole(int &x, int &y);

// Affiche l'endroit survole par la souris #Clement
void afficheCaseSurvole(int x, int y, Carte& carte);

// Affiche le chemin pour le Heros
void afficheChemins(int x, int y, Carte& carte, std::vector< std::vector<int> > differentsChemins, int numcase);


#endif
