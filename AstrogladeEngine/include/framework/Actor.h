#pragma once

namespace ly
{
    class World;
    class Actor
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