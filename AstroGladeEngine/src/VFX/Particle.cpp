#include "VFX/Particle.h"
#include "framework/MathUtility.h"

namespace ly
{
	Particle::Particle(World* owningWorld, const std::string& texturePath)
		: Actor{ owningWorld, texturePath }
	{
	}

	void Particle::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		Move(deltaTime);
		Fade();

		if (mTimer.getElapsedTime().asSeconds() >= mLifeTime)
		{
			Destroy();
		}
	}

	void Particle::RandomVelocity(float minSpeed, float maxSpeed)
	{
		mVelocity = RandomUnitVector() * RandomRange(minSpeed, maxSpeed);
	}

	void Particle::RandomSize(float min, float max)
	{
		const float randScale = RandomRange(min, max);
		GetSprite().setScale(randScale, randScale);
	}

	void Particle::RandomLifeTime(float min, float max)
	{
		mLifeTime = RandomRange(min, max);
	}

	void Particle::Move(float deltaTime)
	{
		AddActorLocationOffset(mVelocity * deltaTime);
	}

	void Particle::Fade()
	{
		const float lifeAlpha = mTimer.getElapsedTime().asSeconds() / mLifeTime;
		GetSprite().setColor(LerpColor(GetSprite().getColor(), sf::Color{ 255, 255, 255, 0 }, lifeAlpha));
		GetSprite().setScale(LerpVector(GetSprite().getScale(), sf::Vector2f{ 0.f, 0.f }, lifeAlpha));
	}
}
