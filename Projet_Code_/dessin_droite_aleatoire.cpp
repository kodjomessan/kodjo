#include "dessin_droite_aleatoire.h"
#include <cmath>


Image dessiner_droites_aleatoires(const std::vector<Droite>& droites, const Image& image, int seuil) {
    Image copie = image;

    for (size_t i = 0; i < droites.size(); ++i) {
        if (droites[i].votes < seuil) continue;

        double m = droites[i].m;
        double b = droites[i].b;

        for (int x = 0; x < copie.largeur; ++x) {
            int y = static_cast<int>(std::round(m * x + b));
            if (y >= 0 && y < copie.hauteur) {
                copie.pixels[y][x] = { 255, 0, 0 };  // Rouge
            }
        }
    }

    return copie;
}
