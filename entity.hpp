#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL2/SDL.h>

class Entity {
public:
    Entity(int x, int y, bool visible = true);

    virtual ~Entity();

    //virtual void update() = 0;

    virtual void render(SDL_Renderer* renderer) = 0;

    virtual void interact(Entity* other) = 0;

protected:
    int x;
    int y;
    bool visible;
    SDL_Texture* image;
};

#endif // ENTITY_HPP
