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


std::string TypeCase::Description() {
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


//à se débarasser, présent uniquement dans Unite::deplaceVersCase
int Case::get(int i) {
    if (i == 0) {
        return x;
    }
    else {
        return y;
    }
}


void Case::brillanceOnOff(bool flag) {
    brillance = flag;
    this->affiche();
}


void Case::affiche() {
    Imagine::drawRect(x - 1, y - 1, Taille, Taille, Imagine::WHITE);
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


Imagine::Color Case::getImage() {
    return type.Image();
}


std::string Case::getDescription() {
    return type.Description();
}


Bouton::Bouton (int xmin, int ymin, int xmax, int ymax, Imagine::Color c, std::string nom){
    zoneDeDelimitation[0]=xmin;
    zoneDeDelimitation[1]=ymin;
    zoneDeDelimitation[2]=xmax;
    zoneDeDelimitation[3]=ymax;
    image=c;
    nomBouton=nom;
    taillePolice = 0;
}


int Bouton::largeur(){
    return zoneDeDelimitation[2] - zoneDeDelimitation[0];
}


int Bouton::hauteur(){
    return zoneDeDelimitation[3] - zoneDeDelimitation[1];
}


// A changer
void Bouton::affiche(){
    int taille = std::min(int (1.5 * this->largeur() / nomBouton.size()), this->hauteur());
    Imagine::fillRect(zoneDeDelimitation[0], zoneDeDelimitation[1], this->largeur(),
            this->hauteur(), image);
    Imagine::drawString(zoneDeDelimitation[0], zoneDeDelimitation[1] + taille, nomBouton, Imagine::WHITE, taille);
}


bool Bouton::boutonActive(int x, int y){
    if (x > zoneDeDelimitation[0] && y > zoneDeDelimitation[1] && x < zoneDeDelimitation[2] && y < zoneDeDelimitation[3]) {
        return true;
    }
    return false;
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


void finJournee(std::vector<Unite> &unites) {
    std::cout << "à compléter !! (fonction finJournee)" << std::endl;
    for (int i = 0; i < unites.size(); ++i) {
        unites[i].setDep(unites[i].getDepMax());
    }
}

void finTourCombat(std::vector<Unite> &unites) {
    std::cout << "à modifier !! (fonction finTourCombat)" << std::endl;
    for (int i = 0; i < unites.size(); ++i) {
        unites[i].setDep(unites[i].getDepMax());
    }
}


// A supprimer a la fin, mais on le garde au cas ou on change d'avis
void choisir(int &choix, int &x, int &y) {
    choix = -1;
    x = -1;
    y = -1;
    int tailleEcriture = 9;
    // A MODIFIER
    Imagine::drawString(NbCase * Taille + Separation, LargDroite + tailleEcriture + 1, "0 : deplacement",
                        Imagine::BLACK, tailleEcriture);
    Imagine::drawString(NbCase * Taille + Separation, LargDroite + 2 * (tailleEcriture + 1), "1 : attaque",
                        Imagine::BLACK, tailleEcriture);
    Imagine::drawString(NbCase * Taille + Separation, LargDroite + 3 * (tailleEcriture + 1), "ESP: Fin de tour",
                        Imagine::BLACK, tailleEcriture);
    Imagine::Event e;
    do {
        getEvent(0, e);
        if (e.type == Imagine::EVT_KEY_ON) {
            choix = e.key;
        }
        if (e.type == Imagine::EVT_BUT_ON) {
            x = e.pix[0];
            y = e.pix[1];
        }
    } while (e.type != Imagine::EVT_KEY_OFF && e.type != Imagine::EVT_BUT_OFF);
    // A MODIFIER
    Imagine::fillRect(NbCase * Taille + Separation, LargDroite, LargDroite, 2 * (tailleEcriture + 2), Imagine::WHITE);
}


void survole(int &x, int &y) {
    Imagine::Event e;
    getEvent(0, e);
    x = e.pix[0];
    y = e.pix[1];
}


void afficheSurvole(int x, int y, Case *carte) {
    // A MODIFIER
    Imagine::fillRect(LargGauche + Separation + NbCase * Taille, LargDroite + 10, LargDroite, LargDroite,
                      Imagine::WHITE);
    if (numeroCase(x, y) != -1) {
        Imagine::fillRect(LargGauche + Separation + NbCase * Taille, LargDroite + 10, Taille, Taille,
                          carte[numeroCase(x, y)].getImage());
        Imagine::drawString(LargGauche + Separation + NbCase * Taille, LargDroite + 30 + Taille,
                            carte[numeroCase(x, y)].getDescription(), Imagine::BLACK, 4);
    }
}


void sauvegarde(std::vector<Unite> unites) {
    std::ofstream fichier("../Gestion/sauvegarde.txt", std::ios::out | std::ios::trunc);
        if (fichier) {
            fichier << unites.size() << std::endl;
            for (int i = 0; i < unites.size(); i ++){
                fichier << unites[i].getCase() << std::endl;
                fichier << unites[i].getDep() << std::endl;
                fichier << unites[i].getDepMax() << std::endl;
            }
            fichier.close();
        }
        else {
            std::cout << "Erreur à l'ouverture !" << std::endl;
        }
}


void charge(std::vector<Unite> &unites, Case *carte){
    std::ifstream fichier("D:/Charles/cours/Ponts/Info/2sem/Projet/Atelier_Prog/Gestion/sauvegarde.txt", std::ios::in);
        if(fichier){
            std::string ligne;
            std::getline(fichier,ligne);
            int T = atoi(ligne.c_str());
            std::cout << T;
            for (int i = 0; i < T; i ++){
                Unite u;
                std::getline(fichier,ligne);
                float val = atoi(ligne.c_str());
                u.setCase(val);
                carte[int(val)].flagHeros();
                std::getline(fichier,ligne);
                val = atoi(ligne.c_str());
                u.setDep(val);
                std::getline(fichier,ligne);
                val = atoi(ligne.c_str());
                u.setDepMax(val);
                unites.push_back(u);
            }
            fichier.close();
        }
    else {
        std::cerr << "Erreur à l'ouverture !" << std::endl;
    }
}



