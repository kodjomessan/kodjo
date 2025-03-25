#include "ecriture_ppm.h"
#include <fstream>
#include <iostream>

void ecrire_image_ppm(const Image& image, const std::string& nom_fichier) {
    std::ofstream fichier(nom_fichier);
    if (!fichier.is_open()) {
        std::cerr << "Erreur : impossible d’écrire dans le fichier " << nom_fichier << std::endl;
        return;
    }

    std::cout << "ecriture en cours ..." << std::endl;
    // Écrire l'en-tête
    fichier << "P3\n";
    fichier << image.largeur << " " << image.hauteur << "\n";
    fichier << image.valeur_max << "\n";

    // Écrire les pixels
    for (int y = 0; y < image.hauteur; ++y) {
        for (int x = 0; x < image.largeur; ++x) {
            Couleur pixel = image.pixels[y][x];
            std::cout << "pixel =" << image.pixels[y][x].r << "," << image.pixels[y][x].g << "," << pixel.b << " ; " << std::endl;
            fichier << pixel.r << "\n" << pixel.g << "\n" << pixel.b << "\n";
        }
        fichier << "\n";
    }

    fichier.close();
    std::cout << "Image enregistrée dans : " << nom_fichier << std::endl;
}
