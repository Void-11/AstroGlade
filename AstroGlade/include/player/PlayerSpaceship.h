#ifndef ASTROGLADE_GAME_PLAYER_PLAYERSPACESHIP_H
#define ASTROGLADE_GAME_PLAYER_PLAYERSPACESHIP_H

#include <string>

#include "framework/Core.h"
#include "spaceship/Spaceship.h"

namespace ly
{
	class Shooter;

	class PlayerSpaceship : public Spaceship
	{
	public:
		explicit PlayerSpaceship(World* owningWorld, const std::string& path = "SpaceShooterRedux/PNG/playerShip.png");
		~PlayerSpaceship() override;

		void Tick(float deltaTime) override;
		void SetSpeed(const sf::Vector2f& newSpeed) { mSpeed = newSpeed; }
		[[nodiscard]] sf::Vector2f GetSpeed() const { return mSpeed; }
		void Shoot() override;
		// Equips newShooter, or levels up the current shooter when it is of the same type.
		void SetShooter(unique<Shooter> newShooter);
		void ApplyDefaultWeapon(int weaponLevel);
		void ApplyDefaultWeaponLevelIfUsingLaser(int weaponLevel);
		void ApplyDamage(float amt) override;
		void BeginPlay() override;

	private:
		[[nodiscard]] unique<Shooter> CreateDefaultShooter();
		void HandleInput();
		void NormalizeInput();
		void ClampInputOnEdge();
		void ConsumeInput();
		[[nodiscard]] bool IsBoosting() const;
		void StopInvulnerable();
		void UpdateInvulnerable(float deltaTime);

		sf::Vector2f mMoveInput;
		sf::Vector2f mSpeed;
		float mBoostSpeedMultiplier = 1.6f;

		unique<Shooter> mShooter;

		float mInvulnerableTime = 2.f;
		bool mInvulnerable = true;

		float mInvulnerableFlashInterval = 0.5f;
		float mInvulnerableFlashTimer = 0.f;
		float mInvulnerableFlashDir = 1.f;
	};
}

#endif // ASTROGLADE_GAME_PLAYER_PLAYERSPACESHIP_H
