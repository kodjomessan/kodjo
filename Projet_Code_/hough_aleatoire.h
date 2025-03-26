#ifndef HOUGH_ALEATOIRE_H
#define HOUGH_ALEATOIRE_H

#include "lecteur_ppm.h"
#include <vector>
#include <map>

struct Droite {
    double m;
    double b;
    int votes;
};

// Retourne les droites d�tect�es avec un nombre d�it�rations donn�es
std::vector<Droite> detection_droites_aleatoire(const Image& image_binaire, int nb_iterations, double precision);

#endif

