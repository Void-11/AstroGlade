#pragma once

#include <functional>
#include "framework/Actor.h"
namespace ly
{
	class PlayerSpaceship;
	class Reward;
	using RewardFunc = std::function<void(PlayerSpaceship*)>;
	using RewardFactoryFunc = std::function<weak<Reward>(World*)>;

	enum class RewardAudioType
	{
		Generic,
		Health,
		Weapon,
		Life,
		ScoreMultiplier
	};

	class Reward : public Actor
	{
	public:
		Reward(World* world, const std::string& texturePath, RewardFunc rewardFunc, RewardAudioType audioType = RewardAudioType::Generic, float speed = 200.f);
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override;
	private:
		virtual void OnActorBeginOverlap(Actor* otherActor) override;
		RewardFunc mRewardFunc;
		RewardAudioType mAudioType;
		float mSpeed;
	};

	weak<Reward> CreateHealthReward(World* world);
	weak<Reward> CreateThreewayShooterReward(World* world);
	weak<Reward> CreateFrontalWiperReward(World* world);
	weak<Reward> CreateLifeReward(World* world);
	weak<Reward> CreateScoreMultiplierReward(World* world);

	weak<Reward> CreateReward(World* world, const std::string& texturePath, RewardFunc rewardFunc, RewardAudioType audioType);

	void RewardHealth(PlayerSpaceship* player);
	void RewardThreewayShooter(PlayerSpaceship* player);
	void RewardFrontalWiper(PlayerSpaceship* player);
	void RewardLife(PlayerSpaceship* player);
	void RewardScoreMultiplier(PlayerSpaceship* player);
}
