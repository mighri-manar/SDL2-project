#ifndef STATICOBJECT_H
#define STATICOBJECT_H

#include <SDL2/SDL.h>
#include "GameObject.hpp"
#include "TextureMgr.hpp"
#include "ObjectFactory.hpp"

class StaticObject: public GameObject {

    public:
        StaticObject(Transform* tf): GameObject(tf){
            int imgW, imgH;
            SDL_Texture* texture = TextureMgr::Instance()->GetTexture(tf->TextureID);
            SDL_QueryTexture(texture, NULL, NULL, &imgW, &imgH);
            m_Tf->Width = imgW;
            m_Tf->Height = imgH;
        }

        virtual void Draw(){
            GameObject::Draw();
        }

        virtual void Update(float dt){
            GameObject::Update(dt);
        }

        virtual void Clean(){
            GameObject::Clean();
        }
};

static Registrar<StaticObject> staticObj("SOBJECT");

#endif // STATICOBJECT_H

