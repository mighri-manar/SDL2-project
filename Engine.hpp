#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "GameState.hpp"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Engine {
public:
    void Init();
    void Quit();
    void Clean();
    void Update();
    void Render();
    void Events();

    bool IsRunning();
    SDL_Window* GetWindow();
    SDL_Renderer* GetRenderer();
    int GetWidth();
    int GetHeight();
    void SetWidth(int width);
    void SetHeight(int height);
    static Engine* Instance();

private:
    Engine();
    bool m_IsRunning;
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    static Engine* s_Instance;
    int m_Width, m_Height;
};

#endif // ENGINE_H
