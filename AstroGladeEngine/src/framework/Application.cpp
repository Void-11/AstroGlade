#include "framework/Application.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/AudioManager.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"

namespace ly
{

	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		: mWindow{ sf::VideoMode(windowWidth, windowHeight), title, style }
	{

	}

	void Application::Run()
	{
		mTickClock.restart();
		float accumulatedTime = 0.f;
		constexpr float targetDeltaTime = 1.f / kTargetFrameRate;
		while (mWindow.isOpen())
		{
			sf::Event windowEvent{};
			while (mWindow.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
				{
					QuitApplication();
				}
				else
				{
					DispatchEvent(windowEvent);
				}
			}
			accumulatedTime += mTickClock.restart().asSeconds();
			bool worldChanged = false;
			while (accumulatedTime >= targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				worldChanged = true;
			}

			if (worldChanged)
			{
				RenderInternal();
			}
			else
			{
				// Nothing moved since the last frame, so wait for the next tick instead of drawing the same frame again.
				sf::sleep(sf::seconds(targetDeltaTime - accumulatedTime));
			}
		}
	}

	sf::Vector2u Application::GetWindowSize() const
	{
		return mWindow.getSize();
	}

	bool Application::DispatchEvent(const sf::Event& event)
	{
		if (mCurrentWorld)
		{
			return mCurrentWorld->DispatchEvent(event);
		}
		return false;
	}
	
	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
	
		if (mCurrentWorld)
		{
			mCurrentWorld->TickInternal(deltaTime);
		}

		const bool simulationPaused = mCurrentWorld && mCurrentWorld->IsPaused();
		if (!simulationPaused)
		{
			TimerManager::Get().UpdateTimer(deltaTime);
			PhysicsSystem::Get().Step(deltaTime);
		}

		if (mCleanCycleClock.getElapsedTime().asSeconds() >= kCleanCycleInterval)
		{
			mCleanCycleClock.restart();
			AssetManager::Get().CleanCycle();
			AudioManager::Get().CleanCycle();
			if (mCurrentWorld)
			{
				mCurrentWorld->CleanCycle();
			}
		}

		if (mPendingWorld && mPendingWorld != mCurrentWorld)
		{
			// Releasing the previous world destroys its actors before the physics world is rebuilt.
			mCurrentWorld = mPendingWorld;

			PhysicsSystem::Get().Reset();
			mCurrentWorld->BeginPlayInternal();
		}
	}

	void Application::RenderInternal()
	{
		mWindow.clear();

		Render();

		mWindow.display();
	}

	void Application::Render()
	{
		if (mCurrentWorld)
		{
			mCurrentWorld->Render(mWindow);
		}
	}

	void Application::Tick([[maybe_unused]] float deltaTime)
	{
		
	}

	void Application::QuitApplication()
	{
		mWindow.close();
	}
}
