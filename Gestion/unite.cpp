#include "unite.h"
#include <iostream>
#include "joueurs.h"


//attaque de base
Attaque::Attaque() {
    zoneInfluence.push_back(portee10);
    zoneInfluence.push_back(portee01);
    zoneInfluence.push_back(portee_10);
    zoneInfluence.push_back(portee0_1);

    puissance = 10;
}

//vérifier que la copie de vectors fonctionne bien !!
Attaque::Attaque(const Attaque &att) {
    zoneInfluence = att.zoneInfluence;
    puissance = att.puissance;
}


Attaque::Attaque(std::vector<Imagine::Coords<2> > zone, int power) {
    zoneInfluence = zone;
    puissance = power;
}


void Attaque::zone(Carte &carte, bool b, int caseUnite) {
    for (int i = 0; i < zoneInfluence.size(); ++i) {
        if (caseUnite + zoneInfluence[i].y() * NbCase > 0 && caseUnite + zoneInfluence[i].y() * NbCase &&
            (caseUnite / NbCase == (caseUnite + zoneInfluence[i].x()) / NbCase)) {
            carte[caseUnite + zoneInfluence[i].x() + zoneInfluence[i].y() * NbCase].brillanceOnOff(b);
        }
    }
}


int Attaque::getPuissance() {
    return puissance;
}


Unite::Unite() {
    tour = false;
    PDep = 8;
    numcase = 0;
    PV = 100;
    force = 10;
}


Unite::Unite(const Unite &unit) {
    tour = false;
    PV = unit.PV;
    PVMax = unit.PVMax;
    mana = unit.mana;
    manaMax = unit.manaMax;
    force = unit.force;
    dexterite = unit.dexterite;
    initiative = unit.initiative;
    numcase = unit.numcase;
    PDep = unit.PDep;
    PDepMax = unit.PDepMax;
    initiativeTemporaire = unit.initiativeTemporaire;

    for (int i = 0; i++; i < NB_DEG_PHY) {
        defensePhy[i] = unit.defensePhy[i];
    }

    for (int i = 0; i++; i < NB_RES) {
        defenseMag[i] = unit.defenseMag[i];
    }

    for (int i = 0; i++; i < NB_MAX_ATTAQUES) {
        competences[i] = unit.competences[i];
    }
}


Unite::Unite(int ID, float dep, float depMax, int num, float init) {
    tour = false;
    IDjoueur = ID;
    PDep = dep;
    PDepMax = depMax;
    numcase = num;
    PDepMax = dep;
    initiative = init;
    initiativeTemporaire = init;
    PV = 100;
    force = 10;
}


/*
Unite::Unite(float dep, float depMax, int num) {
    PDep = dep;
    numcase = num;
    PDepMax = depMax;
}
*/


Unite::Unite(float dep, int num){
    PDep = dep;
    numcase = num;
    initiative = 0;
    initiativeTemporaire = 0;
    PV = 100;
    force = 10;
}


bool Unite::operator<(Unite u) const{
    return (initiativeTemporaire < u.initiativeTemporaire);
}

void Unite::choixAction() {
    std::cout << "Implementer le choix d'action méthode choixAction de Unite";
}


void Unite::deplacement(Carte &carte, int x1, int y1, bool gestion) {
    float dep = PDep;

    if (dep > 0) {
        if (carte[numeroCase(x1, y1)].Brillance()) {
            afficheCaseDisponibleOnOff(carte, false, dep, numeroCase(x1, y1));
            deplaceVersCase(carte[numeroCase(x1, y1)], carte[numcase]);
            PDep = dep;
            return;
        }

        int caseDep = carte[numeroCase(x1, y1)].plusProcheVoisineBrillante(x1, y1, carte, numcase);
        // Cas où l'on a cliqué sur une Unite que l'on veut/peut attaquer.

        if (!gestion && numeroCase(x1, y1) != numcase && carte[numeroCase(x1, y1)].getOccupe() && caseDep != -1) {
            afficheCaseDisponibleOnOff(carte, false, dep, caseDep);
            deplaceVersCase(carte[caseDep], carte[numcase]);
            PDep = dep;
            this->attaqueDeBase(carte[numeroCase(x1,y1)].getUnite());
            return;
        }

        afficheCaseDisponibleOnOff(carte, false, dep, numeroCase(x1, y1));
    }
}


// Fonction simple permettant d'afficher les cases disponibles pour le Heros, ou de les enlever
std::vector<std::vector<int> > Unite::afficheCaseDisponibleOnOff(Carte &carte, bool b, float &deplacement,
                                                                 int case_a_atteindre) {
    return carte[numcase].fastMarching(PDep, carte, b, deplacement, case_a_atteindre);
}


void Unite::deplaceVersCase(Case &c2, Case &c1) {
    if (!c2.getOccupe()) {
        c2.flagHeros(c1.getUnite());
        c1.flagHeros(NULL);
        c1.affiche();
        c2.affiche();
        numcase = numeroCase(c2.get(0), c2.get(1));
    }
}


void Unite::changeOrientation(int i) {
    orientation = i;
}


void Unite::changeInitiativeTemporaire() {
    initiativeTemporaire -= 30;
}


int Unite::getCase() const {
    return numcase;
}

int Unite::getID() const {
    return IDjoueur;
}

float Unite::getInit() const{
    return initiativeTemporaire;
}


void Unite::ouvreVille(Ville* v) {

}


void Unite::setCase(int num) {
    numcase = num;
}


float Unite::getDep() const {
    return PDep;
}


void Unite::setDep(float dep) {
    PDep = dep;
}


void Unite::setDepMax(float depMax) {
    PDepMax = depMax;
}


float Unite::getDepMax() const {
    return PDepMax;
}


//à implémenter
void Unite::prendDommage(int attRecue) {
    std::cout << "à implémenter !" << std::endl;
    PV = PV - 10;
}


void Unite::setAttaque(Attaque att, int i) {
    competences[i] = att;
}



bool Unite::estVivant() {
    if (PV <= 0) {
        return false;
    }
    return true;
}


void Unite::tourCombat(Carte &carte, std::vector<Unite *> unites, Bouton boutonFinTour, Bouton boutonAction) {
    bool tourContinue = true;
    int x = 0, y = 0;

    while (tourContinue) {
        // On stocke les différents chemins si on veut pouvoir les afficher. Cela dépend si on est en Gestion ou en Combat
        std::vector<std::vector<int> > differentsChemins;

        differentsChemins = afficheCaseDisponibleOnOff(carte, true, PDep, 0);
        boutonAction.affiche();

        clic(x, y, carte, differentsChemins, numcase);

        // A modifier
        for (int i = 0; i < NbCase; ++i) {
            for (int j = 0; j < NbCase; ++j) {
                carte[j * NbCase + i].affiche();
            }
        }

        if (boutonFinTour.boutonActive(x, y)) {
            afficheCaseDisponibleOnOff(carte, false, PDep, 0);
            break;
        }

        // A modifier, voir l'ordre des boutons


        if (boutonAction.boutonActive(x, y)) {
            afficheCaseDisponibleOnOff(carte, false, PDep, 0);
            competences[1].zone(carte, true, getCase());
            attaque(competences[0], carte);
            competences[1].zone(carte, false, getCase());
            tourContinue = false;
        }
        else {
            deplacement(carte, x, y, false);
        }
        boutonAction.affiche();

        if (PDep==0){
            tourContinue=false;
        }
    }
    finTourCombat(unites);
}


void Unite::action(Attaque att, Unite *u) {
    // A MODIFIER
    u->prendDommage(att.getPuissance());
}


void Unite::attaqueDeBase(Unite* u) {
    u->prendDommage(force);
}


void Unite::declancheCombat(Unite* u) {

}

void Unite::retire(int i) {

}


void Unite::attaque(Attaque attq, Carte &carte) {
    int x1, y1 = 0;

    do {
        clic(x1, y1, carte);
    } while (numeroCase(x1, y1) < 0 || !carte[numeroCase(x1, y1)].Brillance());
    if (carte[numeroCase(x1, y1)].getOccupe()) {
        action(attq, carte[numeroCase(x1, y1)].getUnite());
    }
}


/*
// La fonction est a modifier niveau affichage et a organiser
std::vector<Bouton> Unite::boutonAction(Carte &carte) {
    int coin = 0;
    int longMaxMot = 0;
    int taillePolice = Taille / 2 - 2;
    int caseIni = numcase;
    int x, y;
    std::vector<std::string> nomBoutons;
    nomBoutons.push_back("Action");
    nomBoutons.push_back("Inventaire");
    if (PDep != 0) {
        nomBoutons.push_back("Déplacement");
    }
    if (carte[numcase].getDescription() == descVille) {
        nomBoutons.push_back("Ville");
    }
    for (int i = 0; i < nomBoutons.size(); ++i) {
        longMaxMot = std::max(int(nomBoutons[i].size()), longMaxMot);
    }
    int largMax = (int((longMaxMot * taillePolice * 1.5) / Taille) + 1) * Taille - 2;
    std::vector<Bouton> B;
    if (numcase % NbCase >= NbCase / 2) {
        coin += 1;
    }
    if (numcase >= NbCase * NbCase / 2) {
        coin += 2;
    }
    if (coin == 0) {
        caseIni += 1 + NbCase;
    }
    if (coin == 1) {
        caseIni += -1 - largMax / Taille + NbCase;
    }
    if (coin == 2) {
        caseIni += 1 - NbCase;
    }
    if (coin == 3) {
        caseIni += -1 - largMax / Taille - NbCase;
    }
    x = (caseIni % NbCase) * Taille;
    y = (caseIni / NbCase) * Taille;
    for (int i = 0; i < nomBoutons.size(); ++i) {
        Bouton b(x, y + i * Taille * ((-1) * (coin > 1) + (coin <= 1)), x + largMax + 1,
                 y + Taille - 1 + i * Taille * ((-1) * (coin > 1) + (coin <= 1)), Imagine::BLACK,
                 nomBoutons[i]);
        B.push_back(b);
    }
    return B;
}
*/

void Unite::ramasse(Mere *obj) {

}

void Unite::achete(Ville* ville, int i, bool b) {
}


void Unite::ouvreInventaire() {

}


void Unite::equipe(Ville* ville, int i, bool droite) {

}


std::string Unite::getNomCasque() {

}


Unite::~Unite() {

}


Sbire::Sbire() {

}


Sbire::Sbire(const Sbire &s) {

}


Armee::Armee() {

}


Armee::Armee(std::vector<Sbire> sbires) {
    for (int i = 0; i < TAILLE_ARMEE; i++) {
        sbireArmee[i] = sbires[i];
    }
}


Armee::Armee(const Armee &a) {
    for (int i = 0; i < TAILLE_ARMEE; i++) {
        sbireArmee[i] = a.sbireArmee[i];
    }
}


Heros::Heros(int ID, float dep, float depMax, int num, float init) : Unite(ID, dep, depMax, num, init) {
    Casque c("Casque de base");
    Arme a("Arme de base");
    Torse t("Armure de Base");
    Gants g("Gants de base");
    Anneau an("Anneau de base");
    Bottes b("Bottes de base");
    Jambes j("Genouilleres de base");
    equipementCasque = c;
    equipementArmeDroite = a;
    equipementTorse = t;
    equipementGants = g;
    equipementAnneauDroite = an;
    equipementBottes = b;
    equipementJambes = j;
}


Heros::Heros(const Heros &h) : Unite(h) {
    niveau = h.niveau;
    exp = h.exp;
    ArmeeHeros = h.ArmeeHeros;
}

void Heros::retire(int i) {
    inventaire.retire(i);
}


void Heros::ouvreVille(Ville* v) {
    Heros* h2 = new Heros(1,1,1,1,1);
    if (typeid(this)== typeid(h2)){
        // Creation des differents boutons pour les differentes categories d'objets
        std::vector<Bouton> boutonsChoix;
        std::vector<std::string> nomBoutons;
        nomBoutons.push_back("Arme");
        nomBoutons.push_back("Anneau");
        nomBoutons.push_back("Bottes");
        nomBoutons.push_back("Gants");
        nomBoutons.push_back("Jambes");
        nomBoutons.push_back("Torse");
        nomBoutons.push_back("Casque");
        nomBoutons.push_back("Objets divers");
        for (int i = 0; i < nomBoutons.size(); ++i) {
            Bouton b(0, Police * i, 140, Police * (i + 1), Imagine::BLACK, nomBoutons[i]);
            boutonsChoix.push_back(b);
        }

        // Creation des differentes categories d'objets
        Inventaire categoriesObjets;
        categoriesObjets.ajoute(new Arme());
        categoriesObjets.ajoute(new Anneau());
        categoriesObjets.ajoute(new Bottes());
        categoriesObjets.ajoute(new Gants());
        categoriesObjets.ajoute(new Jambes());
        categoriesObjets.ajoute(new Torse());
        categoriesObjets.ajoute(new Casque());
        categoriesObjets.ajoute(new Objet());

        // Creation du pointeur vers la fonction equipe
        void (Unite::*pointeurFonction)(Ville*, int, bool) = &Unite::achete;

        (v->getInventaire()).ouvreInventaire(boutonsChoix, categoriesObjets, v, this, pointeurFonction);
        //inventaire.ouvreInventaire(boutonsChoix, categoriesObjets, this, pointeurFonction);
    }
    delete h2;
}


void Heros::achete(Ville* ville, int i, bool b) {
    this->ramasse(ville->getObjet(i)->clone());
}


void Heros::declancheCombat(Unite* u) {
    Bouton boutonFinTour(ZoneBoutonFinTour, Imagine::BLACK, "End turn");
    Bouton boutonAction(ZoneBoutonAction, Imagine::BLACK, "Action");
    Bouton boutonInventaire(ZoneBoutonInventaire, Imagine::BLACK, "Inventaire");
    boutonFinTour.affiche();
    boutonAction.affiche();
    boutonInventaire.affiche();

    // Initialisation d'une attaque
    std::vector<Imagine::Coords<2> > zoneInfl;
    zoneInfl.push_back(portee10);
    zoneInfl.push_back(portee_10);
    zoneInfl.push_back(portee20);
    zoneInfl.push_back(portee_20);
    zoneInfl.push_back(portee01);
    zoneInfl.push_back(portee02);
    zoneInfl.push_back(portee0_2);
    zoneInfl.push_back(portee0_1);
    Attaque coinCoinOuille(zoneInfl, 10);

    Carte carte(0);

    int positionGestion[2] = {this->getCase(), u->getCase()};

    // Initialisation des unites
    this->setCase(100);
    u->setCase(200);
    std::vector<Unite *> unites;
    unites.push_back(this);
    unites.push_back(u);
    carte[100].flagHeros(unites[0]);
    carte[200].flagHeros(unites[1]);

    carte.affiche();

    FilePriorite<Unite> fileUnites;
    fileUnites.push(unites[0]);
    fileUnites.push(unites[1]);


    int i = 1; //numéro du tour, à remplacer

    while (true) {
        //règles d'initiative assez arbitraires, à modifier #Nathanael
        Unite* unitJouable = fileUnites.pop();
        unitJouable->tourCombat(carte, unites, boutonFinTour, boutonAction);
        unitJouable->changeInitiativeTemporaire();
        fileUnites.push(unitJouable);
        i += 1;
    }

    this->setCase(positionGestion[0]);
    u->setCase(positionGestion[1]);
}


Heros::Heros(const Unite &h) : Unite(h) {
}


//*********************************EQUIPEMENT********************************************


Casque Heros::equipeCasque(Casque casque) {
    Casque desequipe = equipementCasque;

    equipementCasque = casque;

    return desequipe;
}


Arme Heros::equipeArmeDroite(Arme arme) {
    Arme desequipe = equipementArmeDroite;

    equipementArmeDroite = arme;

    return desequipe;
}


Arme Heros::equipeArmeGauche(Arme arme) {
    Arme desequipe = equipementArmeGauche;

    equipementArmeGauche = arme;

    return desequipe;
}


Torse Heros::equipeTorse(Torse torse) {
    Torse desequipe = equipementTorse;

    equipementTorse = torse;

    return desequipe;

}

Gants Heros::equipeGants(Gants gants) {
    Gants desequipe = equipementGants;

    equipementGants = gants;

    return desequipe;
}

Jambes Heros::equipeJambes(Jambes jambes) {
    Jambes desequipe = equipementJambes;

    equipementJambes = jambes;

    return desequipe;
}

Bottes Heros::equipeBottes(Bottes bottes) {
    Bottes desequipe = equipementBottes;

    equipementBottes = bottes;

    return desequipe;
}


Anneau Heros::equipeAnneauDroite(Anneau anneau) {
    Anneau desequipe = equipementAnneauDroite;

    equipementAnneauDroite = anneau;

    return desequipe;
}


Anneau Heros::equipeAnneauGauche(Anneau anneau) {
    Anneau desequipe = equipementAnneauGauche;

    equipementAnneauGauche = anneau;

    return desequipe;
}


void Heros::equipe(Ville* ville, int i, bool droite) {
    if (i < inventaire.taille()) {
        inventaire.get(i)->equiper(this, droite);
    }
}


void Heros::ramasse(Mere *obj) {
    inventaire.ajoute(obj);
}


void Heros::ouvreInventaire() {
    // Creation des differents boutons pour les differentes categories d'objets
    std::vector<Bouton> boutonsChoix;
    std::vector<std::string> nomBoutons;
    nomBoutons.push_back("Arme");
    nomBoutons.push_back("Anneau");
    nomBoutons.push_back("Bottes");
    nomBoutons.push_back("Gants");
    nomBoutons.push_back("Jambes");
    nomBoutons.push_back("Torse");
    nomBoutons.push_back("Casque");
    nomBoutons.push_back("Objets divers");
    for (int i = 0; i < nomBoutons.size(); ++i) {
        Bouton b(0, Police * i, 140, Police * (i + 1), Imagine::BLACK, nomBoutons[i]);
        boutonsChoix.push_back(b);
    }

    // Creation des differentes categories d'objets
    Inventaire categoriesObjets;
    categoriesObjets.ajoute(new Arme());
    categoriesObjets.ajoute(new Anneau());
    categoriesObjets.ajoute(new Bottes());
    categoriesObjets.ajoute(new Gants());
    categoriesObjets.ajoute(new Jambes());
    categoriesObjets.ajoute(new Torse());
    categoriesObjets.ajoute(new Casque());
    categoriesObjets.ajoute(new Objet());

    // Creation du pointeur vers la fonction equipe
    void (Unite::*pointeurFonction)(Ville*, int, bool) = &Unite::equipe;

    inventaire.ouvreInventaire(boutonsChoix, categoriesObjets, NULL, this, pointeurFonction);

    //categoriesObjets.~Inventaire();
}


std::string Heros::getNomCasque() {
    return equipementCasque.getNom();
}


Heros::~Heros() {
    inventaire.~Inventaire();
}

