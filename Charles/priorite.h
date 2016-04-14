#pragma once
#include <vector>
#include <assert.h>

class CaseDist {
    int num_case;
    float nb_dep;
public:
    // Constructeur de caseDist
    CaseDist(int num, float dep);
    // Accesseur au numero de la case
    int GetNum();
    // Accesseur au nombre de deplacements restants
    float GetDep();
    // Operateure inferieur ou egal sur la classe
    bool operator<(CaseDist c) const;
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
