#include "ecriture_ppm.h"
#include <fstream>
#include <iostream>

// Fonction pour �crire une image au format PPM (type P3)
void ecrire_image_ppm(const Image& image, const std::string& nom_fichier) {
    // Ouverture du fichier en ecriture 
    std::ofstream fichier(nom_fichier);
    if (!fichier.is_open()) {
        std::cerr << "Erreur : impossible d ecrire dans le fichier " << nom_fichier << std::endl;
        return;
    }

    std::cout << "ecriture en cours ..." << std::endl;

    // === �TAPE 1 : �crire l'en-t�te du fichier PPM ===
    fichier << "P3\n"; // P3 indique qu'on �crit une image en ASCII (et non binaire)
    fichier << image.largeur << " " << image.hauteur << "\n"; // dimensions de l'image
    fichier << image.valeur_max << "\n"; // valeur maximale pour les couleurs (ex : 255)

    // === �TAPE 2 : �crire les donn�es de chaque pixel ===
    for (int y = 0; y < image.hauteur; ++y) {
        for (int x = 0; x < image.largeur; ++x) {
            Couleur pixel = image.pixels[y][x]; // R�cup�ration du pixel (x, y)

            // Affichage dans la console pour suivi/debug
            std::cout << "pixel = " << pixel.r << "," << pixel.g << "," << pixel.b << " ; " << std::endl;

            // �criture des trois composantes du pixel dans le fichier (une par ligne)
            fichier << pixel.r << "\n" << pixel.g << "\n" << pixel.b << "\n";
        }
        fichier << "\n"; // Retour � la ligne apr�s chaque ligne de pixels
    }

    // Fermeture du fichier
    fichier.close();
    std::cout << "Image enregistree dans : " << nom_fichier << std::endl;
}
