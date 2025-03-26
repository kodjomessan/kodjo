#include "dessin_droite_polaire.h"
#include <cmath>

const Couleur ROUGE = { 255, 0, 0 };

Image dessiner_droites_polaire(const HoughPolaire& hough, const Image& image_binaire, int seuil) {
    Image resultat = image_binaire;

    for (int i = 0; i < hough.nb_theta; ++i) {
        for (int j = 0; j < hough.nb_rho; ++j) {
            int votes = hough.accumulateur[i][j];

            if (votes >= seuil) {
                double theta = hough.theta_min + i * hough.pas_theta;
                double rho = hough.rho_min + j * hough.pas_rho;

                for (int x = 0; x < resultat.largeur; ++x) {
                    int y = static_cast<int>(std::round((rho - x * std::cos(theta)) / std::sin(theta)));

                    if (y >= 0 && y < resultat.hauteur) {
                        resultat.pixels[y][x] = ROUGE;
                    }
                }
            }
        }
    }

    return resultat;
}
