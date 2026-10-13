#include <algorithm>
#include <cassert>
#include <random>

#include "framework/MathUtility.h"
namespace ly
{
	namespace
	{
		std::mt19937& RandomEngine()
		{
			static std::mt19937 engine{ std::random_device{}() };
			return engine;
		}
	}

	sf::Vector2f RotationToVector(float rotation)
	{
		const float radians = DegreesToRadians(rotation);
		return sf::Vector2f(std::cos(radians), std::sin(radians));
	}

	float LerpFloat(float a, float b, float alpha)
	{
		alpha = std::clamp(alpha, 0.f, 1.f);

		return a + (b - a) * alpha;
	}

	float RandomRange(float min, float max)
	{
		std::uniform_real_distribution<float> distribution{min, max};

		return distribution(RandomEngine());
	}

	std::size_t RandomIndex(std::size_t count)
	{
		assert(count > 0 && "RandomIndex needs a non-empty range");
		std::uniform_int_distribution<std::size_t> distribution{0, count - 1};

		return distribution(RandomEngine());
	}

	sf::Vector2f RandomUnitVector()
	{
		const float randomX = RandomRange(-1, 1);
		const float randomY = RandomRange(-1, 1);
		sf::Vector2f randVec{ randomX, randomY };
		Normalize(randVec);
		return randVec;
	}

	sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha)
	{
		const auto lerpChannel = [alpha](sf::Uint8 from, sf::Uint8 to)
		{
			return static_cast<sf::Uint8>(LerpFloat(from, to, alpha));
		};

		return sf::Color(lerpChannel(a.r, b.r), lerpChannel(a.g, b.g), lerpChannel(a.b, b.b), lerpChannel(a.a, b.a));
	}

	sf::Vector2f LerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha)
	{
		const float lerpX = LerpFloat(a.x, b.x, alpha);
		const float lerpY = LerpFloat(a.y, b.y, alpha);
		return sf::Vector2f(lerpX, lerpY);

	}
}
