#include <iostream>
#include "framework/Application.h"
#include "framework/Core.h"

namespace ly
{
    Application::Application()
        : mWindow{sf::VideoMode(1024, 1440), "Astro Glade"},
        mTargetFrameRate(60.f),
        mTickClock{}
    {
        
    }

    void Application::Run()
    {
        mTickClock.restart();
        float AccumulatedTime = 0.0f;
        float TargetDeltaTime = 1.0f / mTargetFrameRate;
        
        while (mWindow.isOpen())
        {
            sf::Event windowEvent;
            while (mWindow.pollEvent(windowEvent))
            {
                if(windowEvent.type == sf::Event::EventType::Closed)
                {
                    mWindow.close();
                }
            }
            AccumulatedTime += mTickClock.restart().asSeconds();

            while (AccumulatedTime > TargetDeltaTime)
            {
                AccumulatedTime -= TargetDeltaTime;
                TickInternal(TargetDeltaTime);
                RenderInternal();
            }
        }
    }
    
    void Application::TickInternal(float deltaTime)
    {
        LOG("Ticking at Framerate:  %f", 1.f/deltaTime)
        Tick(deltaTime);
    }

    void Application::RenderInternal()
    {
        mWindow.clear();
        Render();
        mWindow.display();
    }

    void Application::Tick(float deltaTime)
    {
        
    }

    void Application::Render()
    {
        sf::RectangleShape rect{ sf::Vector2f (200,200) };
        rect.setFillColor(sf::Color::Magenta);
        rect.setOrigin(100,100);
        rect.setPosition(mWindow.getSize().x/2.f, mWindow.getSize().y/2.f);
        mWindow.draw(rect);   
    }
}
