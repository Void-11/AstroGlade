#ifndef ASTROGLADE_GAME_ENEMY_CHAOSSTAGE_H
#define ASTROGLADE_GAME_ENEMY_CHAOSSTAGE_H

#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace ly
{
	// Cycles through every enemy type at an ever shorter interval until the stage duration runs out.
	class ChaosStage : public GameStage
	{
	public:
		explicit ChaosStage(World* world);

		void StartStage() override;

	private:
		void StageFinished() override;
		void SpawnVanguard();
		void SpawnTwinBlade();
		void SpawnHexagon();
		void SpawnUFO();

		void IncreaseDifficulty();
		void StageDurationReached();

		float mSpawnInterval = 4.f;
		float mMinSpawnInterval = 0.8f;

		float mSpawnIntervalDecrement = 0.5f;
		float mSpawnIntervalDecrementInterval = 5.f;

		float mStageDuration = 60.f;

		TimerHandle mDifficultTimerHandle;
		TimerHandle mSpawnTimer;
		TimerHandle mStageDurationTimer;
	};
}

#endif // ASTROGLADE_GAME_ENEMY_CHAOSSTAGE_H
