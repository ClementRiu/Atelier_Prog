#include "boutons.h"

/*
Bouton::Bouton(int xmin, int ymin, int xmax, int ymax, Imagine::Color c, std::string nom) {
    zoneDeDelimitation[0] = xmin;
    zoneDeDelimitation[1] = ymin;
    zoneDeDelimitation[2] = xmax;
    zoneDeDelimitation[3] = ymax;
    image = c;
    nomBouton = nom;
    taillePolice = 0;
}


Bouton::Bouton(const int zone[4], Imagine::Color c, std::string nom) {
    zoneDeDelimitation[0] = zone[0];
    zoneDeDelimitation[1] = zone[1];
    zoneDeDelimitation[2] = zone[2];
    zoneDeDelimitation[3] = zone[3];
    image = c;
    nomBouton = nom;
    taillePolice = 0;
}


int Bouton::largeur() {
    return zoneDeDelimitation[2] - zoneDeDelimitation[0];
}


int Bouton::hauteur() {
    return zoneDeDelimitation[3] - zoneDeDelimitation[1];
}


// A changer
void Bouton::affiche(int decalementVertical) {
    int taille = std::min(int(1.2 * this->largeur() / nomBouton.size()), this->hauteur());
    Imagine::fillRect(zoneDeDelimitation[0], zoneDeDelimitation[1] + decalementVertical, this->largeur(),
                      this->hauteur(), image);
    Imagine::drawString(zoneDeDelimitation[0], zoneDeDelimitation[1] + taille + decalementVertical,
                        nomBouton, Imagine::WHITE, taille);
}


bool Bouton::boutonActive(int x, int y, int decalementVertical) {
    if (x > zoneDeDelimitation[0] && y > zoneDeDelimitation[1] + decalementVertical &&
        x < zoneDeDelimitation[2] && y < zoneDeDelimitation[3] + decalementVertical) {
        return true;
    }
    return false;
}


bool Bouton::boutonVide() {
    return (this->largeur() == 0 || this->hauteur() == 0);
}


void Bouton::setNom(std::string nom) {
    nomBouton = nom;
}
*/