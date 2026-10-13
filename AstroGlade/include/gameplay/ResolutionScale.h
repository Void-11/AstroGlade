#ifndef ASTROGLADE_GAME_GAMEPLAY_RESOLUTIONSCALE_H
#define ASTROGLADE_GAME_GAMEPLAY_RESOLUTIONSCALE_H

#include <SFML/Graphics.hpp>

namespace ly
{
	// Gameplay speeds are tuned for this window size and scaled to the real one,
	// so a crossing takes the same time at every resolution.
	inline constexpr float kReferenceWindowWidth = 600.f;
	inline constexpr float kReferenceWindowHeight = 980.f;

	[[nodiscard]] inline sf::Vector2f GetResolutionScale(const sf::Vector2u& windowSize)
	{
		return sf::Vector2f{
			static_cast<float>(windowSize.x) / kReferenceWindowWidth,
			static_cast<float>(windowSize.y) / kReferenceWindowHeight
		};
	}

	// Scales a vector tuned for the reference window, per axis, to a window of windowSize.
	[[nodiscard]] inline sf::Vector2f ScaleToResolution(const sf::Vector2f& referenceValue, const sf::Vector2u& windowSize)
	{
		const sf::Vector2f scale = GetResolutionScale(windowSize);
		return sf::Vector2f{ referenceValue.x * scale.x, referenceValue.y * scale.y };
	}
}

#endif // ASTROGLADE_GAME_GAMEPLAY_RESOLUTIONSCALE_H
