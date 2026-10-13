#ifndef ASTROGLADE_ENGINE_FRAMEWORK_BACKDROPACTOR_H
#define ASTROGLADE_ENGINE_FRAMEWORK_BACKDROPACTOR_H

#include <string>

#include "framework/Actor.h"

namespace ly
{
	// A window sized, repeating texture that scrolls at a constant velocity.
	class BackdropActor : public Actor
	{
	public:
		BackdropActor(World* owningWorld, const std::string& texturePath, const sf::Vector2f& velocity = sf::Vector2f{ 0.f, -50.f });
		void Tick(float deltaTime) override;

	private:
		sf::Vector2f mMovingVelocity;
		float mLeftShift = 0.f;
		float mTopShift = 0.f;
	};
}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_BACKDROPACTOR_H
