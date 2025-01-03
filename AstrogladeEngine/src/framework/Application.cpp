#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"

namespace ly
{
    
    Application::Application(unsigned int windowHeight, unsigned int windowWidth, const std::string& title,sf::Uint32 style)
        : mWindow{sf::VideoMode(windowWidth, windowHeight), title, style},
        mTargetFrameRate(60.f),
        mTickClock{},
        currentWorld{nullptr},
        mCleanCycleClock{},
        mCleanCycleInterval{2.f}
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

    sf::Vector2u Application::GetWindowSize() const
    {
        return mWindow.getSize();
    }

    void Application::TickInternal(float deltaTime)
    {
        Tick(deltaTime);
        
        if (currentWorld)
        {
            //currentWorld->BeginPlayInternal();
            currentWorld->TickInternal(deltaTime);
        }
        
        TimerManager::Get().UpdateTimer(deltaTime);
        PhysicsSystem::Get().Step(deltaTime);

        if(mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval)
        {
            mCleanCycleClock.restart();
            AssetManager::Get().CleanCycle();
            if(currentWorld)
            {
                currentWorld->CleanCycle();
            }
        }
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
         if(currentWorld)
         {
             currentWorld->Render(mWindow);
         }
    }
}
