#include "framework/World.h"
#include "gameplay/GameAudio.h"
#include "player/Reward.h"
#include "player/PlayerSpaceship.h"
#include "player/PlayerManager.h"
#include "weapon/FrontalWiper.h"
#include "weapon/ThreeWayShooter.h"

namespace ly
{
	Reward::Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, RewardAudioType audioType, float speed)
		: Actor{ world, texturePath },
		mRewardFunc{ rewardFunc },
		mAudioType{ audioType },
		mSpeed{ speed }
	{
	}
	void Reward::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
	}
	void Reward::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset({ 0.f, mSpeed * deltaTime });
		if (IsActorOutOfWindowBounds(GetActorGlobalBounds().height))
		{
			Destroy();
		}
	}

	void Reward::OnActorBeginOverlap(Actor* otherActor)
	{
		if (!otherActor || otherActor->IsPendingDestroy())
			return;

		if (!PlayerManager::Get().GetPlayer())
			return;

		weak<PlayerSpaceship> playerSpaceship = PlayerManager::Get().GetPlayer()->GetCurrentSpaceship();
		if (playerSpaceship.expired() || playerSpaceship.lock()->IsPendingDestroy())
			return;

		if (playerSpaceship.lock()->GetUniqueID() == otherActor->GetUniqueID())
		{
			mRewardFunc(playerSpaceship.lock().get());
			GameAudio::PlayRewardPickup(mAudioType);
			Destroy();
		}
	}

	weak<Reward> CreateHealthReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/pill_green.png", RewardHealth, RewardAudioType::Health);
	}

	weak<Reward> CreateThreewayShooterReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", RewardThreewayShooter, RewardAudioType::Weapon);
	}

	weak<Reward> CreateFrontalWiperReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", RewardFrontalWiper, RewardAudioType::Weapon);
	}

	weak<Reward> CreateLifeReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/pickups/playerLife1_blue.png", RewardLife, RewardAudioType::Life);
	}

	weak<Reward> CreateScoreMultiplierReward(World* world)
	{
		return CreateReward(world, "SpaceShooterRedux/PNG/Power-ups/star_gold.png", RewardScoreMultiplier, RewardAudioType::ScoreMultiplier);
	}

	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc, RewardAudioType audioType)
	{
		weak<Reward> reward = world->SpawnActor<Reward>(texturePath, rewardFunc, audioType);
		return reward;
	}

	void RewardHealth(PlayerSpaceship* player)
	{
		static float rewardAmt = 10.f;
		if (player && !player->IsPendingDestroy())
		{
			player->GetHealthComp().ChangeHealth(rewardAmt);
		}
	}

	void RewardThreewayShooter(PlayerSpaceship* player)
	{
		if (!player || player->IsPendingDestroy())
			return;

		player->SetShooter(unique<Shooter>{new ThreeWayShooter{player, 0.4f, {50.f, 0.f} }});
	}
	void RewardFrontalWiper(PlayerSpaceship* player)
	{
		if (!player || player->IsPendingDestroy())
			return;

		player->SetShooter(unique<Shooter>{new FrontalWiper{ player, 0.4f, {50.f, 0.f} }});
	}
	void RewardLife(PlayerSpaceship* player)
	{
		if (!PlayerManager::Get().GetPlayer())
			return;

		PlayerManager::Get().GetPlayer()->AddLifeCount(1);
	}

	void RewardScoreMultiplier(PlayerSpaceship* player)
	{
		if (!player || player->IsPendingDestroy() || !PlayerManager::Get().GetPlayer())
			return;

		PlayerManager::Get().GetPlayer()->IncreaseScoreMultiplier();
	}
}
