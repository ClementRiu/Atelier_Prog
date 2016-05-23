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
    int getNum() const;

    // Accesseur au nombre de deplacements restants
    float getDep() const;

    // Operateur inferieur ou egal sur la classe
    bool operator<(CaseDist c) const;

    // Pour récupérer le chemin de la case
    std::vector<int> getChemin() const;
};


template<typename T>
class FilePriorite {
    std::vector<T*> v;
public:
    // Constructeur de la file de priorite
    FilePriorite();

    // Methode pour inserer un élément dans la file
    void push(T* d);

    // Echange les éléments i et j de v
    void echange(int i, int j);

    // Methode pour retourner le premier element de la file
    T* pop();

    // Methode pour determiner si la file est vide
    bool empty();

    //renvoie la taille de la file
    int size() const;
};

