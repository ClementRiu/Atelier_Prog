#include "priorite.h"
#include "unite.h"


CaseDist::CaseDist(int num, float dep) {
    num_case = num;
    PDep = dep;
}


CaseDist::CaseDist(int num, float dep, std::vector<int> way) {
    num_case = num;
    PDep = dep;
    chemin = way;
}


int CaseDist::getNum() {
    return num_case;
}


bool CaseDist::operator<(CaseDist c) const {
    return (PDep < c.PDep);
}


float CaseDist::getDep() {
    return PDep;
}


std::vector<int> CaseDist::getChemin() {
    return chemin;
}


template <typename T>
FilePriorite<T>::FilePriorite() {
    v.push_back(new T(0,0));
}

template <typename T>
bool FilePriorite<T>::empty() {
    if (!v.empty()) {
        T* a = v.back();
        v.pop_back();
        if (v.empty()) {
            v.push_back(a);
            return true;
        }
        v.push_back(a);
        return false;
    }
    else {
        v.push_back(new T(0,0));
        return true;
    }
}

template <typename T>
void FilePriorite<T>::push(T* d) {
    v.push_back(d);
    int i = v.size() - 1;
    while (!((*v[i]) < (*v[i / 2])) && i > 1) {
        this->echange(i, i / 2);
        i = i / 2;
    }
}


template <typename T>
void FilePriorite<T>::echange(int i, int j) {
    T* a = v[i];
    v[i] = v[j];
    v[j] = a;
}


template <typename T>
T* FilePriorite< T >::pop() {
    assert(v.size() > 1 && "file vide");
    if (!v.empty()) {
        int i = 1;
        this->echange(i, v.size() - 1);
        while ((2 * i + 1 < v.size() - 1 && (*v[i] < *v[2 * i + 1] || *v[i] < *v[2 * i])) ||
               (2 * i < v.size() - 1 && *v[i] < *v[2 * i])) {
            if (*v[2 * i + 1] < *v[2 * i] || 2 * i + 1 == v.size() - 1) {
                this->echange(i, 2 * i);
                i = 2 * i;
            }
            else {
                this->echange(i, 2 * i + 1);
                i = 2 * i + 1;
            }
        }
    }
    T* a = v.back();
    v.pop_back();
    v.empty();
    return a;
}

template class FilePriorite<CaseDist>;
template class FilePriorite<Unite>;

