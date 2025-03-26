#ifndef DESSIN_DROITE_POLAIRE_H
#define DESSIN_DROITE_POLAIRE_H

#include "hough_polaire.h"

// Cr�e une image avec les droites d�tect�es trac�es en rouge
Image dessiner_droites_polaire(const HoughPolaire& hough, const Image& image_binaire, int seuil);
#endif

