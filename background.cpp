// background.cpp
#include "background.hpp"
#include <iostream>
#include <stdexcept>

Background::Background(SDL_Renderer* renderer, const char* imagePath, int width, int height)
        : renderer(renderer), texture(nullptr) {
    SDL_Surface* imageSurface = IMG_Load(imagePath);
    if (imageSurface == nullptr) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    } else {
        texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        if (texture == nullptr) {
            std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        } else {
            destRect = {0, 0, width, height};  // Only set if texture creation was successful
        }
        SDL_FreeSurface(imageSurface);
    }
}

void Background::render(SDL_Renderer* pRenderer) {
    if (texture) {
        SDL_Rect renderQuad = {0, 0, 800, 600}; // Adjust as needed
        SDL_RenderCopy(pRenderer, texture, nullptr, &renderQuad);
    }
}



Background::~Background() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr; 
    }
}

void Background::clean() {
    SDL_DestroyTexture(texture);
}