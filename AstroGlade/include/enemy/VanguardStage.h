#ifndef ASTROGLADE_GAME_ENEMY_VANGUARDSTAGE_H
#define ASTROGLADE_GAME_ENEMY_VANGUARDSTAGE_H

#include <SFML/Graphics.hpp>

#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace ly
{
	class EnemySpaceship;

	// Sends rows of Vanguards down the left, middle and right of the screen.
	// The first Vanguards killed are guaranteed to drop a three-way shooter.
	class VanguardStage : public GameStage
	{
	public:
		explicit VanguardStage(World* world);
		void StartStage() override;

	private:
		void StageFinished() override;
		void SpawnVanguard();
		void SwitchRow();
		void VanguardKilled(EnemySpaceship* enemy);

		float mSpawnInterval = 2.f;
		float mSwitchInterval = 5.f;
		float mSpawnDistanceToEdge = 100.f;

		sf::Vector2f mLeftSpawnLoc;
		sf::Vector2f mMiddleSpawnLoc;
		sf::Vector2f mRightSpawnLoc;
		sf::Vector2f mSpawnLoc;

		TimerHandle mSpawnTimerHandle;
		TimerHandle mSwitchTimerHandle;

		int mRowsToSpawn = 3;
		int mRowSpawnCount = 0;

		int mVanguardsPerRow = 3;
		int mCurrentRowVanguardCount = 0;
		int mVanguardsKilled = 0;
		int mGuaranteedWeaponRewardKillCount = 3;
		bool mGuaranteedWeaponRewardSpawned = false;
	};
}

#endif // ASTROGLADE_GAME_ENEMY_VANGUARDSTAGE_H
