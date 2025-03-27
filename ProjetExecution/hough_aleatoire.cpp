#include "hough_aleatoire.h"
#include "utils_image.h"
#include <random>
#include <cmath>
#include <iostream>

std::vector<Droite> detection_droites_aleatoire(const Image& image_binaire, int nb_iterations, double precision) {
    std::vector<std::pair<int, int>> points_blancs = extraire_pixels_blancs(image_binaire);
    std::map<std::pair<int, int>, int> accumulateur; // (m arrondi, b arrondi) donne votes

    if (points_blancs.size() < 2) return {};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, points_blancs.size() - 1);

    for (int k = 0; k < nb_iterations; ++k) {
        int i1 = dist(gen);
        int i2 = dist(gen);

        if (i1 == i2) continue;

        int x1 = points_blancs[i1].first;
        int y1 = points_blancs[i1].second;
        int x2 = points_blancs[i2].first;
        int y2 = points_blancs[i2].second;

        if (x1 == x2) continue; // éviter division par zéro (droite verticale)

        double m = (double)(y2 - y1) / (x2 - x1);
        double b = y1 - m * x1;

        int m_discret = static_cast<int>(std::round(m / precision));
        int b_discret = static_cast<int>(std::round(b / precision));

        accumulateur[std::make_pair(m_discret, b_discret)]++;
    }

    std::vector<Droite> resultats;

    for (std::map<std::pair<int, int>, int>::const_iterator it = accumulateur.begin(); it != accumulateur.end(); ++it) {
        int m_discret = it->first.first;
        int b_discret = it->first.second;
        int votes = it->second;

        double m = m_discret * precision;
        double b = b_discret * precision;

        Droite d = { m, b, votes };
        resultats.push_back(d);
    }

    return resultats;
}
