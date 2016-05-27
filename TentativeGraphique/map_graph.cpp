#include"map_graph.h"
#include "joueurs.h"

//Constructeur par défaut.
Case_Graph::Case_Graph() {
    nom = "Vide";
}

//Assesseur en lecture de l'attribut nom.
std::string Case_Graph::get_nom() {
    return nom;
}

//Assesseur en lecture de l'attribut description.
std::string Case_Graph::get_description() {
    return description;
}

//Assesseur en lecture de l'attribut nom_image.
std::string Case_Graph::get_nom_image() {
    return nom_image;
}

//Assesseur en écriture de l'attribut nom.
void Case_Graph::set_nom(std::string nom_voulu) {

    nom = nom_voulu;

}

//Assesseur en écriture de l'attribut description.
void Case_Graph::set_description(std::string description_voulue) {
    description = description_voulue;
}

//Assesseur en écriture de l'attribut nom_image.
void Case_Graph::set_nom_image(std::string nom_image_voulue) {
    nom_image = std::string(nom_image_voulue);
}

//Assesseur en écriture de l'attribut frame.
void Case_Graph::set_frame(std::string nom_image_voulue) {
    if (std::string(nom_image_voulue) == std::string("foret1")) {
        frame = foret1;
    }
    if (std::string(nom_image_voulue) == std::string("eau1")) {
        frame = eau1;
    }
    if (std::string(nom_image_voulue) == std::string("lande1")) {
        frame = lande1;
    }
}

//Méthode qui modifie l'intégralité des paramètres de la case.
void Case_Graph::set_Case_Graph(std::string nom_voulu, std::string description_voulue, std::string nom_image_voulue) {
    set_nom(nom_voulu);
    set_description(description_voulue);
    set_nom_image(nom_image_voulue);
    set_frame(nom_image_voulue);

}

void Case_Graph::affiche(int num, CarteduMonde carte) const{
    int xp = ((num / widthmap) - carte.get_pos_centre()[0]) * taille_case_graph + widthworld / 2;
    int yp = ((num % widthmap) - carte.get_pos_centre()[1]) * taille_case_graph + heightworld / 2;
    Imagine::display(frame, xp, yp);
    Imagine::drawRect(xp, yp, taille_case_graph, taille_case_graph, gris, 1);
}

TypeCase::TypeCase(const float dep, const std::string desc) {
    PDep = dep;
    description = desc;
}


TypeCase::TypeCase() {
}

void TypeCase::affiche(int num, CarteduMonde carte) const{
    /*
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
    if (this->getOccupe()) {
        Imagine::fillRect(x + Taille / 4, y + Taille / 4, (Taille - 1) / 2, (Taille - 1) / 2, Imagine::BLACK);
        Imagine::fillRect(x * taillemax / Taille + Taille * NbCase + Separation, y * taillemax / Taille, taillemax,
                          taillemax, Imagine::BLACK);
    }
    */
    case_aff.affiche(num, carte);
}

//Assesseur en écriture de l'attribut case_aff.
void TypeCase::set_case_aff(std::string nom_voulu, std::string description_voulue, std::string name){
    case_aff.set_Case_Graph(nom_voulu, description_voulue, name);
}

//Assesseur en lecture de l'attribute case_aff.
Case_Graph TypeCase::get_case_aff(){
    return case_aff;
}

float TypeCase::NbDep() const {
    return PDep;
}


std::string TypeCase::Description() const{
    return description;
}


bool TypeCase::popUp(const std::string question) const{/*
    Bouton oui(ZoneBoutonOui, "OUI", 0);
    Bouton non(ZoneBoutonNon, "NON", 0);
    Bouton quest(ZoneBoutonQuestion, question, 0);
    quest.affiche_graph();
    oui.affiche_graph();
    non.affiche_graph();
    int x, y;
    clicSimple(x, y);
    while (!(oui.boutonActive(x, y)) && !non.boutonActive(x, y)) {
        clicSimple(x, y);
    }
    if (oui.boutonActive(x, y)) {
        return true;
    }*/
    return false;
}


void TypeCase::action(Unite* h) {

}


TypeCase* TypeCase::clone() const {
    return new TypeCase(*this);
}


bool TypeCase::boutonChoix(){

}


CaseVille::CaseVille(const std::string desc, Ville* v, int camp) : TypeCase(INF, desc){
    if (camp == 1){
        set_case_aff("Ville Bleue", std::string("Une ville de qualité des bleus"), "villebleue");
    }
    if (camp == 2){
        set_case_aff("Ville Rouge", std::string("Une ville de qualité des rouges"), "villerouge");
    }
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


CaseCombat::CaseCombat(const std::string desc, std::string nom) : TypeCase(INF, desc){
    if (std::string(nom) == "Etendue d'Eau"){
        set_case_aff("Etendue d'Eau", "De l'eau, sans vie, sans poisson, rien que de l'eau", "eau1");
    }
    if (std::string(nom) == "Foret"){
        set_case_aff("Foret", "C'est vert, les souris s'y cachent, c'est UNE FORET", "foret1");
    }
    if (std::string(nom) == "Lande"){
        set_case_aff("Lande", "Les choses les plus chiantes du monde...", "lande1");
    }
}


CaseCombat::CaseCombat() : TypeCase() {

}


CaseCombat* CaseCombat::clone() const {
    return new CaseCombat(*this);
}


bool CaseCombat::boutonChoix(){
    return this->popUp("Voulez-vous vous battre ?");
}


CaseNormale::CaseNormale(const float dep, const std::string desc, std::string nom) : TypeCase(dep, desc){
    if (std::string(nom) == "Etendue d'Eau"){
        set_case_aff("Etendue d'Eau", "De l'eau, sans vie, sans poisson, rien que de l'eau", "eau1");
    }
    if (std::string(nom) == "Foret"){
        set_case_aff("Foret", "C'est vert, les souris s'y cachent, c'est UNE FORET", "foret1");
    }
    if (std::string(nom) == "Lande"){
        set_case_aff("Lande", "Les choses les plus chiantes du monde...", "lande1");
    }
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

//Assesseur en lecture du nom de l'image, attribut de case_aff.
std::string Case::get_nom_image(){
    return type->get_case_aff().get_nom_image();
}

//Assesseur en lecture du nom de l'image, attribut de case_aff.
std::string Case::get_nom(){
    return type->get_case_aff().get_nom();
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

//Set la case.
void Case::set_case_aff(std::string nom_voulu, std::string description_voulue, std::string name){
    type->set_case_aff(nom_voulu, description_voulue, name);
}

void Case::flagHeros(Unite* u) {
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


void Case::brillanceOnOff(const bool flag, Imagine::Coords<2> pos_centre) {
    Imagine::Coords<2> pos_world(widthworld / 2, heightworld / 2);
    Imagine::Coords<2> pos_case(x, y);
    pos_case = pos_world + pos_case - pos_centre * taille_case_graph;
    brillance = flag;
    if (!flag) {
        utileChemin = flag;
        if ((pos_world + pos_case * taille_case_graph)[0] > 0 && (pos_world + pos_case * taille_case_graph)[1] > 0 &&
            (pos_world + pos_case * taille_case_graph)[0] < widthworld &&
            (pos_world + pos_case * taille_case_graph)[1] < heightworld) {
            Imagine::drawRect(pos_case, taille_case_graph, taille_case_graph, gris);
        }
    }
        /*
        this->affiche();
         */
    else {
        if ((pos_world + pos_case * taille_case_graph)[0] > 0 && (pos_world + pos_case * taille_case_graph)[1] > 0 &&
            (pos_world + pos_case * taille_case_graph)[0] < widthworld &&
            (pos_world + pos_case * taille_case_graph)[1] < heightworld) {
            Imagine::drawRect(pos_case, taille_case_graph, taille_case_graph, Imagine::RED);
        }
    }
}





//Affiche les chemins et la surbrillance.
void Case::affiche_chemin(){
    if (brillance && !utileChemin) {
        Imagine::drawRect(x, y, taille_case_graph, taille_case_graph, Imagine::BLACK);
    }
    if (utileChemin) {
        Imagine::drawRect(x, y , taille_case_graph, taille_case_graph, Imagine::RED);
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


int Case::plusProcheVoisineBrillante(const int x1, const int y1, CarteduMonde &carte, const int numcase) const{
    // Renvoie la case voisine la plus proche du point (x1, y1) qui est en brillance
    std::vector<int> numCase = casesVoisines(x1, y1, carte);
    for (int i = 0; i < numCase.size(); ++i) {
        if (carte[numCase[i]].Brillance() || numcase == numCase[i]) {
            return numCase[i];
        }
    }
    return -1;
}


std::vector<int> Case::casesVoisines(const int x1, const int y1, CarteduMonde &carte) const{
    std::vector<int> numCase;
    std::vector<int> priorite;
    // On cherche autour de notre case les cases qui sont accessibles
    if (numeroCase(x, y, carte.get_pos_centre()) % NbCase != NbCase - 1) {
        numCase.push_back(numeroCase(x, y, carte.get_pos_centre()) + 1);
        priorite.push_back(x + Taille - x1);
    }
    if (numeroCase(x, y, carte.get_pos_centre()) % NbCase != 0) {
        numCase.push_back(numeroCase(x, y, carte.get_pos_centre()) - 1);
        priorite.push_back(x1 - x);
    }
    if (numeroCase(x, y, carte.get_pos_centre()) >= NbCase) {
        numCase.push_back(numeroCase(x, y, carte.get_pos_centre()) - NbCase);
        priorite.push_back(y1 - y);
    }
    if (numeroCase(x, y, carte.get_pos_centre()) < NbCase * (NbCase - 1)) {
        numCase.push_back(numeroCase(x, y, carte.get_pos_centre()) + NbCase);
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


std::vector<std::vector<int> > Case::fastMarching(const float dep, CarteduMonde &carte, const bool brillance, float &dep_restant,
                                                  const int case_a_atteindre) {
    // Algorithme de FastMarching, cf cours d'Algo
    int num_case = numeroCase(x, y, carte.get_pos_centre());
    FilePriorite<CaseDist> F;
    std::vector<int> chemin;
    std::vector<std::vector<int> > differentsChemins;
    F.push(new CaseDist(num_case, dep, chemin));
    std::cout<<num_case<<std::endl;
    while (!F.empty()) {
        CaseDist* c = F.pop();
        for (int i = -1; i <= 1; i = i + 2) {
            for (int j = 1; j <= NbCase; j = j + NbCase - 1) {
                std::cerr<<"test6"<<" / "<<NbCase<<"  /i "<<c->getNum()<<std::endl;
                if (c->getNum() + i * j >= 0 && c->getNum() + i * j < NbCase * NbCase &&
                    ((c->getNum() + i * j) % NbCase != 0 || c->getNum() % NbCase != NbCase - 1) &&
                    ((c->getNum() + i * j) % NbCase != NbCase - 1 || c->getNum() % NbCase != 0) &&
                    c->getDep() - carte[c->getNum() + i * j].NbDep() >= 0 &&
                    carte[c->getNum() + i * j].Brillance() != brillance &&
                    !carte[c->getNum() + i * j].getOccupe()) {
                    carte[c->getNum() + i * j].brillanceOnOff(brillance, carte.get_pos_centre());
                    std::cerr<<"test5";
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

/*
Imagine::Color Case::getImage() const{
    return type->Image();
}
 */

// Affiche la case
void Case::affiche(CarteduMonde carte) const{
    int num = numeroCase(x, y, carte.get_pos_centre());
    type->affiche(num, carte);
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

Case::~Case(){

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


/*
Carte::Carte(int inutilePourLInstant) {
    Imagine::Image<int> I=recuit_simule(NbCase,NbCase);
    for (int i = 0; i < NbCase * Taille; i += Taille) {
        for (int j = 0; j < NbCase * Taille; j += Taille) {
            int k = i/Taille;
            int l = j/Taille;
            if (I(k,l)==0){
                Case c(i, j, new CaseNormale(2, "C'est vert, les souris s'y cachent, c'est de l'herbe", Imagine::GREEN));
                carte[numeroCase(i, j)] = c;
            }
            if(I(k,l)==1){
                Case c(i, j,  new CaseNormale(1, "Une case a moindre cout de deplacement", Imagine::YELLOW));
                carte[numeroCase(i, j)] = c;
            }
            if (I(k,l)==2){
                Case c(i, j, new CaseNormale(INF, "De l'eau, sans vie, sans poisson, rien que de l'eau", Imagine::BLUE));
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
                Case c(i, j, new CaseNormale(INF, "De l'eau, sans vie, sans poisson, rien que de l'eau", Imagine::BLUE));
                carte[numeroCase(i, j)] = c;
            }
            if ((i + 1) % (j + 1) == 1) {
                Case c(i, j, new CaseNormale(2, "C'est vert, les souris s'y cachent, c'est de l'herbe", Imagine::GREEN));
                carte[numeroCase(i, j)] = c;
            }
            if ((i + 1) % (j + 1) > 1) {
                Case c(i, j,  new CaseNormale(1, "Une case a moindre cout de deplacement", Imagine::YELLOW));
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
*/

int numeroCase(const int x, const int y, Imagine::Coords<2> pos_centre) {
    Imagine::Coords<2> pos_case;
    Imagine::Coords<2> xy(x, y);
    pos_case = (xy / taille_case_graph);
    if (x >= 0 && x <widthworld && y >= 0 && y <heightworld) {
        return ((pos_case[1]) * width_nombre_case_world + pos_case[0]);
    }
    return -1;
}
//Fonction qui renvoie true si le point est dans la 'mmap' et false sinon.
bool dans_mmap(Imagine::Coords<2> point) {
    return dans_mmap(point[0], point[1]);
}

//Fonction qui renvoie true si le point est dans la 'mmap' et false sinon.
bool dans_mmap(int x, int y) {
    if (x > widthworld + 2 && x < widthworld + widthmmap && y > 2 && y < heightmmap + 2) {
        return true;
    }
    else {
        return false;
    }
}

//Constructeur par défaut.
CarteduMonde::CarteduMonde() : listecase(widthmap, heightmap),
                               image_map(widthmap * taille_case_graph, heightmap * taille_case_graph),
                               image_mmap(widthmap * taille_case_mmap +
                                          (width_nombre_case_mmap - width_nombre_case_world),
                                          heightmap * taille_case_mmap +
                                          (height_nombre_case_mmap - height_nombre_case_world)) {
    pos_centre = (widthmap / 2, heightmap / 2);
    generation();
    cree_map_mmap();
}

CarteduMonde::CarteduMonde(int inutile) : listecase(widthmap, heightmap),
                                          image_map(widthmap * taille_case_graph, heightmap * taille_case_graph),
                                          image_mmap(widthmap * taille_case_mmap +
                                                     (width_nombre_case_mmap - width_nombre_case_world),
                                                     heightmap * taille_case_mmap +
                                                     (height_nombre_case_mmap - height_nombre_case_world)) {
    pos_centre = (widthmap / 2, heightmap / 2);

    generation();

    cree_map_mmap();

}

//Générateur de 'map'. Rempli listecase.
void CarteduMonde::generation() {
    // Pour le moment crée de manière simple la map.
    for (int i = 0; i < widthmap; i++) {
        for (int j = 0; j < heightmap; j++) {
            if (i == j) {
                Case c(i, j, new CaseNormale(INF, "De l'eau, sans vie, sans poisson, rien que de l'eau", "Etendue d'Eau"));
                listecase(i, j) = c;
            }
            else {
                if (i < 20) {
                    Case c(i, j, new CaseNormale(2, "C'est vert, les souris s'y cachent, c'est UNE FORET", "Foret"));
                    listecase(i, j) = c;
                }
                else {
                    Case c(i, j, new CaseNormale(1, "Les choses les plus chiantes du monde...", "Lande"));
                    listecase(i, j) = c;
                }
            }
        }
    }
    /*

    listecase(widthmap / 2, heightmap / 2).set_case_aff("Ville Bleue", "Le doux foyer des gentils bleus",
                                                        "villebleue");

    listecase(widthmap / 4, heightmap / 5).set_case_aff("Ville Rouge", "Le doux foyer des méchants rouges",
                                                        "villerouge");
                                                        */
}

//Rempli image_map et image mmap en fonction de la listecase.
void CarteduMonde::cree_map_mmap() {

    image_mmap.fill(Imagine::BLACK);


    std::string nom_image_voulue;   //Nom de l'image courant.
    std::string nom_voulue; //Nom de la case courant.
    Imagine::Image<Imagine::Color> frame_voulue;    //Frame courante.
    Imagine::Color couleur_voulue;  //Couleur courante.

    for (int i = 0; i < widthmap; i++) {
        for (int j = 0; j < heightmap; j++) {

            nom_image_voulue = listecase(i, j).get_nom_image();
            frame_voulue = entre_image_case(nom_image_voulue);
            nom_voulue = listecase(i, j).get_nom();
            couleur_voulue = entre_couleur_case(nom_voulue);
            //Travail sur 'map'.
            for (int k = 0; k < taille_case_graph; k++) {
                for (int l = 0; l < taille_case_graph; l++) {
                    image_map(i * taille_case_graph + k, j * taille_case_graph + l) = frame_voulue(k, l);
                }
            }
            //Travail sur 'mmap'.
            for (int k = 0; k < taille_case_mmap; k++) {
                for (int l = 0; l < taille_case_mmap; l++) {
                    image_mmap(i * taille_case_mmap + k + (width_nombre_case_mmap - width_nombre_case_world) / 2,
                               j * taille_case_mmap + l +
                               (height_nombre_case_mmap - height_nombre_case_world) / 2) = couleur_voulue;
                }
            }

        }
    }

}


//Assesseur en lecture de la position du centre.
Imagine::Coords<2> CarteduMonde::get_pos_centre() {
    return pos_centre;
}

//Assesseur en lecture de l'attribut listecase, renvoie la case de coordonnée pos_lue. Prend des Coords en argument.
Case CarteduMonde::get_case(Imagine::Coords<2> pos_lue) {
    return get_case(pos_lue[0], pos_lue[1]);
}

//Assesseur en lecture de l'attribut listecase, renvoie la case de coordonnée x, y. Prend des int en argument.
Case& CarteduMonde::get_case(int x, int y) {
    return listecase[x, y];
}

// Permer d'accéder à carte[i]
Case &CarteduMonde::operator[](const int i) {
    return listecase[i % widthmap, int(i / widthmap)];
}

//Méthode qui affiche la carte dans le 'world' et la minimap sur la 'mmap'.
void CarteduMonde::affiche(std::vector<Unite*> unite1, std::vector<Unite*> unite2) {
    int bord_gauche = pos_centre[0] - width_nombre_case_world / 2;    //En case. Défini le bord gauche du 'world'.
    int bord_droit = pos_centre[0] + width_nombre_case_world / 2;    //En case. Défini le bord droite du 'world'.
    int bord_haut = pos_centre[1] - height_nombre_case_world / 2;    //En case. Défini le bord gauche du 'world'.
    int bord_bas = pos_centre[1] + height_nombre_case_world / 2;    //En case. Défini le bord gauche du 'world'.

    int bord_gauche_graph = bord_gauche * taille_case_graph;    //En pixel. Défini le bord gauche du 'world'.
    int bord_droit_graph = bord_droit * taille_case_graph;    //En pixel. Défini le bord droite du 'world'.
    int bord_haut_graph = bord_haut * taille_case_graph;    //En pixel. Défini le bord gauche du 'world'.
    int bord_bas_graph = bord_bas * taille_case_graph;    //En pixel. Défini le bord gauche du 'world'.

    int bord_gauche_mmap = bord_gauche * taille_case_mmap;    //En pixel. Défini le bord gauche du 'world'.
    int bord_droit_mmap = bord_droit * taille_case_mmap;    //En pixel. Défini le bord droite du 'world'.
    int bord_haut_mmap = bord_haut * taille_case_mmap;    //En pixel. Défini le bord gauche du 'world'.
    int bord_bas_mmap = bord_bas * taille_case_mmap;    //En pixel. Défini le bord gauche du 'world'.

    //Affichage du 'world'.
    assert(bord_droit - widthmap <= 0);   //Le bord droit du 'world' est dans la 'map'.
    assert(bord_bas - heightmap <= 0);  //Le bord bas du 'world' est dans la 'map'.
    assert(bord_gauche >= 0);    //Le bord gauche du 'world' est dans la 'map'.
    assert(bord_haut >= 0);   //Le bord haut du 'world' est dans la 'map'.

    //Affichage du 'world'.
    Imagine::Image<Imagine::Color> world_affiche;
    world_affiche = image_map.getSubImage(bord_gauche_graph, bord_haut_graph, widthworld, heightworld);
    Imagine::display(world_affiche, 0, 0);

    //Affichage de l'encadrement des cases.
    for (int j = 0; j < height_nombre_case_world; j++) {
        Imagine::drawLine(0, j * taille_case_graph, widthworld, j * taille_case_graph, gris);
    }
    for (int i = 0; i < width_nombre_case_world; i++) {
        Imagine::drawLine(i * taille_case_graph, 0, i * taille_case_graph, heightworld, gris);
    }


    //Affichage de la 'mmap'.
    Imagine::Image<Imagine::Color> mmap_affiche;
    mmap_affiche = image_mmap.getSubImage(bord_gauche_mmap, bord_haut_mmap, widthmmap, heightmmap);
    Imagine::display(mmap_affiche, widthworld + (widthui - widthmmap) / 2, (widthui - widthmmap) / 2);

    //Encadrement de la zone correspondant au 'world' dans 'mmap'.
    Imagine::drawRect(
            widthworld + (widthui - widthmmap) / 2 + (widthmmap - width_nombre_case_world * taille_case_mmap) / 2 - 1,
            (widthui - widthmmap) / 2 + (widthmmap - width_nombre_case_world * taille_case_mmap) / 2 - 1,
            width_nombre_case_world * taille_case_mmap + 2, height_nombre_case_world * taille_case_mmap + 2,
            Imagine::BLACK);
    for (int i = 0; i < unite1.size(); i++){
        unite1[i]->affiche_unite(get_pos_centre());
    }
    for (int i = 0; i < unite2.size(); i++){
        unite2[i]->affiche_unite(get_pos_centre());
    }

}

/*
//Méthode qui décale l'affichage selon la directio dir voulue.
void CarteduMonde::deplace_clavier(int dir) {
    if (dir == Imagine::KEY_UP && pos_centre[1] - height_nombre_case_world / 2 > 0) {
        pos_centre[1] -= 1;
        affiche();
    }
    if (dir == Imagine::KEY_DOWN &&
        pos_centre[1] + height_nombre_case_world / 2 - heightmap < 0) {
        pos_centre[1] += 1;
        affiche();
    }
    if (dir == Imagine::KEY_LEFT && pos_centre[0] - width_nombre_case_world / 2 > 0) {
        pos_centre[0] -= 1;
        affiche();
    }
    if (dir == Imagine::KEY_RIGHT &&
        pos_centre[0] + width_nombre_case_world / 2 - widthmap < 0) {
        pos_centre[0] += 1;
        affiche();
    }
}*/

//Méthode qui place pos_centre au coordonnée voulue et réaffiche le 'world' et la 'mmap'. Prend des Coords en argument pour déterminer la position voulue.
void CarteduMonde::deplace_souris(Imagine::Coords<2> pos_voulue, std::vector<Unite*> unite1, std::vector<Unite*> unite2) {
    deplace_souris(pos_voulue[0], pos_voulue[1], unite1, unite2);
}

//Méthode qui place pos_centre au coordonnée voulue et réaffiche le 'world' et la 'mmap'. Prend des int en argument pour déterminer la position voulue.
void CarteduMonde::deplace_souris(int x, int y, std::vector<Unite*> unite1, std::vector<Unite*> unite2) {
    if (y - height_nombre_case_world / 2 < 0) {
        y = height_nombre_case_world / 2;
    }
    if (y + height_nombre_case_world / 2 - heightmap > 0) {
        y = heightmap - height_nombre_case_world / 2;
    }
    if (x - width_nombre_case_world / 2 < 0) {
        x = width_nombre_case_world / 2;
    }
    if (x + width_nombre_case_world / 2 - widthmap > 0) {
        x = widthmap - width_nombre_case_world / 2;
    }
    pos_centre[0] = x;
    pos_centre[1] = y;
    affiche(unite1, unite2);
}