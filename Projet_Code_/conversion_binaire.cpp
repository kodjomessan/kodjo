#include "conversion_binaire.h"

Image convertir_en_binaire(const Image& image_entree, int seuil) {
    Image image_sortie;
    image_sortie.largeur = image_entree.largeur;
    image_sortie.hauteur = image_entree.hauteur;
    image_sortie.valeur_max = image_entree.valeur_max;
    image_sortie.pixels.resize(image_sortie.hauteur, std::vector<Couleur>(image_sortie.largeur));

    for (int y = 0; y < image_entree.hauteur; ++y) {
        for (int x = 0; x < image_entree.largeur; ++x) {
            Couleur pixel = image_entree.pixels[y][x];
            int gris = static_cast<int>(0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b);

            if (gris < seuil) {
                image_sortie.pixels[y][x] = { 0, 0, 0 };       // noir
            }
            else {
                image_sortie.pixels[y][x] = { 255, 255, 255 }; // blanc
            }
        }
    }

    return image_sortie;
}
