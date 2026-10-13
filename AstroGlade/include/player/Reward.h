#ifndef ASTROGLADE_GAME_PLAYER_REWARD_H
#define ASTROGLADE_GAME_PLAYER_REWARD_H

#include <functional>
#include <string>

#include "framework/Actor.h"

namespace ly
{
	class PlayerSpaceship;
	class Reward;
	using RewardFunc = std::function<void(PlayerSpaceship&)>;
	using RewardFactoryFunc = std::function<weak<Reward>(World*)>;

	enum class RewardAudioType
	{
		Generic,
		Health,
		Weapon,
		Life,
		ScoreMultiplier
	};

	// A pickup that falls down the screen and applies its reward to the player spaceship that touches it.
	class Reward : public Actor
	{
	public:
		Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, RewardAudioType audioType = RewardAudioType::Generic, float speed = 200.f);
		void BeginPlay() override;
		void Tick(float deltaTime) override;

	private:
		void OnActorBeginOverlap(Actor* otherActor) override;

		RewardFunc mRewardFunc;
		RewardAudioType mAudioType;
		float mSpeed;
	};

	[[nodiscard]] weak<Reward> CreateHealthReward(World* world);
	[[nodiscard]] weak<Reward> CreateThreewayShooterReward(World* world);
	[[nodiscard]] weak<Reward> CreateFrontalWiperReward(World* world);
	[[nodiscard]] weak<Reward> CreateLifeReward(World* world);
	[[nodiscard]] weak<Reward> CreateScoreMultiplierReward(World* world);
}

#endif // ASTROGLADE_GAME_PLAYER_REWARD_H
