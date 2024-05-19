#include "Play.hpp"
#include "Menu.hpp"
#include "Pause.hpp"

Play::Play(){}

bool Play::Init(){
    m_DevMode = true;
    m_Ctxt = Engine::Instance()->GetRenderer();

    Parser::Instance()->ParseTextures("/home/manar/Documents/ENIT/POO/sdl project/textures.tml");
    m_LevelMap = Parser::Instance()->ParseMap("/home/manar/Documents/ENIT/POO/sdl project/map.tmx");
    Parser::Instance()->ParseGameObjects("/home/manar/Documents/ENIT/POO/sdl project/level1.tml", &m_SceneObjects);

    TileLayer* colLayer = m_LevelMap->GetLayers().back();
    CollisionMgr::Instance()->SetCollisionLayer(colLayer);
    Camera::Instance()->SetLimit(colLayer->GetWidth(), colLayer->GetHeight());

    auto player = ObjectFactory::Instance()->CreateObject("WARRIOR", new Transform(200, 600, 136, 96, "player_idle"));
    Camera::Instance()->SetViewPort({0, 0, Engine::Instance()->GetWidth(), Engine::Instance()->GetHeight()});
    Camera::Instance()->SetTarget(player->GetOrigin());
    m_GameObjects.push_back(std::move(player));

    std::cout << "play initialized!" << std::endl;
    return true;
}

void Play::Render(){

    SDL_SetRenderDrawColor(m_Ctxt, 45, 80, 82, 255);
    SDL_RenderClear(m_Ctxt);

    for(auto& scene_obj : m_SceneObjects)
        scene_obj->Draw();

    m_LevelMap->Render();

    for(auto& object : m_GameObjects)
        object->Draw();

    SDL_RenderPresent(m_Ctxt);
}

void Play::Update(){

    Events();

    
        float dt = Timer::Instance()->GetDeltaTime();

        for(auto& object : m_GameObjects)
            object->Update(dt);

        Camera::Instance()->TrackTarget();
        m_LevelMap->Update();

        for(auto& scene_obj : m_SceneObjects)
            scene_obj->Update(dt);
    
}

void Play::Events(){


        if(Input::Instance()->GetMouseButtonDown(LEFT)){
            const Vector2D currMousePos = Input::Instance()->GetMousePosition();
            const SDL_Point point = {static_cast<int>(currMousePos.X), static_cast<int>(currMousePos.Y)};
            const SDL_Rect viewport = Camera::Instance()->GetViewPort();

            if(SDL_PointInRect(&point, &viewport)){
                const Vector2D lastMousePos = Input::Instance()->GetMouseLastPosition();
                const Vector2D target = (currMousePos - lastMousePos)*-1;
                Camera::Instance()->Translate(target);
            }
        }

        //Camera::Instance()->TranslateX(10*Input::Instance()->GetAxisKey(HORIZONTAL));
        //Camera::Instance()->TranslateY(10*Input::Instance()->GetAxisKey(VERTICAL));
    

    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_F5))
        m_DevMode = false;
    if(Input::Instance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
        m_DevMode = true;
}

bool Play::Exit(){

    m_LevelMap->Clean();
    delete m_LevelMap;

    for(auto& scene_obj : m_SceneObjects){
        scene_obj->Clean();
        scene_obj.release();
    }

    for(auto& object : m_GameObjects){
        object->Clean();
        object.release();
    }

    m_SceneObjects.clear();
    m_GameObjects.clear();
    TextureMgr::Instance()->Clean();
    std::cout << "exit play" << std::endl;
    return true;
}

void Play::OpenMenu(){
    StateMgr::Instance()->ChangeState(new Menu());
}

void Play::PauseGame(){
    StateMgr::Instance()->PushState(new Pause());
    std::cout << "pause game" << std::endl;
}


