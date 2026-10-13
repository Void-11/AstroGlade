#ifndef ASTROGLADE_ENGINE_FRAMEWORK_APPLICATION_H
#define ASTROGLADE_ENGINE_FRAMEWORK_APPLICATION_H

#include <string>
#include <type_traits>

#include <SFML/Graphics.hpp>

#include "framework/Core.h"

namespace ly
{
	class World;
	class Application
	{
	public:
		Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style);
		virtual ~Application() = default;

		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		void Run();

		template<typename WorldType>
		weak<WorldType> LoadWorld();

		[[nodiscard]] sf::Vector2u GetWindowSize() const;
		sf::RenderWindow& GetWindow() { return mWindow; }
		const sf::RenderWindow& GetWindow() const { return mWindow; }
		void QuitApplication();
	private:
		bool DispatchEvent(const sf::Event& event);
		void TickInternal(float deltaTime);
		void RenderInternal();

		virtual void Render();
		virtual void Tick(float deltaTime);

		static constexpr float kTargetFrameRate = 60.f;
		static constexpr float kCleanCycleInterval = 2.f;

		sf::RenderWindow mWindow;
		sf::Clock mTickClock;
	
		shared<World> mCurrentWorld;
		shared<World> mPendingWorld;

		sf::Clock mCleanCycleClock;
	};

	template<typename WorldType>
	weak<WorldType> Application::LoadWorld()
	{
		static_assert(std::is_base_of_v<World, WorldType>, "LoadWorld requires a type derived from World");

		auto newWorld = std::make_shared<WorldType>(this);
		mPendingWorld = newWorld;
		return newWorld;
	}
}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_APPLICATION_H
