#include "dessin_droite.h"
#include <cmath>

Image dessiner_droites_naives(const HoughNaif& hough, Image image, int seuil) {
    Couleur rouge = { 255, 0, 0 };

    for (int i = 0; i < hough.nb_m; ++i) {
        for (int j = 0; j < hough.nb_b; ++j) {
            if (hough.accumulateur[i][j] >= seuil) {
                double m = hough.m_min + i * hough.pas_m;
                double b = hough.b_min + j * hough.pas_b;

                for (int x = 0; x < image.largeur; ++x) {
                    int y = static_cast<int>(std::round(m * x + b));

                    if (y >= 0 && y < image.hauteur) {
                        image.pixels[y][x] = rouge;
                    }
                }
            }
        }
    }

    return image;
}
