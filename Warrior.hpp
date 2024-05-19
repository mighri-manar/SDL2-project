#ifndef WARRIOR_H
#define WARRIOR_H

#include "SpriteAnimation.hpp"
#include "RigidBody.hpp"
#include "Collider.hpp"
#include "Vector2D.hpp"
#include "GameObject.hpp"

#define JUMP_FORCE 10.0f
#define JUMP_TIME 15.0f;

#define RUN_FORCE 4.0f
#define ATTACK_TIME 20.0f

class Warrior: public GameObject{

    public:
        Warrior(Transform* tf);
        virtual void Draw();
        virtual void Clean();
        virtual void Update(float dt);

    private:
        void AnimationState();

    private:
        bool m_IsRunning;
        bool m_IsJumping;
        bool m_IsFalling;
        bool m_IsGrounded;
        bool m_IsAttacking;
        bool m_IsCrouching;

        float m_JumpTime;
        float m_JumpForce;
        float m_AttackTime;

        Collider* m_Collider;
        SpritetAnimation* m_Animation;
        RigidBody* m_RigidBody;
        Vector2D m_LastSafePosition;
};

#endif // WARRIOR_H
