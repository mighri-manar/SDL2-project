#include "Engine.hpp"
#include <cassert>
#include "Play.hpp"
#include "StateMgr.hpp"

Engine* Engine::s_Instance = nullptr;
Engine::Engine() {
    // Constructor implementation, if needed
}
/*--------------------------------------------------------------------------------------------------------------------*/
void Engine::Init(){
    m_Width = SCREEN_WIDTH;
    m_Height = SCREEN_HEIGHT;

    assert(!SDL_Init(SDL_INIT_VIDEO) && SDL_GetError());
    SDL_WindowFlags w_flags = (SDL_WindowFlags)(SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_Window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_Width, m_Height, w_flags);

    SDL_RendererFlags r_flags = (SDL_RendererFlags)(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    m_Renderer = SDL_CreateRenderer(m_Window, -1, r_flags);
    assert(m_Window && m_Renderer && SDL_GetError());

    StateMgr::Instance()->ChangeState(new Play());
    m_IsRunning = true;
}
/*--------------------------------------------------------------------------------------------------------------------*/

void Engine::Render(){

}
/*--------------------------------------------------------------------------------------------------------------------*/

void Engine::Update(){

}
/*--------------------------------------------------------------------------------------------------------------------*/

void Engine::Events(){

}
/*--------------------------------------------------------------------------------------------------------------------*/

void Engine::Clean(){
    StateMgr::Instance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();
}
/*--------------------------------------------------------------------------------------------------------------------*/

void Engine::Quit(){
    m_IsRunning = false;
}
/*--------------------------------------------------------------------------------------------------------------------*/

bool Engine::IsRunning() {
    return m_IsRunning;
}
/*--------------------------------------------------------------------------------------------------------------------*/

SDL_Window* Engine::GetWindow() {
    return m_Window;
}
/*--------------------------------------------------------------------------------------------------------------------*/

SDL_Renderer* Engine::GetRenderer() {
    return m_Renderer;
}
/*--------------------------------------------------------------------------------------------------------------------*/

int Engine::GetWidth() {
    return m_Width;
}
/*--------------------------------------------------------------------------------------------------------------------*/

int Engine::GetHeight() {
    return m_Height;
}
/*--------------------------------------------------------------------------------------------------------------------*/

void Engine::SetWidth(int width) {
    m_Width = width;
}
/*--------------------------------------------------------------------------------------------------------------------*/

void Engine::SetHeight(int height) {
    m_Height = height;
}
/*--------------------------------------------------------------------------------------------------------------------*/

Engine* Engine::Instance() {
    return s_Instance = (s_Instance != nullptr) ? s_Instance : new Engine();
}
/*--------------------------------------------------------------------------------------------------------------------*/



