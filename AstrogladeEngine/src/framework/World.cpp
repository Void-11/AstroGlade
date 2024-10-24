#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

namespace ly
{
    World::World(Application* owningApp)
        :mOwningApp{owningApp},
        mBeginPlay(false),
        mActors{},
        mPendingActors{}
    {
        
    }

    void World::BeginPlayInternal()
    {
        if(!mBeginPlay)
        {
            mBeginPlay = true;
            BeginPlay();
        }
    }

    void World::TickInternal(float deltaTime)
    {
        for(shared<Actor> actor : mPendingActors)
        {
            mActors.push_back(actor);
            actor->BeginPlayIternal();
        }

        mPendingActors.clear();
        
        for(auto iter = mActors.begin(); iter != mActors.end();)
        {
            if(iter->get()->IsPendingDestroy())
            {
                iter = mActors.erase(iter);
            }
            else
            {
                iter->get()->Tick(deltaTime);
                ++iter; 
            }
        }
        
        Tick(deltaTime);
    }

    World::~World()
    {
        
    } 

    void World::BeginPlay()
    {
       LOG("Begin Play")
    }

    void World::Tick(float deltaTime)
    {
        LOG("Tick at Framerate: ", 1.f/deltaTime)
    }
}
