#ifndef ASTROGLADE_GAME_SPACESHIP_SPACESHIP_H
#define ASTROGLADE_GAME_SPACESHIP_SPACESHIP_H

#include <string>

#include "framework/Actor.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
	class Spaceship : public Actor
	{
	public:
		explicit Spaceship(World* owningWorld, const std::string& texturePath = "");

		void Tick(float deltaTime) override;
		void SetVelocity(const sf::Vector2f& newVel);
		[[nodiscard]] sf::Vector2f GetVelocity() const { return mVelocity; }
		virtual void Shoot();
		void BeginPlay() override;
		void ApplyDamage(float amt) override;
		HealthComponent& GetHealthComp() { return mHealthComp; }

	private:
		void Blink();
		void UpdateBlink(float deltaTime);

		virtual void OnHealthChanged(float amt, float health, float maxHealth);
		virtual void OnTakenDamage(float amt, float health, float maxHealth);
		void Blow();
		virtual void Blew();

		sf::Vector2f mVelocity;
		HealthComponent mHealthComp{ 100.f, 100.f };

		float mBlinkTime = 0.f;
		float mBlinkDuration = 0.2f;
		sf::Color mBlinkColorOffset{ 255, 0, 0, 255 };
	};
}

#endif // ASTROGLADE_GAME_SPACESHIP_SPACESHIP_H
