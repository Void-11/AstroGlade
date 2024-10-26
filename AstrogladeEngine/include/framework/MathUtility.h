#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
    sf::Vector2f RotationToVector(float rotation);
    float DegreeToRadians(float degrees);
    float RadiansToDegrees(float radians);
}
