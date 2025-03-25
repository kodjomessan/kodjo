# Projet INFO802 : Détection de Droites avec la Transformation de Hough

Ce projet implémente la **transformée de Hough**, une technique utilisée pour détecter des formes géométriques dans des images, en particulier les lignes droites. Le code permet de lire une image en format **PPM**, de la convertir en binaire puis d'appliquer la transformée de Hough pour détecter les lignes. Il fournit également des outils pour enregistrer les résultats sous forme de nouvelles images.

## Description du projet

Le but de ce projet est de montrer comment appliquer la transformée de Hough sur une image en format **PPM**. Il est composé de plusieurs étapes :
- **Lecture d’une image PPM** avec la structure appropriée pour les couleurs.
- **Conversion de l’image en binaire** à l’aide d’un seuil.
- **Application de la transformée de Hough** pour détecter les lignes dans l’image binaire.
- **Visualisation des résultats** : l’image transformée est ensuite enregistrée et peut être visualisée.

Le projet comprend également des outils de **gestion de version** avec **Git**.

## Fonctionnalités principales

- **Lecture d’image PPM** : Chargement d’une image avec la gestion des en-têtes, commentaires et pixels RGB.
- **Conversion binaire** : Conversion des pixels d’une image en binaire selon un seuil de gris.
- **Transformée de Hough** : Détection des lignes droites dans une image binaire.
- **Sauvegarde des résultats** : Enregistrement de l'image traitée dans un nouveau fichier PPM.

## Structure du projet

Le projet est organisé de la manière suivante :

- `lecteur_ppm.h` et `lecteur_ppm.cpp` : Fonction pour lire une image en format PPM.
- `conversion_binaire.h` et `conversion_binaire.cpp` : Fonction pour convertir une image en binaire à l’aide d’un seuil.
- `ecriture_ppm.h` et `ecriture_ppm.cpp` : Fonction pour écrire une image en format PPM.
- `hough_naif.h` et `hough_naif.cpp` : Implémentation d’une approche naïve de la transformée de Hough pour détecter les lignes.

### Fichiers principaux

- **lecteur_ppm.h / lecteur_ppm.cpp** : Ces fichiers contiennent les fonctions pour lire une image en format PPM et stocker ses informations dans une structure.
- **conversion_binaire.h / conversion_binaire.cpp** : Ces fichiers définissent la fonction qui convertit l'image en niveaux de gris en une image binaire (noir et blanc) selon un seuil de gris.
- **ecriture_ppm.h / ecriture_ppm.cpp** : Ces fichiers contiennent la fonction pour sauvegarder l’image résultante dans un fichier PPM.
- **hough_naif.h / hough_naif.cpp** : Implémentation de l'algorithme de la transformée de Hough. Ce fichier inclut des fonctions pour initialiser l’espace d’accumulation et y insérer les données issues des pixels de l’image binaire.
