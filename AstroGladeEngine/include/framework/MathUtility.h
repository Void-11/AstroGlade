#ifndef ASTROGLADE_ENGINE_FRAMEWORK_MATHUTILITY_H
#define ASTROGLADE_ENGINE_FRAMEWORK_MATHUTILITY_H

#include <cmath>
#include <cstddef>

#include <SFML/Graphics.hpp>

namespace ly
{
	inline constexpr float kPi = 3.14159265358979323846f;

	[[nodiscard]] sf::Vector2f RotationToVector(float rotation);

	[[nodiscard]] constexpr float DegreesToRadians(float degrees)
	{
		return degrees * (kPi / 180.f);
	}

	[[nodiscard]] constexpr float RadiansToDegrees(float radians)
	{
		return radians * (180.f / kPi);
	}

	template<typename T>
	[[nodiscard]] float GetVectorLength(const sf::Vector2<T>& vector)
	{
		return static_cast<float>(std::sqrt(vector.x * vector.x + vector.y * vector.y));
	}

	template<typename T>
	sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vectorToScale, float amt)
	{
		vectorToScale.x *= amt;
		vectorToScale.y *= amt;
		return vectorToScale;
	}

	template<typename T>
	sf::Vector2<T>& Normalize(sf::Vector2<T>& vector)
	{
		const float vectorLength = GetVectorLength<T>(vector);
		if (vectorLength == 0.f) return vector;

		ScaleVector(vector, 1.f / vectorLength);

		return vector;
	}

	[[nodiscard]] sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha);

	[[nodiscard]] sf::Vector2f LerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha);

	[[nodiscard]] float LerpFloat(float a, float b, float alpha);

	[[nodiscard]] float RandomRange(float min, float max);
	// Uniformly picks an index in [0, count). count must be greater than zero.
	[[nodiscard]] std::size_t RandomIndex(std::size_t count);
	[[nodiscard]] sf::Vector2f RandomUnitVector();
}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_MATHUTILITY_H
