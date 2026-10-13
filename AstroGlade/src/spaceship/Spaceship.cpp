#include <algorithm>

#include "spaceship/Spaceship.h"
#include "framework/MathUtility.h"
#include "gameplay/GameAudio.h"
#include "VFX/Explosion.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld, texturePath }
	{
	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
		UpdateBlink(deltaTime);
	}

	void Spaceship::SetVelocity(const sf::Vector2f& newVel)
	{
		mVelocity = newVel;
	}

	void Spaceship::Shoot()
	{
	}

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysics(true);
		mHealthComp.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
		mHealthComp.onTakenDamage.BindAction(GetWeakRef(), &Spaceship::OnTakenDamage);
		mHealthComp.onHealthEmpty.BindAction(GetWeakRef(), &Spaceship::Blow);
	}

	void Spaceship::ApplyDamage(float amt)
	{
		mHealthComp.ChangeHealth(-amt);
	}

	void Spaceship::Blink()
	{
		if (mBlinkTime == 0.f)
		{
			mBlinkTime = mBlinkDuration;
		}
	}

	void Spaceship::UpdateBlink(float deltaTime)
	{
		if (mBlinkTime > 0.f)
		{
			mBlinkTime = std::max(mBlinkTime - deltaTime, 0.f);
			GetSprite().setColor(LerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
		}
	}

	void Spaceship::OnHealthChanged([[maybe_unused]] float amt, [[maybe_unused]] float health, [[maybe_unused]] float maxHealth)
	{
	}

	void Spaceship::OnTakenDamage([[maybe_unused]] float amt, [[maybe_unused]] float health, [[maybe_unused]] float maxHealth)
	{
		GameAudio::PlayShipHit(*this);
		Blink();
	}

	void Spaceship::Blow()
	{
		GameAudio::PlayShipDeath(*this);
		SpawnExplosion(*GetWorld(), GetActorLocation());
		Blew();
		Destroy();
	}

	void Spaceship::Blew()
	{
	}
}
