#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>
#include "IObject.hpp"
#include "TextureMgr.hpp"
#include "Transform.hpp"

class GameObject : public IObject{

    public:
        GameObject(Transform* tf): m_Tf(tf){}

        virtual void Draw(){
            TextureMgr::Instance()->Draw(m_Tf);
        }

        virtual void Update(float dt){

        }

        virtual void Clean(){
            delete m_Tf;
        }

        inline Vector2D* GetOrigin(){return m_Tf->Origin;}

    protected:
        Transform* m_Tf;
};

#endif // GAMEOBJECT_H
