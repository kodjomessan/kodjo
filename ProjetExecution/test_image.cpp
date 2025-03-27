#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"

int main() {
    // Lire une image depuis un fichier PPM
    Image image = lire_image_ppm("imgTresSimple.ppm");

    // Afficher quelques infos de vérification
    std::cout << "Largeur : " << image.largeur << std::endl;
    std::cout << "Hauteur : " << image.hauteur << std::endl;
    std::cout << "Valeur max : " << image.valeur_max << std::endl;

    afficheImage(image);

    //// Écrire cette image dans un nouveau fichier
    ecrire_image_ppm(image, "copie_image.ppm");

    return 0;
}
