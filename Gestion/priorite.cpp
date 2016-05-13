#include "priorite.h"

#include <iostream>


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

FilePriorite::FilePriorite() {
    v.push_back(CaseDist(0, 0));
}


bool FilePriorite::empty() {
    if (!v.empty()) {
        CaseDist a = v.back();
        v.pop_back();
        if (v.empty()) {
            v.push_back(a);
            return true;
        }
        v.push_back(a);
        return false;
    }
    else {
        v.push_back(CaseDist(0, 0));
        return true;
    }
}

void FilePriorite::push(CaseDist d) {
    v.push_back(d);
    int i = v.size() - 1;
    while (!(v[i] < v[i / 2]) && i > 1) {
        std::swap(v[i], v[i / 2]);
        i = i / 2;
    }
}


CaseDist FilePriorite::pop() {
    assert(v.size() > 1 && "file vide");
    if (!v.empty()) {
        int i = 1;
        std::swap(v[i], v[v.size() - 1]);
        while ((2 * i + 1 < v.size() - 1 && (v[i] < v[2 * i + 1] || v[i] < v[2 * i])) ||
               (2 * i < v.size() - 1 && v[i] < v[2 * i])) {
            if (v[2 * i + 1] < v[2 * i] || 2 * i + 1 == v.size() - 1) {
                std::swap(v[i], v[2 * i]);
                i = 2 * i;
            }
            else {
                std::swap(v[i], v[2 * i + 1]);
                i = 2 * i + 1;
            }
        }
    }
    CaseDist a = v.back();
    v.pop_back();
    v.empty();
    return a;
}


FileUnite::FileUnite() {
}


bool FileUnite::empty() {
    if (!v.empty()) {
        Unite* a = v.back();
        v.pop_back();
        if (v.empty()) {
            v.push_back(a);
            return true;
        }
        v.push_back(a);
        return false;
    }
    else {
        //v.push_back(Unite(0, 0));
        return true;
    }
}

void FileUnite::push(Unite* d, float prio) {
    v.push_back(d);
    priorite.push_back(prio);
    int i = v.size() - 1;

    while (priorite[i] >= priorite[i / 2] && i >= 1) {
        std::swap(v[i], v[i / 2]);
        std::swap(priorite[i], priorite[i / 2]);
        i = i / 2;
    }
}


Unite* FileUnite::pop() {
    assert(v.size() > 1 && "file vide");

    if (!v.empty()) {
        int i = 1;
        std::swap(v[i], v[v.size() - 1]);
        std::swap(priorite[i], priorite[priorite.size() - 1]);

        while ((2 * i + 1 < v.size() - 1 && (priorite[i] < priorite[2 * i + 1] || priorite[i] < priorite[2 * i])) ||
               (2 * i < v.size() - 1 && priorite[i] < priorite[2 * i])) {
            if (priorite[2 * i + 1] < priorite[2 * i] || 2 * i + 1 == v.size() - 1) {
                std::swap(v[i], v[2 * i]);
                std::swap(priorite[i], priorite[2 * i]);
                i = 2 * i;
            }
            else {
                std::swap(v[i], v[2 * i + 1]);
                std::swap(priorite[i], priorite[2 * i + 1]);
                i = 2 * i + 1;
            }
        }
    }
    Unite* a = v.back();
    v.pop_back();
    priorite.pop_back();
    v.empty();
    return a;
}
