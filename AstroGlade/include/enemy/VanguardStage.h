#pragma once
#include <SFML/Graphics.hpp>
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace ly
{
	class EnemySpaceship;

	class VanguardStage : public GameStage
	{
	public:
		VanguardStage(World* world);
		virtual void StartStage() override;
		virtual void TickStage(float deltaTime) override;
	private:
		float mSpawnInterval;
		float mSwitchInterval;
		float mSpawnDistanceToEdge;

		sf::Vector2f mLeftSpawnLoc;
		sf::Vector2f mMiddleSpawnLoc;
		sf::Vector2f mRightSpawnLoc;
		sf::Vector2f mSpawnLoc;

		TimerHandle mSpawnTimerHandle;
		TimerHandle mSwitchTimerHandle;

		int mRowsToSpawn;
		int mRowSpawnCount;

		int mVarguardsPerRow;
		int mCurrentRowVanguardCount;
		int mVanguardsKilled;
		int mGuaranteedWeaponRewardKillCount;
		bool mGuaranteedWeaponRewardSpawned;
		bool mFinishedSpawning;

		virtual void StageFinished() override;
		void SpawnVanguard();
		void SwithRow();
		void VanguardKilled(EnemySpaceship* enemy);
	};
}
