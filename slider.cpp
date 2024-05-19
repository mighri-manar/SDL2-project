#include "slider.hpp"
Slider::Slider(int x, int y, int w, int h, int minVal, int maxVal, int currentVal, SDL_Renderer* rend)
        : minValue(minVal), maxValue(maxVal), currentValue(currentVal), renderer(rend), isDragging(false) {
    sliderBox = {x, y, w, h};
}

void Slider::handleEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.x >= sliderBox.x && e.button.x <= (sliderBox.x + sliderBox.w) &&
            e.button.y >= sliderBox.y && e.button.y <= (sliderBox.y + sliderBox.h)) {
            isDragging = true;
            updateValue(e.button.x);
        }
    } else if (e.type == SDL_MOUSEBUTTONUP) {
        isDragging = false;
    } else if (e.type == SDL_MOUSEMOTION && isDragging) {
        updateValue(e.motion.x);
    }
}

void Slider::updateValue(int mouseX) {
    // Ensure that the mouseX is within the boundaries of the slider
    if (mouseX < sliderBox.x) {
        mouseX = sliderBox.x;
    } else if (mouseX > sliderBox.x + sliderBox.w) {
        mouseX = sliderBox.x + sliderBox.w;
    }

    int position = mouseX - sliderBox.x; // Position within the slider
    currentValue = minValue + (position * (maxValue - minValue) / sliderBox.w);
    Mix_VolumeMusic(currentValue); // Adjust the volume immediately
}


void Slider::render() {
    // Draw the slider track
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255); // Grey color
    SDL_RenderFillRect(renderer, &sliderBox);

    // Draw the slider handle
    int handleWidth = 10; // Width of the handle
    int handlePosition = ((currentValue - minValue) * sliderBox.w / (maxValue - minValue)) - (handleWidth / 2);
    SDL_Rect handleRect = {sliderBox.x + handlePosition, sliderBox.y, handleWidth, sliderBox.h};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color for the handle
    SDL_RenderFillRect(renderer, &handleRect);
}

Slider::~Slider() = default;