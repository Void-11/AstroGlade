#ifndef ASTROGLADE_GAME_WEAPON_LASERSHOOTER_H
#define ASTROGLADE_GAME_WEAPON_LASERSHOOTER_H

#include <string>

#include <SFML/System.hpp>

#include "weapon/Shooter.h"

namespace ly
{
	// Fires a single laser from an offset relative to the owner. Higher levels shorten the cooldown.
	class LaserShooter : public Shooter
	{
	public:
		explicit LaserShooter(Actor* owner,
			float cooldownTime = 1.f,
			const sf::Vector2f& localPositionOffset = { 0.f, 0.f },
			float localRotationOffset = 0.f,
			const std::string& laserTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png"
		);

		[[nodiscard]] bool IsOnCooldown() const override;

		void SetLaserTexturePath(const std::string& laserTexturePath);

	private:
		bool ShootImpl() override;

		sf::Clock mCooldownClock;
		float mCooldownTime;
		sf::Vector2f mLocalPositionOffset;
		float mLocalRotationOffset;
		std::string mLaserTexturePath;
	};
}

#endif // ASTROGLADE_GAME_WEAPON_LASERSHOOTER_H
