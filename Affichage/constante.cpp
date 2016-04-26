#include "constante.h"

Imagine::Image<Imagine::Color> foret1;
Imagine::Image<Imagine::Color> eau1;
Imagine::Image<Imagine::Color> lande1;

bool charge_image() {
    if (!Imagine::load(foret1, srcPath("forest_texture.jpg"))) {
        std::cout << "Image \"forest_texture.jpg\" non trouvée." << std::endl;
        return false;
    }
    foret1 = foret1.getSubImage(0, 0, taille_case, taille_case);

    if (!Imagine::load(eau1, srcPath("water_texture.jpg"))) {
        std::cout << "Image \"water_texture.jpg\" non trouvée." << std::endl;
        return false;
    }
    eau1 = eau1.getSubImage(0, 0, taille_case, taille_case);

    if (!Imagine::load(lande1, srcPath("moor_texture.jpg"))) {
        std::cout << "Image \"moor_texture.jpg\" non trouvée." << std::endl;
        return false;
    }
    lande1 = lande1.getSubImage(0, 0, taille_case, taille_case);


    std::cout << "Toutes les images sont chargées" << std::endl;
    return true;
}