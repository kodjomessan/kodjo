#include "utils_image.h"
#include "lecteur_ppm.h"  // pour Image et Couleur
#include <vector>

std::vector<std::pair<int, int>> extraire_pixels_blancs(const Image& image_binaire) {
    std::vector<std::pair<int, int>> points;

    for (int y = 0; y < image_binaire.hauteur; ++y) {
        for (int x = 0; x < image_binaire.largeur; ++x) {
            Couleur c = image_binaire.pixels[y][x];

            if (c.r == 255 && c.g == 255 && c.b == 255) {
                points.emplace_back(x, y);
            }
        }
    }

    return points;
}
