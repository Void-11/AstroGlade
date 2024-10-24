#pragma once
#include "framework/Object.h"

namespace ly
{
    class World;
    class Actor : public Object
    {
    public:

        Actor(World* owningWorld);
        
        virtual ~Actor();
        
        void BeginPlayIternal();
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);

    private:

        World* mOwningWorld;
        bool mHasBeginPlay;
    };
}