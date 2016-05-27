#ifndef OUTILS_H
#define OUTILS_H

#include <iostream>
#include "unite.h"
#include "constante.h"

void sauvegarde(std::vector<Unite*> unites);
void charge(std::vector<Unite*> & unites, CarteduMonde carte);

// Fonction renvoyant en référence dans x et y la position d'un clic et affichant les cases survolees
void clic(int &x, int &y, CarteduMonde& carte);

// Fonction renvoyant en référence dans x et y la position d'un clic
void clicSimple(int &x, int &y);

// Fonction pour choisir d'attaquer ou se deplacer (ou autre plus tard...). choix devient 0 pour le deplacement et 1 pour l'attaque
void choisir(int &choix, int &x, int &y);

// Renvoie les coordonnees de la case survolee
void survole(int &x, int &y);

// Affiche l'endroit survole par la souris #Clement
void afficheCaseSurvole(int x, int y, CarteduMonde& carte);

// Affiche le chemin pour le Heros
void afficheChemins(int x, int y, CarteduMonde& carte, std::vector< std::vector<int> > differentsChemins, int numcase);


#endif