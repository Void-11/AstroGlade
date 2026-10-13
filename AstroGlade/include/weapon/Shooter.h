#ifndef ASTROGLADE_GAME_WEAPON_SHOOTER_H
#define ASTROGLADE_GAME_WEAPON_SHOOTER_H

namespace ly
{
	class Actor;

	// A weapon mounted on an actor. Shooters are owned by their actor and refer back to it,
	// so they are neither copyable nor movable.
	class Shooter
	{
	public:
		static constexpr int kMaxLevel = 4;

		virtual ~Shooter() = default;
		Shooter(const Shooter&) = delete;
		Shooter& operator=(const Shooter&) = delete;

		bool Shoot();

		[[nodiscard]] virtual bool CanShoot() const { return true; }
		[[nodiscard]] virtual bool IsOnCooldown() const { return false; }
		[[nodiscard]] Actor* GetOwner() const { return mOwner; }

		[[nodiscard]] int GetCurrentLevel() const { return mCurrentLevel; }
		[[nodiscard]] bool IsAtMaxLevel() const { return mCurrentLevel == kMaxLevel; }

		void IncrementLevel(int amt = 1);
		// Clamps the level to [1, kMaxLevel]. Composite shooters override this to keep their parts in sync.
		virtual void SetCurrentLevel(int level);

	protected:
		explicit Shooter(Actor* owner);

	private:
		virtual bool ShootImpl() = 0;

		Actor* mOwner;
		int mCurrentLevel = 1;
	};

	// Tries to fire every shooter, in order and without short-circuiting.
	// Returns true if at least one of them fired.
	template<typename... Shooters>
	bool ShootAll(Shooters&... shooters)
	{
		bool fired = false;
		((fired = shooters.Shoot() || fired), ...);
		return fired;
	}
}

#endif // ASTROGLADE_GAME_WEAPON_SHOOTER_H
