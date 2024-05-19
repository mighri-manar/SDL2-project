#ifndef MAIN_CPP_SLIDER_HPP
#define MAIN_CPP_SLIDER_HPP
#include<SDL2/SDL.h>
#include<SDL2/SDL_mixer.h>

class Slider {
public:
    SDL_Rect sliderBox;
    int minValue, maxValue, currentValue;
    bool isDragging;
    SDL_Renderer* renderer;

    Slider(int x, int y, int w, int h, int minVal, int maxVal, int currentVal, SDL_Renderer* rend);
    ~Slider();

    void handleEvent(SDL_Event& e) ;

    void updateValue(int mouseX) ;

    void render() ;
};


#endif //MAIN_CPP_SLIDER_HPP