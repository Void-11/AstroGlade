#include "player/Player.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
	namespace
	{
		int ClampWeaponLevel(int level)
		{
			const int minWeaponLevel = 1;
			const int maxWeaponLevel = 4;
			if (level < minWeaponLevel)
			{
				return minWeaponLevel;
			}

			if (level > maxWeaponLevel)
			{
				return maxWeaponLevel;
			}

			return level;
		}
	}

	Player::Player()
		: mLifeCount{3},
		mScore{0},
		mScoreMultiplier{1},
		mMaxScoreMultiplier{5},
		mDefaultWeaponLevel{1},
		mCurrentPlayerSpaceship{}
	{
	}
	weak<PlayerSpaceship> Player::SpawnSpaceship(World* world)
	{
		if (mLifeCount > 0)
		{
			auto windowSize = world->GetWindowSize();
			mCurrentPlayerSpaceship = world->SpawnActor<PlayerSpaceship>();
			mCurrentPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(windowSize.x/2.f, windowSize.y - 100.f));
			mCurrentPlayerSpaceship.lock()->SetActorRotation(-90.f);
			ApplyDefaultWeaponToCurrentSpaceship();
			return mCurrentPlayerSpaceship;
		}
		else
		{
			mCurrentPlayerSpaceship = weak<PlayerSpaceship>{};
			onLifeExhausted.Broadcast();
		}

		return weak<PlayerSpaceship>{};
	}

	bool Player::ConsumeLife()
	{
		if (mLifeCount == 0)
		{
			onLifeExhausted.Broadcast();
			return false;
		}

		--mLifeCount;
		mCurrentPlayerSpaceship = weak<PlayerSpaceship>{};
		onLifeChange.Broadcast(mLifeCount);
		if (mLifeCount == 0)
		{
			onLifeExhausted.Broadcast();
			return false;
		}

		return true;
	}

	void Player::AddLifeCount(unsigned int count)
	{
		if (count > 0)
		{
			mLifeCount += count;
			onLifeChange.Broadcast(mLifeCount);
		}
	}
	void Player::AddScore(unsigned int amt)
	{
		if (amt > 0)
		{
			mScore += amt * mScoreMultiplier;
			onScoreChange.Broadcast(mScore);
		}
	}

	void Player::IncreaseScoreMultiplier(unsigned int amt)
	{
		if (amt == 0 || mScoreMultiplier == mMaxScoreMultiplier)
		{
			return;
		}

		mScoreMultiplier += amt;
		if (mScoreMultiplier > mMaxScoreMultiplier)
		{
			mScoreMultiplier = mMaxScoreMultiplier;
		}

		onScoreChange.Broadcast(mScore);
	}

	void Player::IncreaseDefaultWeaponLevel(unsigned int amt)
	{
		if (amt == 0)
		{
			return;
		}

		mDefaultWeaponLevel = ClampWeaponLevel(mDefaultWeaponLevel + static_cast<int>(amt));
		if (!mCurrentPlayerSpaceship.expired() && !mCurrentPlayerSpaceship.lock()->IsPendingDestroy())
		{
			mCurrentPlayerSpaceship.lock()->ApplyDefaultWeaponLevelIfUsingLaser(mDefaultWeaponLevel);
		}
	}

	void Player::ApplyDefaultWeaponToCurrentSpaceship()
	{
		if (!mCurrentPlayerSpaceship.expired() && !mCurrentPlayerSpaceship.lock()->IsPendingDestroy())
		{
			mCurrentPlayerSpaceship.lock()->ApplyDefaultWeapon(mDefaultWeaponLevel);
		}
	}
}
