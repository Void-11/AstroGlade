#ifndef ASTROGLADE_GAME_ENEMY_HEXAGONSTAGE_H
#define ASTROGLADE_GAME_ENEMY_HEXAGONSTAGE_H

#include <SFML/Graphics.hpp>

#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace ly
{
	// Spawns Hexagons in groups of three, in a V formation at the top center of the screen.
	class HexagonStage : public GameStage
	{
	public:
		explicit HexagonStage(World* world);

		void StartStage() override;

	private:
		void StageFinished() override;
		void SpawnHexagon();

		float mSpawnInterval = 5.f;
		float mSideSpawnOffset = 80.f;
		int mSpawnGroupAmt = 5;
		int mCurrentSpawnCount = 0;

		sf::Vector2f mMidSpawnLoc;
		sf::Vector2f mLeftSpawnLoc;
		sf::Vector2f mRightSpawnLoc;

		TimerHandle mSpawnTimer;
	};
}

#endif // ASTROGLADE_GAME_ENEMY_HEXAGONSTAGE_H
