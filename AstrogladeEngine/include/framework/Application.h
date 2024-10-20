#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
    class Application
    {
    public:

        Application();
        
        void Run();
        
    private:

        sf::RenderWindow mWindow;
        float mTargetFrameRate;
        sf::Clock mTickClock;

        void TickInternal(float deltaTime);
        void RenderInternal();
        virtual void Tick(float deltaTime);
        virtual void Render();
        
    };
}