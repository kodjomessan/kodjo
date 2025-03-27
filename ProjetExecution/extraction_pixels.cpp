#include "lecteur_ppm.h"
#include <vector>

// Fonction qui extrait tous les pixels blancs d'une image binaire.
// Elle retourne un vecteur contenant les coordonn�es (x, y) de chaque pixel blanc.
std::vector<std::pair<int, int>> extraire_pixels_blancs(const Image& image_binaire) {
    // Vecteur pour stocker les coordonn�es des pixels blancs
    std::vector<std::pair<int, int>> pixels_blancs;

    // Parcours des lignes de l'image (axe y)
    for (int y = 0; y < image_binaire.hauteur; ++y) {
        // Parcours des colonnes de l'image (axe x)
        for (int x = 0; x < image_binaire.largeur; ++x) {
            // R�cup�ration de la couleur du pixel � la position (x, y)
            Couleur pixel = image_binaire.pixels[y][x];

            // V�rifie si le pixel est blanc (toutes les composantes valent 255)
            if (pixel.r == 255 && pixel.g == 255 && pixel.b == 255) {
                // Ajout des coordonn�es du pixel dans la liste
                pixels_blancs.emplace_back(x, y);
            }
        }
    }

    // Retourne la liste des coordonn�es des pixels blancs
    return pixels_blancs;
}
