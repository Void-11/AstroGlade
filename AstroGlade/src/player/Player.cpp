#include <algorithm>

#include "framework/World.h"
#include "player/Player.h"
#include "player/PlayerSpaceship.h"
#include "weapon/Shooter.h"

namespace ly
{
	weak<PlayerSpaceship> Player::SpawnSpaceship(World* world)
	{
		if (mLifeCount <= 0)
		{
			mCurrentPlayerSpaceship.reset();
			onLifeExhausted.Broadcast();
			return {};
		}

		mCurrentPlayerSpaceship = world->SpawnActor<PlayerSpaceship>();
		if (const shared<PlayerSpaceship> spaceship = mCurrentPlayerSpaceship.lock())
		{
			const sf::Vector2u windowSize = world->GetWindowSize();
			spaceship->SetActorLocation(sf::Vector2f{ static_cast<float>(windowSize.x) / 2.f, static_cast<float>(windowSize.y) - 100.f });
			spaceship->SetActorRotation(-90.f);
		}
		ApplyDefaultWeaponToCurrentSpaceship();
		return mCurrentPlayerSpaceship;
	}

	bool Player::ConsumeLife()
	{
		if (mLifeCount <= 0)
		{
			onLifeExhausted.Broadcast();
			return false;
		}

		--mLifeCount;
		mCurrentPlayerSpaceship.reset();
		onLifeChange.Broadcast(mLifeCount);
		if (mLifeCount == 0)
		{
			onLifeExhausted.Broadcast();
			return false;
		}

		return true;
	}

	void Player::AddLifeCount(int count)
	{
		if (count > 0)
		{
			mLifeCount += count;
			onLifeChange.Broadcast(mLifeCount);
		}
	}

	void Player::AddScore(int amt)
	{
		if (amt > 0)
		{
			mScore += amt * mScoreMultiplier;
			onScoreChange.Broadcast(mScore);
		}
	}

	void Player::IncreaseScoreMultiplier(int amt)
	{
		if (amt <= 0 || mScoreMultiplier == kMaxScoreMultiplier)
		{
			return;
		}

		mScoreMultiplier = std::min(mScoreMultiplier + amt, kMaxScoreMultiplier);
		onScoreChange.Broadcast(mScore);
	}

	void Player::IncreaseDefaultWeaponLevel(int amt)
	{
		if (amt <= 0)
		{
			return;
		}

		mDefaultWeaponLevel = std::clamp(mDefaultWeaponLevel + amt, 1, Shooter::kMaxLevel);
		if (const shared<PlayerSpaceship> spaceship = mCurrentPlayerSpaceship.lock(); spaceship && !spaceship->IsPendingDestroy())
		{
			spaceship->ApplyDefaultWeaponLevelIfUsingLaser(mDefaultWeaponLevel);
		}
	}

	void Player::ApplyDefaultWeaponToCurrentSpaceship()
	{
		if (const shared<PlayerSpaceship> spaceship = mCurrentPlayerSpaceship.lock(); spaceship && !spaceship->IsPendingDestroy())
		{
			spaceship->ApplyDefaultWeapon(mDefaultWeaponLevel);
		}
	}
}
