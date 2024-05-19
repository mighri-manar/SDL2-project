#include "raindrop.hpp"
#include<SDL2/SDL.h>

Raindrop::Raindrop(int posX, int posY, int vel) : x(posX), y(posY), velocity(vel), fallTime(0) {}

int Raindrop::getX() const {
    return x;
}

int Raindrop::getY() const {
    return y;
}

void Raindrop::setX(int posX) {
    x = posX;
}

void Raindrop::setY(int posY) {
    y = posY;
}

void Raindrop::update() {
    // Increment the fall time
    incrementFallTime();

    // Update the raindrop position based on velocity
    y += velocity;

    // You may want to update the X position as well if needed
}

void Raindrop::render(SDL_Renderer* renderer) const {
    // Set the drawing color to blue (you can change the color as needed)

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Draw a line to represent the raindrop
    SDL_RenderDrawLine(renderer, x, y, x, y + 5); // Vertical line


}

bool Raindrop::isOffScreen(int screenHeight) const {
    // Check if the raindrop is off the screen based on the screen height
    return y > screenHeight;
}

void Raindrop::incrementFallTime() {
    fallTime++; // Increment the fall time by 1
}

void Raindrop::resetFallTime() {
    fallTime = 0; // Reset the fall time to 0
}

int Raindrop::getFallTime() const {
    return fallTime; // Return the current fall time
}