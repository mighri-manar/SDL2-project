#ifndef ENEMY_H
#define ENEMY_H

#include "GameObject.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "SeqAnimation.hpp"
#include "SpriteAnimation.hpp"
#include "ObjectFactory.hpp"

class Enemy: public GameObject {

    public:
        Enemy(Transform* tf);

        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);

    private:
        Collider* m_Collider;
        RigidBody* m_RigiBody;
        SeqAnimation* m_Animation;
        Vector2D m_LastSafePosition;
        bool m_Flip;
};

#endif // ENEMY_H

