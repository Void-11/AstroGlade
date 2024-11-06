#pragma once
#include "framework/Core.h"
#include <box2d/b2_world.h>

namespace ly
{
    class Actor;
    class PhysicsSystem
    {
    public:

        static PhysicsSystem& Get();
        void Step(float deltaTime);
        b2Body* AddListener(Actor* Listener);
        void RemoveListener(b2Body* bodyToRemove);
        float GetPhysicsScale() const { return mPhysicsScale; }

    protected:

        PhysicsSystem();

    private:

        static unique<PhysicsSystem> physicsSystem;
        b2World mPhysicsWorld;
        float mPhysicsScale;
        int mVelocityIterations;
        int mPositionIterations;
    };
}
