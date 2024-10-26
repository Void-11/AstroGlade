#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
    class World;
    class Application
    {
    public:

        Application(unsigned int windowHeight,unsigned int windowWidth, const std::string& title, sf::Uint32 style);
        
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
        sf::Clock mCleanCycleClock;
        float mCleanCycleInterval;
    };

    template <typename WorldType>
    weak<WorldType> Application::LoadWorld()
    {
        shared<WorldType> newWorld{new WorldType(this) };
        currentWorld = newWorld;
        return newWorld;
    }

}