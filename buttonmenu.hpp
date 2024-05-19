#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Button {
private:
    SDL_Rect buttonRect;
    SDL_Color buttonColor;
    SDL_Color hoverColor;
    std::string buttonText;
    SDL_Renderer* renderer;
    TTF_Font* font;
    int BUTTON_BORDER_WIDTH = 2;
    bool hovered = false;

    void renderText(SDL_Color color);
    void renderBorder();

public:
    Button(int x, int y, int width, int height, SDL_Color color, std::string text, SDL_Renderer* renderer, TTF_Font* font);
    void render();
    Button(const Button& other) = default;
    Button& operator=(const Button& other) = default;
    bool wasClicked(int mouseX, int mouseY) const;
    void hover();
    void unhover();
    std::string getText() const { return buttonText; }
};


#endif // BUTTON_HPP
