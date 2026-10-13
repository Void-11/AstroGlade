#ifndef ASTROGLADE_ENGINE_FRAMEWORK_WORLD_H
#define ASTROGLADE_ENGINE_FRAMEWORK_WORLD_H

#include <type_traits>
#include <utility>

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
	class Actor;
	class HUD;
	class Application;
	class GameStage;

	class World : public Object
	{
	public:
		explicit World(Application* owningApp);
		
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		void Render(sf::RenderWindow& window);

		~World() override = default;

		template<typename ActorType, typename... Args>
		weak<ActorType> SpawnActor(Args&&... args);

		template<typename HUDType, typename... Args>
		weak<HUDType> SpawnHUD(Args&&... args);

		[[nodiscard]] sf::Vector2u GetWindowSize() const;
		void CleanCycle();
		void AddStage(const shared<GameStage>& newStage);
		virtual bool DispatchEvent(const sf::Event& event);
		Application* GetApplication() { return mOwningApp; }
		const Application* GetApplication() const { return mOwningApp; }

		void SetPaused(bool paused) { mIsPaused = paused; }
		[[nodiscard]] bool IsPaused() const { return mIsPaused; }
	private:
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void RenderHUD(sf::RenderWindow& window);
		Application* mOwningApp;
		bool mBeganPlay = false;
		bool mIsPaused = false;

		List<shared<Actor>> mActors;

		List<shared<Actor>> mPendingActors;

		List<shared<GameStage>> mGameStages;
		
		List<shared<GameStage>>::iterator mCurrentStage = mGameStages.end();

		shared<HUD> mHUD;

		virtual void InitGameStages();
		virtual void AllGameStageFinished();
		virtual void OnGameStageStarted(GameStage& startedStage);
		virtual void OnGameStageFinished(GameStage& finishedStage);
		void NextGameStage();
		void StartStages();
		void BeginStage(GameStage& stage);
	};


	template<typename ActorType, typename... Args>
	weak<ActorType> World::SpawnActor(Args&&... args)
	{
		static_assert(std::is_base_of_v<Actor, ActorType>, "SpawnActor requires a type derived from Actor");

		auto newActor = std::make_shared<ActorType>(this, std::forward<Args>(args)...);
		mPendingActors.push_back(newActor);
		return newActor;
	}

	template<typename HUDType, typename... Args>
	weak<HUDType> World::SpawnHUD(Args&&... args)
	{
		static_assert(std::is_base_of_v<HUD, HUDType>, "SpawnHUD requires a type derived from HUD");

		auto newHUD = std::make_shared<HUDType>(std::forward<Args>(args)...);
		mHUD = newHUD;
		return newHUD;
	}

}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_WORLD_H
