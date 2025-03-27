#include <iostream>
#include "lecteur_ppm.h"
#include "hough_naif.h"
#include "conversion_binaire.h"
#include "dessin_droite.h"
#include "ecriture_ppm.h"

int main() {
    // 1. Lire l’image
    Image image_originale = lire_image_ppm("imgTresSimple.ppm");

    // 2. Appliquer Hough naïf pour détecter les droites AVANT binarisation
    HoughNaif hough = initialiser_hough_naif(image_originale, -5.0, 5.0, 0.1, 1.0);
    remplir_accumulateur_naif(hough, image_originale);  // on travaille sur l’image brute
    afficher_droites_significatives(hough, 1);           // seuil = 1 vote

    // 3. Convertir l’image en binaire (après détection)
    Image image_binaire = convertir_en_binaire(image_originale, 128);
    ecrire_image_ppm(image_binaire, "image_binaire.ppm");

    // 4. Dessiner les droites détectées sur l’image binaire (ou copie)
    Image image_resultat = dessiner_droites_naives(hough, image_binaire, 1); // seuil = 1 vote

    // 5. Sauvegarder l’image finale avec les droites
    ecrire_image_ppm(image_resultat, "image_droites.ppm");

    return 0;
}
