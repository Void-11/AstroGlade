#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"
namespace ly
{
	class PlayerSpaceship;
	class GameplayHUD;
	class GameLevelOne : public World
	{
	public:
		        GameLevelOne(Application* owningApp);
		        virtual void BeginPlay() override;
		        virtual void InitGameStages() override;
		        virtual void AllGameStageFinished() override;
		        virtual bool DispatchEvent(const sf::Event& event) override;
		    private:
		        weak<PlayerSpaceship> mPlayerSpaceship;		weak<GameplayHUD> mGameplayHUD;
		void PlayerSpaceshipDestroyed(Actor* destoryedPlayerSpaceship);
		TimerHandle timerHandle_Test;
		void QuitGame();
		void Restart();
		void GameOver();
		void SpawnCosmetics();
	};
}