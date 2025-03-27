#include "bresenham.h"
#include <cmath>

void tracer_segment_bresenham(Image& image, int x0, int y0, int x1, int y1, Couleur couleur) {
    bool pente_raide = std::abs(y1 - y0) > std::abs(x1 - x0);

    // Si la pente est raide, on échange x et y
    if (pente_raide) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    // S'assurer que l'on trace de gauche à droite
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = std::abs(y1 - y0);
    int erreur = dx / 2;
    int ystep = (y0 < y1) ? 1 : -1;
    int y = y0;

    for (int x = x0; x <= x1; ++x) {
        int px = pente_raide ? y : x;
        int py = pente_raide ? x : y;

        if (px >= 0 && px < image.largeur && py >= 0 && py < image.hauteur) {
            image.pixels[py][px] = couleur;
        }

        erreur -= dy;
        if (erreur < 0) {
            y += ystep;
            erreur += dx;
        }
    }
}
