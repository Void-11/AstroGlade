#ifndef ASTROGLADE_GAME_ENEMY_ENEMYSPACESHIP_H
#define ASTROGLADE_GAME_ENEMY_ENEMYSPACESHIP_H

#include <string>

#include "framework/Core.h"
#include "player/Reward.h"
#include "spaceship/Spaceship.h"

namespace ly
{
	class EnemySpaceship : public Spaceship
	{
	public:
		EnemySpaceship(World* owningWorld,
			const std::string& texturePath,
			float collisionDamage = 50.f,
			float rewardSpawnWeight = 0.5f,
			List<RewardFactoryFunc> rewards =
			{
				CreateHealthReward,
				CreateThreewayShooterReward,
				CreateFrontalWiperReward,
				CreateLifeReward,
				CreateScoreMultiplierReward
			}
		);

		void Tick(float deltaTime) override;
		void SetScoreAwardAmt(int amt);
		// The chance, in [0, 1], that a reward drops when this enemy is destroyed.
		void SetRewardSpawnWeight(float weight);
		Delegate<EnemySpaceship*> onEnemyKilled;

	private:
		void SpawnReward();
		void OnActorBeginOverlap(Actor* other) override;
		void Blew() override;

		float mCollisionDamage;
		int mScoreAwardAmt = 10;
		float mRewardSpawnWeight;
		List<RewardFactoryFunc> mRewardFactories;
	};
}

#endif // ASTROGLADE_GAME_ENEMY_ENEMYSPACESHIP_H
