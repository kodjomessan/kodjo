#include "traitement_image.h"
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include <vector>
#include <iostream>

int main() {
    // Lire l'image à tester
    Image mon_image = lire_image_ppm("imgTresSimple.ppm");

    std::cout << "Image lue : " << mon_image.largeur << " x " << mon_image.hauteur << std::endl;
    std::cout << "Valeur max : " << mon_image.valeur_max << std::endl;

    // Convertir l'image en niveaux de gris
    convertir_en_niveaux_de_gris(mon_image);
    ecrire_image_ppm(mon_image, "image_gris.ppm");

    // Détecter les contours avec Sobel
    Image image_contours;
    detecter_contours_sobel(mon_image, image_contours, 100);  // seuil de 100
    ecrire_image_ppm(image_contours, "image_contours.ppm");

    std::cout << "Traitement effectué et images sauvegardées." << std::endl;

    return 0;
}
