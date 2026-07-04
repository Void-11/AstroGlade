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
		        virtual void OnGameStageStarted(GameStage& startedStage) override;
		        virtual void OnGameStageFinished(GameStage& finishedStage) override;
		    private:
		        weak<PlayerSpaceship> mPlayerSpaceship;		weak<GameplayHUD> mGameplayHUD;
		bool mGameFinished;
		bool mBossFightActive;
		void PlayerSpaceshipDestroyed(Actor* destoryedPlayerSpaceship);
		TimerHandle mRespawnTimerHandle;
		float mRespawnDelay;
		void ResumeGame();
		void QuitGame();
		void Restart();
		void GameOver();
		void FinishGame(bool playerWon);
		void RespawnPlayerSpaceship();
		void ApplyBossRespawnLoadout(PlayerSpaceship& playerSpaceship);
		void SpawnCosmetics();
	};
}
