#pragma once
#include "framework/Core.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "framework/Object.h"

namespace ly
{
    class Application;
    class Actor;
    class World : public Object
    {
    public:
        
        World(Application* owningApp);

        void BeginPlayInternal();
        void TickInternal(float deltaTime);
        void Render(sf::RenderWindow& window);
        
        virtual ~World();

        template<typename ActorType, typename... Args>
        weak<ActorType> SpawnActor(Args... args);

        sf::Vector2u GetWindowSize() const;
        void CleanCycle(); 

    private:

        Application* mOwningApp;
        bool mBeginPlay;
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);

        list<shared<Actor>> mActors;
        list<shared<Actor>> mPendingActors;
    };

    template<typename ActorType, typename... Args>
    weak<ActorType> World::SpawnActor(Args... args)
    {
        shared<ActorType> newActor{ new ActorType(this, args...) };
        mPendingActors.push_back(newActor);
        return newActor;
    }
}
