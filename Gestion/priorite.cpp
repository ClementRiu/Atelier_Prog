#include "priorite.h"


CaseDist::CaseDist(int num, float dep){
    num_case = num;
    PDep = dep;
}


int CaseDist::getNum(){
    return num_case;
}


bool CaseDist::operator<(CaseDist c) const{
    return (PDep < c.PDep);
}


float CaseDist::getDep(){
    return PDep;
}


FilePriorite::FilePriorite(){
    v.push_back(CaseDist(0,0));
}


bool FilePriorite::empty(){
    if (!v.empty()){
        CaseDist a = v.back();
        v.pop_back();
        if (v.empty()){
            v.push_back(a);
            return true;
        }
        v.push_back(a);
        return false;
    }
    else{
        v.push_back(CaseDist(0, 0));
        return true;
    }
}

void FilePriorite::push(CaseDist d) {
    v.push_back(d);
    int i = v.size() - 1;
    while (!(v[i] < v[i/2])  && i > 1){
        std::swap(v[i], v[i/2]);
        i = i / 2;
    }
}


CaseDist FilePriorite::pop() {
    assert(v.size() > 1 && "file vide");
    if (!v.empty()){
        int i = 1;
        std::swap(v[i], v[v.size() - 1]);
        while ((2 * i + 1< v.size() - 1 && (v[i] < v[2 * i + 1] || v[i] < v[2 * i])) || (2 * i < v.size() - 1 && v[i]<v[2 * i])){
            if (v[2 * i + 1] < v[2 * i] || 2 * i + 1 == v.size() - 1){
                std::swap(v[i], v[2 * i]);
                i = 2 * i;
            }
            else{
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
