#pragma once
#include "framework/Core.h"
#include <box2d/b2_world.h>

namespace ly
{
    class PhysicsSystem
    {
    public:

        static PhysicsSystem& Get();

    protected:

        PhysicsSystem();

    private:

        static unique<PhysicsSystem> physicsSystem;
        b2World mPhysicsWorld;
        float mPhysicsScale;
    };
}
