#ifndef HOUGH_NAIF_H
#define HOUGH_NAIF_H

#include "lecteur_ppm.h"

struct HoughNaif {
    std::vector<std::vector<int>> accumulateur;
    double m_min, m_max, pas_m;
    double b_min, b_max, pas_b;
    int nb_m, nb_b;
};

// Initialise la structure Hough
HoughNaif initialiser_hough_naif(const Image& image, double m_min, double m_max, double pas_m, double pas_b);

// Remplit l'accumulateur à partir d'une image binaire
void remplir_accumulateur_naif(HoughNaif& hough, const Image& image_binaire);
void afficher_droites_significatives(const HoughNaif& hough, int seuil);


#endif

