#include "buttonmenu.hpp"

#include <utility>

Button::Button(int x, int y, int width, int height, SDL_Color color, std::string text, SDL_Renderer* renderer, TTF_Font* font)
        : buttonRect{x, y, width, height}, buttonColor{color}, buttonText(std::move(text)), renderer(renderer), font(font), hoverColor{0, 0, 255, 255} {}
void Button::renderText(SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, buttonText.c_str(), color); // White text
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {buttonRect.x + (buttonRect.w - textSurface->w) / 2, buttonRect.y + (buttonRect.h - textSurface->h) / 2, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

void Button::renderBorder() {
    SDL_Rect topBorder = {buttonRect.x, buttonRect.y, buttonRect.w, BUTTON_BORDER_WIDTH};
    SDL_Rect leftBorder = {buttonRect.x, buttonRect.y, BUTTON_BORDER_WIDTH, buttonRect.h};
    SDL_Rect bottomBorder = {buttonRect.x, buttonRect.y + buttonRect.h - BUTTON_BORDER_WIDTH, buttonRect.w, BUTTON_BORDER_WIDTH};
    SDL_Rect rightBorder = {buttonRect.x + buttonRect.w - BUTTON_BORDER_WIDTH, buttonRect.y, BUTTON_BORDER_WIDTH, buttonRect.h};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    SDL_RenderFillRect(renderer, &topBorder);
    SDL_RenderFillRect(renderer, &leftBorder);
    SDL_RenderFillRect(renderer, &bottomBorder);
    SDL_RenderFillRect(renderer, &rightBorder);
}

void Button::render() {
    // Draw button background only if hovered, for visual feedback
    /*if (hovered) {
        SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
        SDL_RenderFillRect(renderer, &buttonRect);
        renderBorder();  // Uncomment if border is desired when hovered
    }*/

    if (hovered) {
        renderText(hoverColor);
    } else {
        renderText(buttonColor);
    }
}


bool Button::wasClicked(int mouseX, int mouseY) const {
    return (mouseX >= buttonRect.x && mouseX <= (buttonRect.x + buttonRect.w) &&
            mouseY >= buttonRect.y && mouseY <= (buttonRect.y + buttonRect.h));
}

void Button::hover() {
    renderText(hoverColor);
    hovered = true;

}

void Button::unhover() {
    renderText(buttonColor);
    hovered = false;

}