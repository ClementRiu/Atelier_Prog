#pragma once

#include "constante.h"
#include "case_graph.h"

class CarteduMonde {
private:
    Imagine::Coords<2> pos_centre;    // Position du point centrale de la map.
    Imagine::Image<Case_Graph> listecase; // Image contenant la liste des cases de la map.

public:
    //Constructeur par défaut.
    CarteduMonde();

    //Assesseur en lecture de l'attribut pos_centre.
    void get_pos_centre(Imagine::Coords<2> &pos);

    //Méthode qui affiche la carte dans le 'world' et la minimap sur la 'mmap'.
    void affiche();

    //Méthode qui décale l'affichage selon la direction dir voulue.
    void deplace_clavier(int dir);

    //Méthode qui place pos_centre au coordonnée voulue et réaffiche le 'world' et la 'mmap'. Prend des Coords en argument pour déterminer la position voulue.
    void deplace_souris(Imagine::Coords<2> pos_voulue);

    //Méthode qui place pos_centre au coordonnée voulue et réaffiche le 'world' et la 'mmap'. Prend des int en argument pour déterminer la position voulue.
    void deplace_souris(int x, int y);
};