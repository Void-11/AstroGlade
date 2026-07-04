#pragma once

namespace ly
{
	class Actor;
	class Shooter
	{
	public:
		bool Shoot();

		virtual bool CanShoot() const { return true; }
		virtual bool IsOnCooldown() const { return false; }
		Actor* GetOwner() const { return mOwner; }
		
		int GetCurrentLevel() const { return mCurrentLevel; }
		int GetMaxLevel() const { return mMaxLevel; }

		virtual void IncrementLevel(int amt = 1);
		virtual void SetCurrentLevel(int level);
	protected:
		Shooter(Actor* owner);
	private:
		virtual bool ShootImpl() = 0;
		Actor* mOwner;

		int mCurrentLevel;
		int mMaxLevel;
	};
}
