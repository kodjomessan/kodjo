#include <iostream>
#include "lecteur_ppm.h"
#include "ecriture_ppm.h"
#include "conversion_binaire.h"

int main() {
    // �tape 1 : Lire une image couleur
    Image image_couleur = lire_image_ppm("imgTresSimple.ppm");

    // �tape 2 : Appliquer la conversion binaire avec un seuil (ex. : 128)
    int seuil = 128;
    Image image_binaire = convertir_en_binaire(image_couleur, seuil);

    // �tape 3 : Sauvegarder l�image binaire
    ecrire_image_ppm(image_binaire, "image_binaire.ppm");

    std::cout << "Conversion binaire termin�e. R�sultat enregistr� dans 'image_binaire.ppm'" << std::endl;

    return 0;
}
