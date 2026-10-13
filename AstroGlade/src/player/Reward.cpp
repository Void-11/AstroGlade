#include <utility>

#include "framework/World.h"
#include "gameplay/GameAudio.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "player/Reward.h"
#include "weapon/FrontalWiper.h"
#include "weapon/ThreeWayShooter.h"

namespace ly
{
	namespace
	{
		constexpr float kHealthRewardAmount = 10.f;

		weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc, RewardAudioType audioType)
		{
			return world->SpawnActor<Reward>(texturePath, std::move(rewardFunc), audioType);
		}

		void RewardHealth(PlayerSpaceship& player)
		{
			player.GetHealthComp().ChangeHealth(kHealthRewardAmount);
		}

		void RewardThreewayShooter(PlayerSpaceship& player)
		{
			player.SetShooter(std::make_unique<ThreeWayShooter>(&player, 0.4f, sf::Vector2f{ 50.f, 0.f }));
		}

		void RewardFrontalWiper(PlayerSpaceship& player)
		{
			player.SetShooter(std::make_unique<FrontalWiper>(&player, 0.4f, sf::Vector2f{ 50.f, 0.f }));
		}

		void RewardLife([[maybe_unused]] PlayerSpaceship& player)
		{
			if (Player* const owningPlayer = PlayerManager::Get().GetPlayer())
			{
				owningPlayer->AddLifeCount(1);
			}
		}

		void RewardScoreMultiplier([[maybe_unused]] PlayerSpaceship& player)
		{
			if (Player* const owningPlayer = PlayerManager::Get().GetPlayer())
			{
				owningPlayer->IncreaseScoreMultiplier();
			}
		}
	}

	Reward::Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, RewardAudioType audioType, float speed)
		: Actor{ world, texturePath },
		mRewardFunc{ std::move(rewardFunc) },
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

		const Player* const player = PlayerManager::Get().GetPlayer();
		if (!player)
			return;

		const shared<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship().lock();
		if (!playerSpaceship || playerSpaceship->IsPendingDestroy())
			return;

		if (playerSpaceship->GetUniqueID() == otherActor->GetUniqueID())
		{
			mRewardFunc(*playerSpaceship);
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
}
