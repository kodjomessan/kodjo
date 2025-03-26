#include "lecteur_ppm.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <array>
Image lire_image_ppm(const std::string& nom_fichier) {
    std::ifstream fichier(nom_fichier);
    Image image;
    std::string ligne;

    if (!fichier.is_open()) {
        std::cerr << "Erreur : impossible d’ouvrir le fichier " << nom_fichier << std::endl;
        exit(1);
    }

    // Lire la ligne P3
    do {
        std::getline(fichier, ligne);
    } while (ligne[0] == '#');

    std::istringstream flux_entete(ligne);
    std::string entete;
    flux_entete >> entete;

    std::cout << "entete = " << entete << std::endl;
    if (entete != "P3") {
        std::cerr << "Erreur : format non pris en charge (doit être P3)." << std::endl;
        exit(1);
    }

    // Lire largeur, hauteur, valeur max (en ignorant les commentaires)
    int compteur = 0;
    int valeur[3] = { 0,0,0 };

    while (compteur < 3 && std::getline(fichier, ligne)) {
        // Ignorer les lignes vides ou commentaires
        if (ligne.empty() || ligne[0] == '#') continue;

        std::istringstream flux(ligne);
        while (flux >> valeur[compteur]) {
            compteur++;
            if (compteur == 3) break;
        }
    }

    int largeur = valeur[0];
    int hauteur = valeur[1];
    int val_max = valeur[2];

    if (largeur <= 0 || hauteur <= 0) {
        std::cerr << "Erreur : largeur ou hauteur invalide (valeurs <= 0)." << std::endl;
        exit(1);
    }

    std::cout << "Image lue : " << largeur << " x " << hauteur << std::endl;
    std::cout << "Valeur max : " << val_max << std::endl;

    image.largeur = largeur;
    image.hauteur = hauteur;
    image.valeur_max = val_max;

    
    // Préparer la structure pour stocker les pixels
    image.pixels.resize(image.hauteur, std::vector<Couleur>(image.largeur));

    int r = 0;
    int g = 0;
    int b = 0;
    int x = 0, y = 0;

    int idxLigne = 0;
    std::array<int, 3> troisValeurs = {0,0,0};
    while (std::getline(fichier, ligne)) {
        if (ligne.empty() || ligne[0] == '#') continue; // ignorer les commentaires

        troisValeurs[idxLigne] = stoi(ligne);
        if (idxLigne == 2) {
            idxLigne = 0;
            if (y >= image.hauteur) break; // éviter dépassement
            image.pixels[y][x] = { troisValeurs[0], troisValeurs[1], troisValeurs[2] };
            x++;
            if (x >= image.largeur) {
                x = 0;
                y++;
            }

        }else{
            troisValeurs[idxLigne] = stoi(ligne);
            idxLigne += 1;
        }
    }
    // Mise en commentaire de la partie qui posait problème 
    //while (std::getline(fichier, ligne)) {

    //    std::istringstream flux_pixels(ligne);
    //    std::cout << "ligne =" << ligne << std::endl;



    //    while (flux_pixels >> r >> g >> b) {
    //        if (y >= image.hauteur) break; // éviter dépassement
    //        image.pixels[y][x] = { r, g, b };
    //        x++;



    //        if (x >= image.largeur) {
    //            x = 0;
    //            y++;
    //        }
    //    }

    //    if (y >= image.hauteur) break;
    //}


    fichier.close();
    return image;

}

void afficheImage(const Image& img) {
    for (int i = 0; i < img.pixels.size();++i) {
        for (int j = 0; j < img.pixels[0].size();++j) {
            std::cout << img.pixels[i][j].r << "," << img.pixels[i][j].g << "," << img.pixels[i][j].b << " ";
        }
        std::cout << "\n";
    }
}
