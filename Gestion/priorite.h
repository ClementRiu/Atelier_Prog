#pragma once

#include <vector>
#include <assert.h>

class CaseDist {
    int num_case;
    float PDep;
    // Ce vector va servir à stocker le chemin utilisé pour arriver à une case. On en a besoin pour afficher les chemins
    std::vector<int> chemin;
public:
    // Constructeur de caseDist
    CaseDist(int num, float dep);

    // Constructeur de caseDist avec un vecteur prdéfini
    CaseDist(int num, float dep, std::vector<int> way);

    // Accesseur au numero de la case
    int getNum();

    // Accesseur au nombre de deplacements restants
    float getDep();

    // Operateur inferieur ou egal sur la classe
    bool operator<(CaseDist c) const;

    // Pour récupérer le chemin de la case
    std::vector<int> getChemin();
};

class FilePriorite {
    std::vector<CaseDist> v;
public:
    // Constructeur de la file de priorite
    FilePriorite();

    // Methode pour inserer un élément dans la file
    void push(CaseDist d);

    // Methode pour retourner le premier element de la file
    CaseDist pop();

    // Methode pour determiner si la file est vide
    bool empty();
};
