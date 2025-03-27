#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"

int main() {
    // Créer une image 2x2
    Image img;
    img.largeur = 2;
    img.hauteur = 2;
    img.valeur_max = 255;

    // Initialiser les pixels
    img.pixels = {
        { {255, 0, 0}, {0, 255, 0} },   // ligne du haut : rouge, vert
        { {0, 0, 255}, {255, 255, 255} } // ligne du bas : bleu, blanc
    };

    // Écrire l'image dans un fichier PPM
    ecrire_image_ppm(img, "test_image.ppm");

    return 0;
}
