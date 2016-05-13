#include "constante.h"

Imagine::Image<Imagine::Color> fond_ecran;
Imagine::Image<Imagine::Color> parchemin;

Imagine::Image<Imagine::Color> foret1;
Imagine::Image<Imagine::Color> eau1;
Imagine::Image<Imagine::Color> lande1;

//Fonction qui charge toutes les frames dans leur variables et vérifie qu'il n'y a pas d'erreur. Adapte également l'image à taille_case_graph.
bool charge_image() {
    if (!Imagine::load(fond_ecran, srcPath("/Image/Fond_ecran/Clair/fond7.jpg"))) {
        std::cout << "Image \"fond7.jpg\" non trouvée." << std::endl;
        return false;
    }
    fond_ecran = fond_ecran.getSubImage(0, 0, widthscreen, heightscreen);

    if (!Imagine::load(parchemin, srcPath("/Image/Parchemin/fondetparchemin.jpg"))) {
        std::cout << "Image \"fondetparchemin.jpg\" non trouvée." << std::endl;
        return false;
    }


    if (!Imagine::load(foret1, srcPath("Image/Foret/forest_texture.jpg"))) {
        std::cout << "Image \"forest_texture.jpg\" non trouvée." << std::endl;
        return false;
    }
    foret1 = foret1.getSubImage(0, 0, taille_case_graph, taille_case_graph);

    if (!Imagine::load(eau1, srcPath("Image/Eau/water_texture.jpg"))) {
        std::cout << "Image \"water_texture.jpg\" non trouvée." << std::endl;
        return false;
    }
    eau1 = eau1.getSubImage(0, 0, taille_case_graph, taille_case_graph);

    if (!Imagine::load(lande1, srcPath("Image/Lande/moor_texture.jpg"))) {
        std::cout << "Image \"moor_texture.jpg\" non trouvée." << std::endl;
        return false;
    }
    lande1 = lande1.getSubImage(0, 0, taille_case_graph, taille_case_graph);


    std::cout << "Toutes les images sont chargées" << std::endl;
    return true;
}