#include "carte.h"
#include "unite.h"
#include "joueurs.h"
#include <math.h>

TypeCase::TypeCase(const float dep, const std::string desc, const Imagine::Color img) {
    PDep = dep;
    description = desc;
    image = img;
}


TypeCase::TypeCase() {
}


Imagine::Color TypeCase::Image() const{
    return image;
}


float TypeCase::NbDep() const {
    return PDep;
}


std::string TypeCase::Description() const{
    return description;
}


bool TypeCase::popUp(const std::string question) const{
    Bouton oui(ZoneBoutonOui, Imagine::BLUE, "OUI");
    Bouton non(ZoneBoutonNon, Imagine::BLUE, "NON");
    Bouton quest(ZoneBoutonQuestion, Imagine::BLACK, question);
    quest.affiche();
    oui.affiche();
    non.affiche();
    int x, y;
    clicSimple(x, y);
    while (!(oui.boutonActive(x, y)) && !non.boutonActive(x, y)) {
        clicSimple(x, y);
    }
    if (oui.boutonActive(x, y)) {
        return true;
    }
    return false;
}


void TypeCase::action(Unite* h) {

}


TypeCase* TypeCase::clone() const {
    return new TypeCase(*this);
}


bool TypeCase::boutonChoix(){

}


CaseVille::CaseVille(const std::string desc, const Imagine::Color img, Ville* v) : TypeCase(INF, desc, img){
    ville = v;
}


CaseVille::CaseVille() : TypeCase(){

}


CaseVille* CaseVille::clone() const {
    return new CaseVille(*this);
}


void CaseVille::action(Unite* h) {
    if (this->boutonChoix()){
        ville->ouvreVille(h);
    }
}


bool CaseVille::boutonChoix(){
    return this->popUp("Voulez-vous entrer dans la ville ?");
}


CaseCombat::CaseCombat(const std::string desc, const Imagine::Color img) : TypeCase(INF, desc, img){

}


CaseCombat::CaseCombat() : TypeCase() {

}


CaseCombat* CaseCombat::clone() const {
    return new CaseCombat(*this);
}


bool CaseCombat::boutonChoix(){
    return this->popUp("Voulez-vous vous battre ?");
}


CaseNormale::CaseNormale(const float dep, const std::string desc, const Imagine::Color img) : TypeCase(dep, desc, img){

}


CaseNormale::CaseNormale() : TypeCase() {
}


CaseNormale* CaseNormale::clone() const {
    return new CaseNormale(*this);
}


Case::Case(const int x1, const int y1, TypeCase* tc) {
    x = x1;
    y = y1;
    taille = Taille;
    pointeurUnite = NULL;
    brillance = false;
    type = tc;
    utileChemin = false;
}


Case::Case() {
}


Case::Case(const Case &tuile) {
    x = tuile.x;
    y = tuile.y;
    taille = tuile.taille;
    pointeurUnite = tuile.pointeurUnite;
    brillance = tuile.brillance;
    utileChemin = utileChemin;
    type = tuile.type->clone();
}


void Case::placeUnite(Unite* u) {
    pointeurUnite = u;
}

void Case::retireUnite() {
    pointeurUnite = NULL;
}


bool Case::getOccupe() const {
    return (pointeurUnite!=NULL);
}


Unite* Case::getUnite() {
    return pointeurUnite;
}

//à se débarasser, présent uniquement dans Unite::deplaceVersCase
int Case::get(const int i) const{
    if (i == 0) {
        return x;
    }
    else {
        return y;
    }
}


void Case::brillanceOnOff(const bool flag) {
    brillance = flag;
    if (!flag) {
        utileChemin = flag;
    }
    this->affiche();
}


void Case::affiche() {
    Imagine::drawRect(x - 1, y - 1, Taille, Taille, Imagine::WHITE);
    Imagine::fillRect(x, y, Taille - 1, Taille - 1, type->Image());
    if (brillance) {
        Imagine::drawRect(x, y, Taille - 2, Taille - 2, Imagine::BLACK);
    }
    if (utileChemin) {
        Imagine::fillCircle(x + Taille / 2, y + Taille / 2, Taille / 5, Imagine::RED);
    }
    // Mini map
    int taillemax = LargDroite / NbCase;
    Imagine::fillRect(x * taillemax / Taille + Taille * NbCase + Separation, y * taillemax / Taille, taillemax,
                      taillemax, type->Image());

    //AFFICHAGE DU JOUEUR 1 EN BLEU, JOUEUR 2 EN ROUGE, A MODIFIER EN FONCTION DU NOMBRE DE JOUEURS
    if (this->getOccupe()) {
        if (this->getUnite()->getID() == 1) {
            Imagine::fillRect(x + Taille / 4, y + Taille / 4, (Taille - 1) / 2, (Taille - 1) / 2, Imagine::BLUE);
            Imagine::fillRect(x * taillemax / Taille + Taille * NbCase + Separation, y * taillemax / Taille, taillemax,
                              taillemax, Imagine::BLUE);
        }
        if (this->getUnite()->getID() == 2) {
            Imagine::fillRect(x + Taille / 4, y + Taille / 4, (Taille - 1) / 2, (Taille - 1) / 2, Imagine::RED);
            Imagine::fillRect(x * taillemax / Taille + Taille * NbCase + Separation, y * taillemax / Taille, taillemax,
                              taillemax, Imagine::RED);
        }
    }

}


float Case::NbDep() const {
    return type->NbDep();
}


bool Case::Brillance() const {
    return brillance;
}


void Case::setChemin() {
    utileChemin = !utileChemin;
}


bool Case::getChemin() const{
    return utileChemin;
}


int Case::plusProcheVoisineBrillante(const int x1, const int y1, Carte &carte, const int numcase) const{
    // Renvoie la case voisine la plus proche du point (x1, y1) qui est en brillance
    std::vector<int> numCase = casesVoisines(x1, y1);
    for (int i = 0; i < numCase.size(); ++i) {
        if (carte[numCase[i]].Brillance() || numcase == numCase[i]) {
            return numCase[i];
        }
    }
    return -1;
}


std::vector<int> Case::casesVoisines(const int x1, const int y1) const{
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


std::vector<std::vector<int> > Case::fastMarching(const float dep, Carte &carte, const bool brillance, float &dep_restant,
                                                  const int case_a_atteindre, std::vector< Imagine::Coords<2> > &vecCaseBrillante) {
    // Algorithme de FastMarching, cf cours d'Algo
    int num_case = numeroCase(x, y);
    FilePriorite<CaseDist> F;
    std::vector<int> chemin;
    std::vector<std::vector<int> > differentsChemins;
    F.push(new CaseDist(num_case, dep, chemin));
    while (!F.empty()) {
        CaseDist* c = F.pop();
        for (int i = -1; i <= 1; i = i + 2) {
            for (int j = 1; j <= NbCase; j = j + NbCase - 1) {
                if (c->getNum() + i * j >= 0 && c->getNum() + i * j < NbCase * NbCase &&
                    ((c->getNum() + i * j) % NbCase != 0 || c->getNum() % NbCase != NbCase - 1) &&
                    ((c->getNum() + i * j) % NbCase != NbCase - 1 || c->getNum() % NbCase != 0) &&
                    c->getDep() - carte[c->getNum() + i * j].NbDep() >= 0 &&
                    carte[c->getNum() + i * j].Brillance() != brillance &&
                    !carte[c->getNum() + i * j].getOccupe()) {
                    carte[c->getNum() + i * j].brillanceOnOff(brillance);
                    vecCaseBrillante.push_back(Imagine::Coords<2>((c->getNum() + i * j) % NbCase, int((c->getNum() + i * j) / NbCase)));
                    chemin = c->getChemin();
                    chemin.push_back(c->getNum() + i * j);
                    differentsChemins.push_back(chemin);
                    F.push(new CaseDist(c->getNum() + i * j, c->getDep() - carte[c->getNum() + i * j].NbDep(), chemin));
                }
                if (case_a_atteindre == c->getNum() && !brillance) {
                    dep_restant = c->getDep();
                }
            }
        }
        delete c;
    }
    return differentsChemins;
}


Imagine::Color Case::getImage() const{
    return type->Image();
}


std::string Case::getDescription() const{
    return type->Description();
}


bool Case::boutonChoix() const{
    return type->boutonChoix();
}


void Case::action(Unite* u) {
    type->action(u);
    if (this->getOccupe()) {
        // Engager phase de combat
    }
}


int energie(Imagine::Image<int> mat){
    int param=5;
    int E=0;
    int W= mat.size(0);
    int H=mat.size(1);
    int nb_case[3]= {0,0,0};
    for (int i = 0 ; i<W; i++){
        for (int j =0; j<H; j++){
            if (i>0 && mat(i-1,j)!=mat(i,j)){
                E+=param;
            }
            if (j>0 && mat(i,j-1)!=mat(i,j)){
                E+=param;
            }
            if (i<W-1 && mat(i+1,j)!=mat(i,j)){
                E+=param;
            }
            if (j<H-1 && mat(i,j+1)!=mat(i,j)){
                E+=param;
            }
            nb_case[mat(i,j)]+=1;
        }
    }
    E+= pow(nb_case[0], 2)+ pow(nb_case[1], 2)+ 8*pow(nb_case[2], 2);
    return E;
}


Imagine::Image<int> recuit_simule(int W, int H){
    srand(time(NULL));
    Imagine::Image<int> matrice(W,H);
    for (int i=0;i<W;i++){
        for (int j=0; j<H; j++ ){
            matrice(i,j)=rand() % 3;
        }
    }
    int E=energie(matrice);
    double k=1.;
    while (k<100){
        for (int n=0; n< W*H; n++){
            int new_case,i,j;
            do{
                i=rand() % W;
                j=rand() % H;
                new_case=rand() % 3;
            } while (new_case == matrice(i,j));
            Imagine::Image<int> matrice2=matrice.clone();
            matrice2(i,j)=new_case;
            int E2=energie(matrice2);
            double p =double(rand())/double(RAND_MAX);
            if (E2<E || (p< exp((E-E2)*k))){
                matrice=matrice2.clone();
                E=E2;
            }
        }
        k+=2.;
    }
    return matrice;
}



Carte::Carte(int inutilePourLInstant) {
    Imagine::Image<int> I=recuit_simule(NbCase,NbCase);
    for (int i = 0; i < NbCase * Taille; i += Taille) {
        for (int j = 0; j < NbCase * Taille; j += Taille) {
            int k = i/Taille;
            int l = j/Taille;
            if (I(k,l)==0){
                Case c(i, j, new CaseNormale(2, "Champs", Imagine::GREEN));
                carte[numeroCase(i, j)] = c;
            }
            if(I(k,l)==1){
                Case c(i, j,  new CaseNormale(1, "Route", Imagine::YELLOW));
                carte[numeroCase(i, j)] = c;
            }
            if (I(k,l)==2){
                Case c(i, j, new CaseNormale(INF, "Eau", Imagine::BLUE));
                carte[numeroCase(i, j)] = c;
            }

        }
    }
}






Carte::Carte(Ville *v) {
    // Creation de la carte
    for (int i = 0; i < NbCase * Taille; i += Taille) {
        for (int j = 0; j < NbCase * Taille; j += Taille) {
            if ((i + 1) % (j + 1) == 0) {
                Case c(i, j, new CaseNormale(INF, "Eau", Imagine::BLUE));
                carte[numeroCase(i, j)] = c;
            }
            if ((i + 1) % (j + 1) == 1) {
                Case c(i, j, new CaseNormale(2, "Champs", Imagine::GREEN));
                carte[numeroCase(i, j)] = c;
            }
            if ((i + 1) % (j + 1) > 1) {
                Case c(i, j,  new CaseNormale(1, "Route", Imagine::YELLOW));
                carte[numeroCase(i, j)] = c;
            }
        }
    }
    Case c(0, 0, new CaseVille(descVille, Imagine::MAGENTA, v));
    Case c2((NbCase - 1) * Taille, (NbCase - 1) * Taille, new CaseVille(descVille, Imagine::MAGENTA, v));
    carte[0] = c;
    carte[NbCase * NbCase - 1] = c2;
}


void Carte::affiche() {
    for (int i = 0; i < NbCase; ++i) {
        for (int j = 0; j < NbCase; ++j) {
            carte[j * NbCase + i].affiche();
        }
    }
}


Case &Carte::operator[](const int i) {
    return carte[i];
}


Case::~Case(){

}


int numeroCase(const int x, const int y) {
    if (x >= LargGauche && x < LargGauche + NbCase * Taille && y < NbCase * Taille) {
        return ((y / Taille) * NbCase + x / Taille);
    }
    return -1;
}



