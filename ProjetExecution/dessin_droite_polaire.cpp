#include "dessin_droite_polaire.h"
#include <cmath>
#include <vector>
#include <tuple>
#include <algorithm>

// Fonction pour dessiner les droites d�tect�es dans l'accumulateur de Hough (coordonn�es polaires)
Image dessiner_droites_polaire(const HoughPolaire& hough, Image image, int seuil) {
    Couleur rouge = { 255, 0, 0 }; // Couleur utilis�e pour dessiner les droites (rouge)

    // === �tape 1 : collecter les droites ayant un nombre de votes >= seuil ===
    std::vector<std::tuple<double, double, int>> droites; // Stocke (theta, rho, votes)

    // Parcours de l'accumulateur
    for (int i = 0; i < hough.nb_theta; ++i) {
        for (int j = 0; j < hough.nb_rho; ++j) {
            int votes = hough.accumulateur[i][j];

            // Si le nombre de votes d�passe le seuil, on enregistre cette droite
            if (votes >= seuil) {
                double theta = hough.theta_min + i * hough.pas_theta;
                double rho = hough.rho_min + j * hough.pas_rho;

                droites.emplace_back(theta, rho, votes);
            }
        }
    }

    // === �tape 2 : trier les droites par nombre de votes d�croissant ===
    std::sort(droites.begin(), droites.end(),
        [](const auto& a, const auto& b) {
            return std::get<2>(a) > std::get<2>(b); // tri par le 3e �l�ment (votes)
        });

    // === �tape 3 : ne garder que les 10 meilleures droites ===
    int nb_max_droites = std::min(10, static_cast<int>(droites.size()));

    // === �tape 4 : dessiner les droites s�lectionn�es sur l'image ===
    for (int k = 0; k < nb_max_droites; ++k) {
        double theta = std::get<0>(droites[k]);
        double rho = std::get<1>(droites[k]);

        // On parcourt chaque pixel de l'image
        for (int x = 0; x < image.largeur; ++x) {
            for (int y = 0; y < image.hauteur; ++y) {
                // Calcul de rho pour ce point (x, y)
                double rho_calc = x * std::cos(theta) + y * std::sin(theta);

                // Si ce point est proche (dans une tol�rance de 0.5) de la droite, on le colore en rouge
                if (std::abs(rho_calc - rho) < 0.5) {
                    image.pixels[y][x] = rouge;
                }
            }
        }
    }

    // Retourne l'image modifi�e avec les droites dessin�es
    return image;
}
