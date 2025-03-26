#include "hough_polaire.h"
#include <cmath>
#include <iostream>
#include <vector>
#include "utils_image.h"


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


HoughPolaire initialiser_hough_polaire(const Image& image, double pas_theta, double pas_rho) {
    HoughPolaire hough;

    hough.theta_min = 0;
    hough.theta_max = M_PI;
    hough.pas_theta = pas_theta;

    double diagonale = std::sqrt(image.largeur * image.largeur + image.hauteur * image.hauteur);
    hough.rho_min = -diagonale;
    hough.rho_max = diagonale;
    hough.pas_rho = pas_rho;

    hough.nb_theta = static_cast<int>((hough.theta_max - hough.theta_min) / pas_theta) + 1;
    hough.nb_rho = static_cast<int>((hough.rho_max - hough.rho_min) / pas_rho) + 1;

    hough.accumulateur.resize(hough.nb_theta, std::vector<int>(hough.nb_rho, 0));

    return hough;
}

void remplir_accumulateur_polaire(HoughPolaire& hough, const Image& image_binaire) {
    std::vector<std::pair<int, int>> pixels_blancs = extraire_pixels_blancs(image_binaire);

    for (size_t k = 0; k < pixels_blancs.size(); ++k) {
        int x = pixels_blancs[k].first;
        int y = pixels_blancs[k].second;

        for (int i = 0; i < hough.nb_theta; ++i) {
            double theta = hough.theta_min + i * hough.pas_theta;
            double rho = x * std::cos(theta) + y * std::sin(theta);

            if (rho < hough.rho_min || rho > hough.rho_max) continue;

            int j = static_cast<int>((rho - hough.rho_min) / hough.pas_rho);

            if (j >= 0 && j < hough.nb_rho) {
                hough.accumulateur[i][j]++;
            }
        }
    }
}



void afficher_droites_polaire(const HoughPolaire& hough, int seuil) {
    std::cout << "---- Droites détectées (méthode polaire, seuil = " << seuil << ") ----\n";

    for (int i = 0; i < hough.nb_theta; ++i) {
        for (int j = 0; j < hough.nb_rho; ++j) {
            int votes = hough.accumulateur[i][j];

            if (votes >= seuil) {
                double theta = hough.theta_min + i * hough.pas_theta;
                double rho = hough.rho_min + j * hough.pas_rho;

                std::cout << "Droite : rho = " << rho
                    << ", theta = " << theta
                    << " rad (" << votes << " votes)" << std::endl;
            }
        }
    }
}


