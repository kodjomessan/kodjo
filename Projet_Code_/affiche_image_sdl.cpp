#include <SDL3/SDL.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct Couleur {
    Uint8 r, g, b;
};

struct Image {
    int largeur, hauteur;
    std::vector<Couleur> pixels;
};

Image lire_image_ppm(const std::string& chemin) {
    std::ifstream fichier(chemin);
    if (!fichier.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir l'image " + chemin);
    }

    std::string entete;
    fichier >> entete;
    if (entete != "P3") throw std::runtime_error("Format PPM non supporté (doit être P3)");

    int largeur, hauteur, valeur_max;
    fichier >> largeur >> hauteur >> valeur_max;

    Image img;
    img.largeur = largeur;
    img.hauteur = hauteur;
    img.pixels.reserve(largeur * hauteur);

    int r, g, b;
    while (fichier >> r >> g >> b) {
        img.pixels.push_back({ static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b) });
    }

    return img;
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erreur SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    Image img;
    try {
        img = lire_image_ppm("image_droites.ppm"); // <-- change le nom selon ton image
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* fenetre = SDL_CreateWindow("Affichage Image PPM", img.largeur, img.hauteur, 0);
    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, nullptr, SDL_RENDERER_ACCELERATED);

    SDL_Texture* texture = SDL_CreateTexture(rendu, SDL_PIXELFORMAT_RGB24,
        SDL_TEXTUREACCESS_STREAMING,
        img.largeur, img.hauteur);

    std::vector<Uint8> donnees(img.largeur * img.hauteur * 3);
    for (size_t i = 0; i < img.pixels.size(); ++i) {
        donnees[i * 3] = img.pixels[i].r;
        donnees[i * 3 + 1] = img.pixels[i].g;
        donnees[i * 3 + 2] = img.pixels[i].b;
    }

    SDL_UpdateTexture(texture, nullptr, donnees.data(), img.largeur * 3);

    bool quitter = false;
    SDL_Event e;
    while (!quitter) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) quitter = true;
        }

        SDL_RenderClear(rendu);
        SDL_RenderTexture(rendu, texture, nullptr, nullptr);
        SDL_RenderPresent(rendu);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}
