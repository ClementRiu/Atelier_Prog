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
    utileChemin = false;
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
    if (!flag) {
        utileChemin = flag;
    }
    this->affiche();
}


void Case::affiche() {
    Imagine::drawRect(x - 1, y - 1, Taille, Taille, Imagine::WHITE);
    Imagine::fillRect(x, y, Taille - 1, Taille - 1, type.Image());
    if (brillance) {
        Imagine::drawRect(x, y, Taille - 2, Taille - 2, Imagine::BLACK);
    }
    if (utileChemin) {
        Imagine::fillCircle(x + Taille / 2, y + Taille / 2, Taille / 5, Imagine::RED);
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


void Case::setChemin() {
    utileChemin = !utileChemin;
}


int Case::plusProcheVoisineBrillante(int x1, int y1, Carte &carte, int numcase) {
    // Renvoie la case voisine la plus proche du point (x1, y1) qui est en brillance
    std::vector<int> numCase = casesVoisines(x1, y1);
    for (int i = 0; i < numCase.size(); ++i) {
        if (carte[numCase[i]].Brillance() || numcase == numCase[i]) {
            return numCase[i];
        }
    }
    return -1;
}


std::vector<int> Case::casesVoisines(int x1, int y1) {
    std::vector<int> numCase;
    std::vector<int> priorite;
    // On cherche autour de notre case les cases qui sont accessibles
    if (numeroCase(x, y) % NbCase != NbCase - 1) {
        numCase.push_back(numeroCase(x, y) + 1);
        priorite.push_back(x + Taille - x1);
    }
    if (numeroCase(x, y) % NbCase != 0) {
        numCase.push_back(numeroCase(x, y) - 1);
        priorite.push_back(x1 - x);
    }
    if (numeroCase(x, y) >= NbCase) {
        numCase.push_back(numeroCase(x, y) - NbCase);
        priorite.push_back(y1 - y);
    }
    if (numeroCase(x, y) < NbCase * (NbCase - 1)) {
        numCase.push_back(numeroCase(x, y) + NbCase);
        priorite.push_back(y + Taille - y1);
    }
    // On trie les tableaux pour que les cases voisines apparaissant en premier soient vraiment les plus près du point de clic
    for (int i = priorite.size() - 1; i > 0; i = i - 1) {
        for (int j = 0; j < i; ++j) {
            if (priorite[j] > priorite[j + 1]) {
                int echange = priorite[j];
                priorite[j] = priorite[j + 1];
                priorite[j + 1] = echange;
                echange = numCase[j];
                numCase[j] = numCase[j + 1];
                numCase[j + 1] = echange;
            }
        }
    }
    return numCase;
}


std::vector<std::vector<int> > Case::fastMarching(float dep, Carte &carte, bool brillance, float &dep_restant,
                                                  int case_a_atteindre) {
    // Algorithme de FastMarching, cf cours d'Algo
    int num_case = numeroCase(x, y);
    FilePriorite F;
    std::vector<int> chemin;
    std::vector<std::vector<int> > differentsChemins;
    CaseDist depart(num_case, dep, chemin);
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
                    chemin = c.getChemin();
                    chemin.push_back(c.getNum() + i * j);
                    differentsChemins.push_back(chemin);
                    CaseDist c2(c.getNum() + i * j, c.getDep() - carte[c.getNum() + i * j].NbDep(), chemin);
                    F.push(c2);
                }
                if (case_a_atteindre == c.getNum() && !brillance) {
                    dep_restant = c.getDep();
                }
            }
        }
    }
    return differentsChemins;
}


Imagine::Color Case::getImage() {
    return type.Image();
}


std::string Case::getDescription() {
    return type.Description();
}


Carte::Carte() {
    // Initialisation des types de case
    TypeCase eau(INF, "De l'eau, sans vie, sans poisson, rien que de l'eau", Imagine::BLUE);
    TypeCase herbe(2, "C'est vert, les souris s'y cachent, c'est de l'herbe", Imagine::GREEN);
    TypeCase route(1, "Une case a moindre cout de deplacement", Imagine::YELLOW);
    TypeCase ville(1, descVille, Imagine::MAGENTA);

    // Creation de la carte
    for (int i = 0; i < NbCase * Taille; i += Taille) {
        for (int j = 0; j < NbCase * Taille; j += Taille) {
            if ((i + 1) % (j + 1) == 0) {
                Case c(i, j, eau);
                carte[numeroCase(i, j)] = c;
            }
            if ((i + 1) % (j + 1) == 1) {
                Case c(i, j, herbe);
                carte[numeroCase(i, j)] = c;
            }
            if ((i + 1) % (j + 1) > 1) {
                Case c(i, j, route);
                carte[numeroCase(i, j)] = c;
            }
        }
    }
    Case c(0, 0, ville);
    carte[0] = c;
}


Case &Carte::operator[](int i) {
    return carte[i];
}


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


int numeroCase(int x, int y) {
    if (x >= LargGauche && x < LargGauche + NbCase * Taille && y < NbCase * Taille) {
        return ((y / Taille) * NbCase + x / Taille);
    }
    return -1;
}


void clic(int &x, int &y, Carte &carte, std::vector<std::vector<int> > differentsChemins, int numcase) {
    Imagine::enableMouseTracking(true);
    Imagine::Event e;
    do {
        getEvent(0, e);
        if (e.type == Imagine::EVT_BUT_ON) {
            x = e.pix[0];
            y = e.pix[1];
        }
        if (e.type == Imagine::EVT_MOTION) {
            // On affiche et on efface les chemins qui correspondent à l'emplacement de la souris
            afficheChemins(x, y, carte, differentsChemins, numcase);
            x = e.pix[0];
            y = e.pix[1];
            // On affiche la case que l'on survole
            afficheSurvole(x, y, carte);
            afficheChemins(x, y, carte, differentsChemins, numcase);
        }
    } while (e.type != Imagine::EVT_BUT_OFF);
    Imagine::enableMouseTracking(false);
}


void clic(int &x, int &y, Carte &carte) {
    std::vector<std::vector<int> > differentsChemins;
    clic(x, y, carte, differentsChemins, 0);
}


void clicSimple(int &x, int &y) {
    Imagine::Event e;
    do {
        getEvent(0, e);
        if (e.type == Imagine::EVT_BUT_ON) {
            x = e.pix[0];
            y = e.pix[1];
        }
    } while (e.type != Imagine::EVT_BUT_OFF);
}


void finJournee(std::vector<Unite *> unites) {
    std::cout << "à compléter !! (fonction finJournee)" << std::endl;
    for (int i = 0; i < unites.size(); ++i) {
        unites[i]->setDep(unites[i]->getDepMax());
    }
}


void finTourCombat(std::vector<Unite *> unites) {
    std::cout << "à modifier !! (fonction finTourCombat)" << std::endl;
    for (int i = 0; i < unites.size(); ++i) {
        unites[i]->setDep(unites[i]->getDepMax());
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


void afficheSurvole(int x, int y, Carte &carte) {
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


void afficheChemins(int x, int y, Carte &carte, std::vector<std::vector<int> > differentsChemins, int numcase) {
    // L'entier suivant correspont à la case la plus proche de (x,y) qui est en brillance. == -1 si aucune.
    int caseProche = carte[numeroCase(x, y)].plusProcheVoisineBrillante(x, y, carte, numeroCase(x, y));
    if (numeroCase(x, y) != -1) {
        int num;
        // La dernière condition signifie que l'on est pas en train de regarder la position du Heros
        if (carte[numeroCase(x, y)].Brillance() ||
            (carte[numeroCase(x, y)].getOccupe() && caseProche != -1 &&
             numeroCase(x, y) != numcase)) {
            // On met dans num le numéro de la case où l'on veut aller
            if (carte[numeroCase(x, y)].Brillance()) {
                num = numeroCase(x, y);
            }
            else {
                num = caseProche;
            }
            // On met en place et on affiche le chemin
            for (int i = 0; i < differentsChemins.size(); ++i) {
                if (differentsChemins[i][differentsChemins[i].size() - 1] == num) {
                    for (int j = 0; j < differentsChemins[i].size(); ++j) {
                        carte[differentsChemins[i][j]].setChemin();
                        carte[differentsChemins[i][j]].affiche();
                    }
                }
            }
        }
    }
}


void sauvegarde(std::vector<Unite *> unites) {
    std::ofstream fichier("../Gestion/sauvegarde.txt", std::ios::out | std::ios::trunc);
    if (fichier) {
        fichier << unites.size() << std::endl;
        for (int i = 0; i < unites.size(); i++) {
            fichier << unites[i]->getCase() << std::endl;
            fichier << unites[i]->getDep() << std::endl;
            fichier << unites[i]->getDepMax() << std::endl;
        }
        fichier.close();
    }
    else {
        std::cout << "Erreur à l'ouverture !" << std::endl;
    }
}


void charge(std::vector<Unite *> unites, Carte &carte) {
    std::ifstream fichier("D:/Charles/cours/Ponts/Info/2sem/Projet/Atelier_Prog/Gestion/sauvegarde.txt", std::ios::in);
    if (fichier) {
        std::string ligne;
        std::getline(fichier, ligne);
        int T = atoi(ligne.c_str());
        std::cout << T;
        for (int i = 0; i < T; i++) {
            std::getline(fichier, ligne);
            int num = atoi(ligne.c_str());
            carte[num].flagHeros();
            std::getline(fichier, ligne);
            float dep = atoi(ligne.c_str());
            std::getline(fichier, ligne);
            float depMax = atoi(ligne.c_str());
            unites.push_back(new Unite(dep, depMax, num));
        }
        fichier.close();
    }
    else {
        std::cerr << "Erreur à l'ouverture !" << std::endl;
    }
}



