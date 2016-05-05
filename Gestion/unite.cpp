#include "unite.h"
#include <iostream>


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


void Attaque::zone(Case *carte, bool b, int caseUnite) {
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
    PDep = 8;
    numcase = 0;
}


Unite::Unite(const Unite &unit) {
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


Unite::Unite(float dep, int num) {
    PDep = dep;
    numcase = num;
    PDepMax = dep;
}


Unite::Unite(float dep, float depMax, int num) {
    PDep = dep;
    numcase = num;
    PDepMax = depMax;
}


void Unite::deplacement(Case *carte) {
    int x1, y1;
    float dep = PDep;
    if (dep > 0) {
        // On met la variable deplacement juste parce qu'on est oblige, elle n'est pas modifiee ici
        afficheCaseDisponibleOnOff(carte, true, dep, 0);
        do {
            clic(x1, y1, carte);

            //Si le joueur clique sur l'unité on annule la phase de déplacement et on retourne au choix d'action
            if (numeroCase(x1, y1) == numcase) {
                afficheCaseDisponibleOnOff(carte, false, dep, numeroCase(x1, y1));
                return;
            }
        } while (numeroCase(x1, y1) == -1 || !carte[numeroCase(x1, y1)].Brillance());


        afficheCaseDisponibleOnOff(carte, false, dep, numeroCase(x1, y1));
        deplaceVersCase(carte[numeroCase(x1, y1)], carte[numcase]);
        PDep = dep;
    }
}


// Fonction simple permettant d'afficher les cases disponibles pour le Heros, ou de les enlever
void Unite::afficheCaseDisponibleOnOff(Case *carte, bool b, float &deplacement, int case_a_atteindre) {
    carte[numcase].fastMarching(PDep, carte, b, deplacement, case_a_atteindre);
}


void Unite::deplaceVersCase(Case &c2, Case &c1) {
    if (!c2.getOccupe()) {
        c1.flagHeros();
        c2.flagHeros();
        c1.affiche();
        c2.affiche();
        numcase = numeroCase(c2.get(0), c2.get(1));
    }
}


void Unite::changeOrientation(int i) {
    orientation = i;
}


int Unite::getCase() const {
    return numcase;
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


void Unite::tour(Case *carte, std::vector<Unite*> unites, Bouton boutonFinTour) {
    bool tourContinue = true;
    int x = 0, y = 0;

    while (tourContinue) {

        std::vector<Bouton> boutons = this->boutonAction(carte);
        for (int i=0; i < boutons.size(); ++i){
            boutons[i].affiche();
        }

        clic(x, y, carte);

        // A modifier
        for (int i = 0; i < NbCase; ++i){
            for (int j = 0; j < NbCase; ++j){
                carte[j * NbCase + i].affiche();
            }
        }

        if (boutonFinTour.boutonActive(x, y)) {
            break;
        }

        // A modifier, voir l'ordre des boutons
        if (boutons[2].boutonActive(x, y)) {
            deplacement(carte);
        }
        if (boutons[0].boutonActive(x, y)) {
            competences[1].zone(carte, true, getCase());
            attaque(competences[0], carte, unites);
            competences[1].zone(carte, false, getCase());
            tourContinue = false;
        }
    }
    finTourCombat(unites);
}


void Unite::action(Attaque att, Unite *u) {
    // A MODIFIER
    u->prendDommage(att.getPuissance());
}


void Unite::attaque(Attaque attq, Case *carte, std::vector<Unite*> unites) {
    int x1, y1, u2 = 0;

    do {
        clic(x1, y1, carte);
    } while (numeroCase(x1, y1) < 0 || !carte[numeroCase(x1, y1)].Brillance());
    //CETTE PARTIE DU CODE EST ATROCE !!!!!!!!
    if (carte[numeroCase(x1, y1)].getOccupe()) {
        while (unites[u2]->getCase() != numeroCase(x1, y1)) {
            u2 += 1;
        }
        action(attq, unites[u2]);
    }
}


// La fonction est a modifier niveau affichage et a organiser
std::vector<Bouton> Unite::boutonAction(Case *carte){
    int coin = 0;
    int longMaxMot = 0;
    int taillePolice = Taille / 2 - 2;
    int caseIni = numcase;
    int x, y;
    std::vector<std::string> nomBoutons;
    nomBoutons.push_back("Action");
    nomBoutons.push_back("Inventaire");
    if (PDep!=0){
        nomBoutons.push_back("Déplacement");
    }
    if (carte[numcase].getDescription()==descVille){
        nomBoutons.push_back("Ville");
    }
    for (int i = 0; i < nomBoutons.size(); ++i){
        longMaxMot = std::max(int(nomBoutons[i].size()),longMaxMot);
    }
    int largMax = (int((longMaxMot * taillePolice * 1.5) / Taille) + 1) * Taille - 2;
    std::vector<Bouton> B;
    if (numcase % NbCase >= NbCase / 2){
        coin += 1;
    }
    if (numcase >= NbCase * NbCase / 2){
        coin += 2;
    }
    if (coin == 0){
        caseIni += 1 + NbCase;
    }
    if (coin == 1){
        caseIni += - 1 - largMax / Taille + NbCase;
    }
    if (coin == 2){
        caseIni += 1 - NbCase;
    }
    if (coin == 3){
        caseIni += - 1 - largMax / Taille - NbCase;
    }
    x = (caseIni % NbCase) * Taille;
    y = (caseIni / NbCase) * Taille;
    for (int i = 0; i < nomBoutons.size(); ++i){
        Bouton b(x, y + i *  Taille * ((-1) * (coin > 1) + (coin <= 1)), x + largMax + 1,
                  y + Taille - 1 + i * Taille * ((-1) * (coin > 1) + (coin <= 1)), Imagine::BLACK,
                 nomBoutons[i]);
        B.push_back(b);
    }
    return B;
}


void Unite::ramasse(Objet *obj){

}


void Unite::ouvreInventaire(){

}


void Unite::equipe(int i, bool droite){

}


std::string Unite::getNomCasque(){

}


Unite::~Unite(){

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


Heros::Heros(float dep, int num) : Unite(dep, num) {
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


void Heros::equipe(int i, bool droite) {
    if (i < inventaire.size()) {
        inventaire[i]->equiper(this, droite);
    }
}


void Heros::ramasse(Objet* obj){
    inventaire.push_back(obj);
}


// Fonction a modifier
void Heros::ouvreInventaire(){
    Imagine::fillRect(0, 0, width, height, Imagine::WHITE);
    std::vector<Bouton> boutonsChoix;
    std::vector<std::string> nomBoutons;
    std::vector<Objet*> nomObjets;
    std::vector<Bouton> boutonEquipement;
    std::vector<int> equipementPresent;
    Bouton boutonStop(NbCase * Taille + Separation, Taille * (NbCase - 5),
                         NbCase * Taille + Separation + LargDroite, NbCase * Taille, Imagine::BLACK,
                         "Fermer");
    Bouton boutonUp(NbCase * Taille + Separation, 0, NbCase * Taille + Separation + LargDroite,
                    LargDroite, Imagine::BLACK, "Up");
    Bouton boutonDown(NbCase * Taille + Separation, LargDroite + 10,
                      NbCase * Taille + Separation + LargDroite, 2 * LargDroite + 10,
                      Imagine::BLACK, "Down");
    boutonStop.affiche();
    boutonUp.affiche();
    boutonDown.affiche();
    nomBoutons.push_back("Arme");
    nomBoutons.push_back("Anneau");
    nomBoutons.push_back("Bottes");
    nomBoutons.push_back("Gants");
    nomBoutons.push_back("Jambes");
    nomBoutons.push_back("Torse");
    nomBoutons.push_back("Casque");
    nomBoutons.push_back("Objets divers");
    for (int i = 0; i < nomBoutons.size(); ++i){
        Bouton b(0, Police * i, 140, Police * (i + 1), Imagine::BLACK, nomBoutons[i]);
        boutonsChoix.push_back(b);
    }
    for (int i = 0; i < boutonsChoix.size(); ++i){
        boutonsChoix[i].affiche();
    }
    nomObjets.push_back(new Arme());
    nomObjets.push_back(new Anneau());
    nomObjets.push_back(new Bottes());
    nomObjets.push_back(new Gants());
    nomObjets.push_back(new Jambes());
    nomObjets.push_back(new Torse());
    nomObjets.push_back(new Casque());
    nomObjets.push_back(new Objet());
    int x, y;
    int decalementVertical = 0;
    clicSimple(x, y);
    while (!boutonStop.boutonActive(x, y)){
        int xmin = 180, ymin = Police, xmax = width - 100, ymax = 2 * Police;
        for (int i = 0; i < boutonsChoix.size(); ++i){
            if (boutonsChoix[i].boutonActive(x, y)){
                decalementVertical = 0;
                boutonEquipement.clear();
                equipementPresent.clear();
                for (int j = 0; j < inventaire.size(); ++j){
                    Bouton b = inventaire[j]->creeBouton(nomObjets[i], xmin, ymin, xmax, ymax);
                    if (!b.boutonVide()){
                        boutonEquipement.push_back(b);
                        equipementPresent.push_back(j);
                    }
                }
            }
        }
        if (boutonUp.boutonActive(x, y)){
            decalementVertical -= EcartementLignesInventaire;
        }
        if (boutonDown.boutonActive(x, y)){
            decalementVertical += EcartementLignesInventaire;
        }
        for (int i = 0; i < boutonEquipement.size(); ++i){
            boutonEquipement[i].affiche(decalementVertical);
        }
        for (int i = 0; i < boutonEquipement.size(); ++i){
            if (boutonEquipement[i].boutonActive(x, y, decalementVertical)){
                this->equipe(equipementPresent[i]);
                boutonEquipement[i].setNom(inventaire[equipementPresent[i]]->getNom());
                boutonEquipement[i].affiche(decalementVertical);
            }
        }
        clicSimple(x, y);
        Imagine::fillRect(180, 0, width - 100 - 180, height, Imagine::WHITE);
    }
    for (int i = 0; i < nomObjets.size(); ++i){
        delete nomObjets[i];
        nomObjets[i] = 0;
    }
}


std::string Heros::getNomCasque(){
    return equipementCasque.getNom();
}


Heros::~Heros(){
    for (int i = 0; i < inventaire.size(); ++i){
        delete inventaire[i];
        inventaire[i] = 0;
    }
}

