#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include <functional>

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
        
        // Safe world switch: queues a world change to occur at the start of the next TickInternal
        template<typename WorldType>
        void QueueWorld();

        sf::Vector2u GetWindowSize() const;
        void QuitApplication() { mWindow.close(); }
        
    private:

        sf::RenderWindow mWindow;
        float mTargetFrameRate;
        sf::Clock mTickClock;

        void TickInternal(float deltaTime);
        void RenderInternal();
        virtual void Tick(float deltaTime);
        virtual void Render();

        shared<World> currentWorld;
        // Pending world switch
        bool mWorldSwitchPending{false};
        std::function<shared<World>()> mPendingWorldCreator;

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

    template <typename WorldType>
    void Application::QueueWorld()
    {
        mWorldSwitchPending = true;
        mPendingWorldCreator = [this]() -> shared<World>
        {
            return shared<World>{ new WorldType(this) };
        };
    }

}
