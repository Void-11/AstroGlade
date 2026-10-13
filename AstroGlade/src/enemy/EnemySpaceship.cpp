#include <utility>

#include "enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"
#include "player/PlayerManager.h"

namespace ly
{
	EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage, float rewardSpawnWeight, List<RewardFactoryFunc> rewards)
		: Spaceship{ owningWorld, texturePath },
		mCollisionDamage{ collisionDamage },
		mRewardSpawnWeight{ rewardSpawnWeight },
		mRewardFactories{ std::move(rewards) }
	{
		SetTeamID(2);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width * 2.f))
		{
			Destroy();
		}
	}

	void EnemySpaceship::SetScoreAwardAmt(int amt)
	{
		mScoreAwardAmt = amt;
	}

	void EnemySpaceship::SetRewardSpawnWeight(float weight)
	{
		if (weight < 0.f || weight > 1.f)
		{
			return;
		}

		mRewardSpawnWeight = weight;
	}

	void EnemySpaceship::SpawnReward()
	{
		if (mRewardFactories.empty()) return;

		if (mRewardSpawnWeight < RandomRange(0.f, 1.f))
			return;

		const RewardFactoryFunc& rewardFactory = mRewardFactories[RandomIndex(mRewardFactories.size())];
		if (const shared<Reward> newReward = rewardFactory(GetWorld()).lock())
		{
			newReward->SetActorLocation(GetActorLocation());
		}
	}

	void EnemySpaceship::OnActorBeginOverlap(Actor* other)
	{
		Spaceship::OnActorBeginOverlap(other);
		if (IsOtherHostile(other))
		{
			other->ApplyDamage(mCollisionDamage);
		}
	}

	void EnemySpaceship::Blew()
	{
		onEnemyKilled.Broadcast(this);
		SpawnReward();
		if (Player* const player = PlayerManager::Get().GetPlayer())
		{
			player->AddScore(mScoreAwardAmt);
		}
	}
}
