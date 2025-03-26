#include "hough_naif.h"
#include <cmath>
#include <iostream>
#include "ecriture_ppm.h"
#include "conversion_binaire.h"
#include "lecteur_ppm.h"
#include "utils_image.h"  // pour extraire_pixels_blancs

HoughNaif initialiser_hough_naif(const Image& image, double m_min, double m_max, double pas_m, double pas_b) {
    HoughNaif hough;

    hough.m_min = m_min;
    hough.m_max = m_max;
    hough.pas_m = pas_m;
    hough.b_min = -image.hauteur;
    hough.b_max = image.hauteur;
    hough.pas_b = pas_b;

    hough.nb_m = static_cast<int>((m_max - m_min) / pas_m) + 1;
    hough.nb_b = static_cast<int>((hough.b_max - hough.b_min) / pas_b) + 1;

    hough.accumulateur.resize(hough.nb_m, std::vector<int>(hough.nb_b, 0));

    return hough;
}

void remplir_accumulateur_naif(HoughNaif& hough, const Image& image_binaire) {
    std::vector<std::pair<int, int>> pixels_blancs = extraire_pixels_blancs(image_binaire);

    for (size_t k = 0; k < pixels_blancs.size(); ++k) {
        int x = pixels_blancs[k].first;
        int y = pixels_blancs[k].second;

        for (int i = 0; i < hough.nb_m; ++i) {
            double m = hough.m_min + i * hough.pas_m;
            double b = y - m * x;

            if (b < hough.b_min || b > hough.b_max) continue;

            int j = static_cast<int>((b - hough.b_min) / hough.pas_b);

            if (j >= 0 && j < hough.nb_b) {
                hough.accumulateur[i][j]++;
            }
        }
    }
}

void afficher_droites_significatives(const HoughNaif& hough, int seuil) {
    std::cout << "---- Droites détectées (seuil = " << seuil << ") ----" << std::endl;

    for (int i = 0; i < hough.nb_m; ++i) {
        for (int j = 0; j < hough.nb_b; ++j) {
            int votes = hough.accumulateur[i][j];

            if (votes >= seuil) {
                double m = hough.m_min + i * hough.pas_m;
                double b = hough.b_min + j * hough.pas_b;

                std::cout << "Droite : y = " << m << " * x + " << b
                    << "   (" << votes << " votes)" << std::endl;
            }
        }
    }
}
