#ifndef DESSIN_DROITE_ALEATOIRE_H
#define DESSIN_DROITE_ALEATOIRE_H

#include "lecteur_ppm.h"
#include "hough_aleatoire.h"

Image dessiner_droites_aleatoires(const std::vector<Droite>& droites, const Image& image, int seuil);

#endif

