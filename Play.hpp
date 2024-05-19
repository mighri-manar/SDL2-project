#ifndef PLAY_H
#define PLAY_H

#include <map>
#include <iostream>
#include "TileMap.hpp"
#include "GameObject.hpp"
#include "GameState.hpp"
#include "Enemy.hpp"
#include "Warrior.hpp"
#include "Timer.hpp"
#include "Input.hpp"
#include "Camera.hpp"
#include "Parser.hpp"
#include "TileLayer.hpp"
#include "ObjectFactory.hpp"
#include "TextureMgr.hpp"
#include "CollisionMgr.hpp"
#include "StateMgr.hpp"
#include "StaticObject.hpp"
#include "Cloud.hpp"

class Play : public GameState{

    public:
        Play();
        void Events();
        virtual bool Init();
        virtual bool Exit();
        virtual void Update();
        virtual void Render();

    private:
        static void OpenMenu();
        static void PauseGame();

    private:
        bool m_DevMode;
        TileMap* m_LevelMap;
        ObjectList m_GameObjects;
        ObjectList m_SceneObjects;
};

#endif // PLAY_H
