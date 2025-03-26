#ifndef HOUGH_POLAIRE_H
#define HOUGH_POLAIRE_H

#include "lecteur_ppm.h"

struct HoughPolaire {
    std::vector<std::vector<int>> accumulateur;
    double theta_min, theta_max, pas_theta;
    double rho_min, rho_max, pas_rho;
    int nb_theta, nb_rho;
};

// Initialise la structure de Hough polaire
HoughPolaire initialiser_hough_polaire(const Image& image, double pas_theta, double pas_rho);

// Remplit l'accumulateur polaire avec l'image binaire
void remplir_accumulateur_polaire(HoughPolaire& hough, const Image& image_binaire);

// Affiche les droites détectées avec un certain seuil de votes
void afficher_droites_polaire(const HoughPolaire& hough, int seuil);

#endif
