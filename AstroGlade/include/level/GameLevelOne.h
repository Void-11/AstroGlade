#ifndef ASTROGLADE_GAME_LEVEL_GAMELEVELONE_H
#define ASTROGLADE_GAME_LEVEL_GAMELEVELONE_H

#include "framework/World.h"

namespace ly
{
	class Actor;
	class GameplayHUD;
	class PlayerSpaceship;

	// The playable level: a sequence of enemy stages that ends with the boss fight.
	class GameLevelOne : public World
	{
	public:
		explicit GameLevelOne(Application* owningApp);
		bool DispatchEvent(const sf::Event& event) override;

	private:
		void BeginPlay() override;
		void InitGameStages() override;
		void AllGameStageFinished() override;
		void OnGameStageStarted(GameStage& startedStage) override;
		void OnGameStageFinished(GameStage& finishedStage) override;

		void PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship);
		void SetPausedWithMusic(bool paused);
		void ResumeGame();
		void QuitGame();
		void Restart();
		void GameOver();
		void FinishGame(bool playerWon);
		void RespawnPlayerSpaceship();
		void BindPlayerSpaceship();
		void ApplyBossRespawnLoadout(PlayerSpaceship& playerSpaceship);
		void SpawnCosmetics();

		weak<PlayerSpaceship> mPlayerSpaceship;
		weak<GameplayHUD> mGameplayHUD;
		bool mGameFinished = false;
		bool mBossFightActive = false;
		float mRespawnDelay = 1.5f;
	};
}

#endif // ASTROGLADE_GAME_LEVEL_GAMELEVELONE_H
