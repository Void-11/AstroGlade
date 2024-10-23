#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
    Actor::Actor(World* owningWorld)
        :mOwningWorld(owningWorld),
        mHasBeginPlay{false}
    {
        
    }

    Actor::~Actor()
    {
        
    }

    void Actor::BeginPlayIternal()
    {
        if(!mHasBeginPlay)
        {
            mHasBeginPlay = true;
            BeginPlay();
        }
    }

    void Actor::BeginPlay()
    {
        LOG("Actor Begin Play")
    }

    void Actor::Tick(float deltaTime)
    {
        LOG("Actor Ticking")
    }
}
