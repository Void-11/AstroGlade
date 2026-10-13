#include "framework/BackdropActor.h"
#include "framework/World.h"

namespace ly
{
	BackdropActor::BackdropActor(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity)
		: Actor{ owningWorld, texturePath },
		mMovingVelocity{ velocity }
	{
		const sf::Vector2u windowSize = owningWorld->GetWindowSize();
		GetSprite().setOrigin(0.f, 0.f);
		GetSprite().setTextureRect(sf::IntRect{ 0, 0, static_cast<int>(windowSize.x), static_cast<int>(windowSize.y) });
		SetTextureRepeated(true);
	}

	void BackdropActor::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		mLeftShift += deltaTime * mMovingVelocity.x;
		mTopShift += deltaTime * mMovingVelocity.y;

		sf::IntRect currentRect = GetSprite().getTextureRect();
		currentRect.left = static_cast<int>(mLeftShift);
		currentRect.top = static_cast<int>(mTopShift);

		GetSprite().setTextureRect(currentRect);
	}
}
