#include "carte.h"
#include "unite.h"

TypeCase::TypeCase(float dep, std::string desc, Imagine::Color img) {
    PDep = dep;
    description = desc;
    image = img;
}


TypeCase::TypeCase() {
}


Imagine::Color TypeCase::Image() {
    return image;
}


float TypeCase::NbDep() const {
    return PDep;
}


std::string TypeCase::Desctiption(){
    return description;
}


Case::Case(int x1, int y1, TypeCase tc) {
    x = x1;
    y = y1;
    taille = Taille;
    occupe = false;
    brillance = false;
    type = tc;
}


Case::Case() {
}


void Case::flagHeros() {
    occupe = !occupe;
}


bool Case::getOccupe() const {
    return occupe;
}


void Case::deplaceHeros(Unite &h, Case &c) {
    if (!c.getOccupe()) {
        this->flagHeros();
        c.flagHeros();
        this->affiche();
        c.affiche();
        h.setCase(numeroCase(c.x, c.y));
    }
}


void Case::brillanceOnOff(bool flag) {
    brillance = flag;
    this->affiche();
}


void Case::affiche() {
    Imagine::fillRect(x, y, Taille - 1, Taille - 1, type.Image());
    if (brillance) {
        Imagine::drawRect(x, y, Taille - 2, Taille - 2, Imagine::BLACK);
    }
    // Mini map
    int taillemax = LargDroite / NbCase;
    Imagine::fillRect(x * taillemax / Taille + Taille * NbCase + Separation, y * taillemax / Taille, taillemax,
                      taillemax, type.Image());
    if (occupe) {
        Imagine::fillRect(x + Taille / 4, y + Taille / 4, (Taille - 1) / 2, (Taille - 1) / 2, Imagine::BLACK);
        Imagine::fillRect(x * taillemax / Taille + Taille * NbCase + Separation, y * taillemax / Taille, taillemax,
                          taillemax, Imagine::BLACK);
    }
}


float Case::NbDep() const {
    return type.NbDep();
}


bool Case::Brillance() const {
    return brillance;
}

void Case::fastMarching(float dep, Case *carte, bool brillance, float &dep_restant, int case_a_atteindre) {
    int num_case = numeroCase(x, y);
    FilePriorite F;
    CaseDist depart(num_case, dep);
    F.push(depart);
    while (!F.empty()) {
        CaseDist c = F.pop();
        for (int i = -1; i <= 1; i = i + 2) {
            for (int j = 1; j <= NbCase; j = j + NbCase - 1) {
                if (c.getNum() + i * j >= 0 && c.getNum() + i * j < NbCase * NbCase &&
                    ((c.getNum() + i * j) % NbCase != 0 || c.getNum() % NbCase != NbCase - 1) &&
                    ((c.getNum() + i * j) % NbCase != NbCase - 1 || c.getNum() % NbCase != 0) &&
                    c.getDep() - carte[c.getNum() + i * j].NbDep() >= 0 &&
                    carte[c.getNum() + i * j].Brillance() != brillance &&
                    !carte[c.getNum() + i * j].getOccupe()) {
                    carte[c.getNum() + i * j].brillanceOnOff(brillance);
                    CaseDist c2(c.getNum() + i * j, c.getDep() - carte[c.getNum() + i * j].NbDep());
                    F.push(c2);
                }
                if (case_a_atteindre == c.getNum() && !brillance) {
                    dep_restant = c.getDep();
                }
            }
        }
    }
}


Imagine::Color Case::getImage(){
    return type.Image();
}


std::string Case::getDescription(){
    return type.Desctiption();
}


int numeroCase(int x, int y) {
    if (x >= LargGauche && x < LargGauche + NbCase * Taille && y < NbCase * Taille) {
        return ((y / Taille) * NbCase + x / Taille);
    }
    return -1;
}


void clic(int &x, int &y, Case *carte) {
    Imagine::enableMouseTracking(true);
    Imagine::Event e;
    do {
        getEvent(0, e);
        if (e.type == Imagine::EVT_BUT_ON) {
            x = e.pix[0];
            y = e.pix[1];
        }
        if (e.type == Imagine::EVT_MOTION) {
            x = e.pix[0];
            y = e.pix[1];
            afficheSurvole(x, y, carte);
        }
    } while (e.type != Imagine::EVT_BUT_OFF);
    Imagine::enableMouseTracking(false);
}


void deplaceHeros(Case *carte, Unite &h, int x1, int y1) {
    carte[h.getCase()].deplaceHeros(h, carte[numeroCase(x1, y1)]);
}


void afficheCaseDisponibleOnOff(Case *carte, Unite h, bool b, float &deplacement, int case_a_atteindre) {
    carte[h.getCase()].fastMarching(h.getDep(), carte, b, deplacement, case_a_atteindre);
}


void deplacement(Case *carte, std::vector<Unite> &unites, int u) {
    int x1, y1;
    float deplacement = unites[u].getDep();
    if (deplacement > 0) {
        // On met la variable deplacement juste parce qu'on est oblige, elle n'est pas modifiee ici
        afficheCaseDisponibleOnOff(carte, unites[u], true, deplacement, 0);
        do {
            clic(x1, y1, carte);
        } while (numeroCase(x1,y1) == -1 || !carte[numeroCase(x1, y1)].Brillance());
        afficheCaseDisponibleOnOff(carte, unites[u], false, deplacement, numeroCase(x1, y1));
        deplaceHeros(carte, unites[u], x1, y1);
        unites[u].setDep(deplacement);
    }
}


void finTour(std::vector<Unite> &unites, int x, int y) {
    // CONDITON A CHANGER EN FONCTION DU TRACE DE L'ENDROIT DE FIN DU TOUR #CLEMENT
    if (x > NbCase * Taille + Separation && y > Taille * (NbCase - 5)) {
        for (int i = 0; i < unites.size(); ++i) {
            unites[i].setDep(unites[i].getDepMax());
        }
    }
}


void choisir(int &choix){
    choix = -1;
    int tailleEcriture = 9;
    // A MODIFIER
    Imagine::drawString(NbCase * Taille + Separation, LargDroite + tailleEcriture + 1, "0 : deplacement", Imagine::BLACK, tailleEcriture);
    Imagine::drawString(NbCase * Taille + Separation, LargDroite + 2 * (tailleEcriture + 1), "1 : attaque", Imagine::BLACK, tailleEcriture);
    Imagine::Event e;
    do {
        getEvent(0, e);
        if (e.type == Imagine::EVT_KEY_ON) {
            choix = e.key;
        }
    } while (e.type != Imagine::EVT_KEY_OFF && (choix != Imagine::KEY_NUMPAD0 || choix != Imagine::KEY_NUMPAD1) );
    // A MODIFIER
    Imagine::fillRect(NbCase * Taille + Separation, LargDroite, LargDroite, 2 * (tailleEcriture + 2), Imagine::WHITE);
}


void survole(int &x, int &y){
    Imagine::Event e;
    getEvent(0, e);
    x = e.pix[0];
    y = e.pix[1];
}



void afficheSurvole(int x, int y, Case *carte){
    // A MODIFIER
    Imagine::fillRect(LargGauche + Separation + NbCase * Taille, LargDroite + 10, LargDroite, LargDroite, Imagine::WHITE);
    if (numeroCase(x, y) != - 1) {
        Imagine::fillRect(LargGauche + Separation + NbCase * Taille, LargDroite + 10, Taille, Taille, carte[numeroCase(x,y)].getImage());
        Imagine::drawString(LargGauche + Separation + NbCase * Taille, LargDroite + 30 + Taille, carte[numeroCase(x,y)].getDescription(), Imagine::BLACK, 4);
    }
}
