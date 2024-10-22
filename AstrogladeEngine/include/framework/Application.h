#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
    class World;
    class Application
    {
    public:

        Application();
        
        void Run();

        template<typename WorldType>
        weak<WorldType> LoadWorld();
        
    private:

        sf::RenderWindow mWindow;
        float mTargetFrameRate;
        sf::Clock mTickClock;

        void TickInternal(float deltaTime);
        void RenderInternal();
        virtual void Tick(float deltaTime);
        virtual void Render();

        shared<World> currentWorld;
    };

    template <typename WorldType>
    weak<WorldType> Application::LoadWorld()
    {
        shared<WorldType> newWorld{new WorldType(this) };
        currentWorld = newWorld;
        return newWorld;
    }

}