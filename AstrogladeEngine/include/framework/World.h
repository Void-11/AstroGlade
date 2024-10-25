#pragma once
#include "framework/Core.h"
#include "SFML/Graphics/RenderWindow.hpp"

namespace ly
{
    class Application;
    class Actor;
    class World
    {
    public:
        
        World(Application* owningApp);

        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        void Render(sf::RenderWindow& window);
        
        virtual ~World();

        template<typename ActorType>
        weak<ActorType> SpawnActor();
        

    private:

        Application* mOwningApp;
        bool mBeginPlay;
        void BeginPlay();
        void Tick(float deltaTime);

        list<shared<Actor>> mActors;
        list<shared<Actor>> mPendingActors;
    };

    template <typename ActorType>
    weak<ActorType> World::SpawnActor()
    {
        shared<ActorType> newActor{ new ActorType{this} };
        mPendingActors.push_back(newActor);
        return newActor;
    }
}
