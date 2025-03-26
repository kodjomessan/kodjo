#ifndef DESSIN_DROITE_POLAIRE_H
#define DESSIN_DROITE_POLAIRE_H

#include "hough_polaire.h"

// Crée une image avec les droites détectées tracées en rouge
Image dessiner_droites_polaire(const HoughPolaire& hough, const Image& image_binaire, int seuil);
#endif

