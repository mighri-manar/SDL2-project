// background.hpp
#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>

class Background {
private:
    SDL_Texture* texture;
    SDL_Rect destRect;
    SDL_Renderer* renderer;

public:
    Background(SDL_Renderer* renderer, const char* imagePath, int width, int height);
    void render(SDL_Renderer *pRenderer);
    ~Background();
     void clean();
};


#endif // BACKGROUND_HPP
