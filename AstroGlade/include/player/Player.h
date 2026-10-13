#ifndef ASTROGLADE_GAME_PLAYER_PLAYER_H
#define ASTROGLADE_GAME_PLAYER_PLAYER_H

#include "framework/Core.h"
#include "framework/Delegate.h"
#include "framework/Object.h"

namespace ly
{
	class PlayerSpaceship;
	class World;

	// The persistent state of a player across spaceship respawns: lives, score and weapon progress.
	class Player : public Object
	{
	public:
		Player() = default;

		weak<PlayerSpaceship> SpawnSpaceship(World* world);
		[[nodiscard]] weak<PlayerSpaceship> GetCurrentSpaceship() const { return mCurrentPlayerSpaceship; }

		bool ConsumeLife();
		void AddLifeCount(int count);
		[[nodiscard]] int GetLifeCount() const { return mLifeCount; }

		void AddScore(int amt);
		[[nodiscard]] int GetScore() const { return mScore; }
		void IncreaseScoreMultiplier(int amt = 1);
		[[nodiscard]] int GetScoreMultiplier() const { return mScoreMultiplier; }

		void IncreaseDefaultWeaponLevel(int amt = 1);
		[[nodiscard]] int GetDefaultWeaponLevel() const { return mDefaultWeaponLevel; }

		Delegate<int> onLifeChange;
		Delegate<int> onScoreChange;
		Delegate<> onLifeExhausted;

	private:
		void ApplyDefaultWeaponToCurrentSpaceship();

		static constexpr int kMaxScoreMultiplier = 5;

		int mLifeCount = 3;
		int mScore = 0;
		int mScoreMultiplier = 1;
		int mDefaultWeaponLevel = 1;
		weak<PlayerSpaceship> mCurrentPlayerSpaceship;
	};
}

#endif // ASTROGLADE_GAME_PLAYER_PLAYER_H
