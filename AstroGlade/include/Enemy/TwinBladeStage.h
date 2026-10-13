#ifndef ASTROGLADE_GAME_ENEMY_TWINBLADESTAGE_H
#define ASTROGLADE_GAME_ENEMY_TWINBLADESTAGE_H

#include <SFML/Graphics.hpp>

#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace ly
{
	// Spawns TwinBlades alternately just left and right of the screen center.
	class TwinBladeStage : public GameStage
	{
	public:
		explicit TwinBladeStage(World* world);
		void StartStage() override;

	private:
		void SpawnTwinBlade();
		void StageFinished() override;

		float mSpawnInterval = 1.5f;
		float mSpawnDistanceToCenter = 100.f;

		sf::Vector2f mLeftSpawnLoc;
		sf::Vector2f mRightSpawnLoc;
		sf::Vector2f mSpawnLoc;

		int mSpawnAmt = 10;
		int mCurrentSpawnCount = 0;

		TimerHandle mSpawnTimerHandle;
	};
}

#endif // ASTROGLADE_GAME_ENEMY_TWINBLADESTAGE_H
