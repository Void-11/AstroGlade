#ifndef ASTROGLADE_GAME_ENEMY_UFOSTAGE_H
#define ASTROGLADE_GAME_ENEMY_UFOSTAGE_H

#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace ly
{
	// Spawns UFOs from either side of the screen, flying towards its center.
	class UFOStage : public GameStage
	{
	public:
		explicit UFOStage(World* world);
		void StartStage() override;

	private:
		void StageFinished() override;
		void SpawnUFO();

		float mSpawnInterval = 4.f;
		int mSpawnAmt = 10;
		int mCurrentSpawnAmt = 0;
		float mUFOSpeed = 200.f;

		TimerHandle mSpawnTimer;
	};
}

#endif // ASTROGLADE_GAME_ENEMY_UFOSTAGE_H
