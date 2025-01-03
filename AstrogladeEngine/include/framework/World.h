﻿#pragma once
#include "framework/Core.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "framework/Object.h"

namespace ly
{
    class Application;
    class Actor;
    class GameStage;
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
        void AddStage(const shared<GameStage>& newStage);

    private:

        Application* mOwningApp;
        bool mBeginPlay;
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);

        list<shared<Actor>> mActors;
        list<shared<Actor>> mPendingActors;
        list<shared<GameStage>> mGameStages;
        list<shared<GameStage>>::iterator mCurrentStage;
        virtual void InitGameStages();
        virtual void AllGameStageFinished();
        void NextGameStage();
        void StartStages();
    };

    template<typename ActorType, typename... Args>
    weak<ActorType> World::SpawnActor(Args... args)
    {
        shared<ActorType> newActor{ new ActorType(this, args...) };
        mPendingActors.push_back(newActor);
        return newActor;
    }
}
