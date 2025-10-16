#pragma once
#include <SFML/System.hpp>
#include "weapon/Shooter.h"

namespace ly
{
	class LaserShooter : public Shooter
	{
	public:
		LaserShooter(Actor* owner,
			float cooldownTime = 1.f,
			const sf::Vector2f& localPositionOffset = { 0.f, 0.f },
			float localRotationOffset = 0.f,
			const std::string& laserTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png"
			);
		virtual bool IsOnCooldown() const override;
		virtual void IncrementLevel(int amt = 1) override;

		void SetLaserTexturePath(const std::string& laserTexturePath);
	private:
		virtual void ShootImpl() override;
		sf::Clock mCooldownClock;
		float mCooldownTime;
		sf::Vector2f mLocalPositionOffset;
		float mLocalRotationOffset;
		std::string mLaserTexturePath;
	};
}