#pragma once

//L'inclusion de 'outilsaff.h' donne accès à ces .h, attention ! Permet d'afficher des cases, la map et...

#include "constante.h"
#include "case_graph.h"
#include "bouton_graph.h"

//Cette fonction trace l'interface graphique.
void interface(Bouton fin_tour, Bouton menu);

//Renvoi la couleur pour la 'mmap' en fonction du type de la case.
Imagine::Color couleur_case(std::string nom);


