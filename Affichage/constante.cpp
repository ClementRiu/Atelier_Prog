#include "constante.h"

Imagine::Image<Imagine::Color> foret1;
Imagine::Image<Imagine::Color> eau1;
Imagine::Image<Imagine::Color> lande1;

//Fonction qui charge toutes les frames dans leur variables et vérifie qu'il n'y a pas d'erreur. Adapte également l'image à taille_case_graph.
bool charge_image() {
    if (!Imagine::load(foret1, srcPath("forest_texture.jpg"))) {
        std::cout << "Image \"forest_texture.jpg\" non trouvée." << std::endl;
        return false;
    }
    foret1 = foret1.getSubImage(0, 0, taille_case_graph, taille_case_graph);

    if (!Imagine::load(eau1, srcPath("water_texture.jpg"))) {
        std::cout << "Image \"water_texture.jpg\" non trouvée." << std::endl;
        return false;
    }
    eau1 = eau1.getSubImage(0, 0, taille_case_graph, taille_case_graph);

    if (!Imagine::load(lande1, srcPath("moor_texture.jpg"))) {
        std::cout << "Image \"moor_texture.jpg\" non trouvée." << std::endl;
        return false;
    }
    lande1 = lande1.getSubImage(0, 0, taille_case_graph, taille_case_graph);


    std::cout << "Toutes les images sont chargées" << std::endl;
    return true;
}