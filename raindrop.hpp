#ifndef RAINDROP_HPP
#define RAINDROP_HPP

#include "animationrain.hpp"
#include<vector>
class Raindrop : public RainAnimation
{
private:
    int x, y;        // Position of the raindrop
    int velocity;    // Falling speed of the raindrop
    int fallTime;    // Time since the raindrop started falling

public:
    Raindrop(int posX, int posY, int vel);
    int getX() const;
    int getY() const;
    void setX(int posX);
    void setY(int posY);
    void update();
    void render(SDL_Renderer *renderer) const ;
    bool isOffScreen(int screenHeight) const;
    // Method to increment the fall time of the raindrop
    void incrementFallTime();

    // Method to reset the fall time of the raindrop
    void resetFallTime();

    // Method to get the fall time of the raindrop
    int getFallTime() const;
};


#endif // RAINDROP_HPP