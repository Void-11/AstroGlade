#pragma once

#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
	class PlayerSpaceship;
	class World;

	class Player : public Object
	{
	public:
		Player();
		weak<PlayerSpaceship> SpawnSpaceship(World* world);
		const weak<PlayerSpaceship> GetCurrentSpaceship() const { return mCurrentPlayerSpaceship; };

		bool ConsumeLife();
		void AddLifeCount(unsigned int count);
		int GetLifeCount() const { return mLifeCount; }
		
		void AddScore(unsigned int amt);
		int GetScore() const { return mScore; }
		void IncreaseScoreMultiplier(unsigned int amt = 1);
		unsigned int GetScoreMultiplier() const { return mScoreMultiplier; }

		void IncreaseDefaultWeaponLevel(unsigned int amt = 1);
		int GetDefaultWeaponLevel() const { return mDefaultWeaponLevel; }

		Delegate<int> onLifeChange;
		Delegate<int> onScoreChange;
		Delegate<> onLifeExhausted;

	private:
		void ApplyDefaultWeaponToCurrentSpaceship();
		unsigned int mLifeCount;
		unsigned int mScore;
		unsigned int mScoreMultiplier;
		unsigned int mMaxScoreMultiplier;
		int mDefaultWeaponLevel;
		weak<PlayerSpaceship> mCurrentPlayerSpaceship;
	};
}
