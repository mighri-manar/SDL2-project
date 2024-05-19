#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SDL2/SDL.h>

class RainAnimation {
public:
    virtual void update() = 0;
    virtual void render(SDL_Renderer* renderer) const = 0;
};

#endif // ANIMATION_HPP