#include "framework/MathUtility.h"

namespace ly
{
    const float PI = 3.1415926535;
    
    sf::Vector2f RotationToVector(float rotation)
    {
        float radians = DegreeToRadians(rotation);
        return sf::Vector2f(std::cos(radians), std::sin(radians));
      //return {std::cos(radians), std::sin(radians)};
    }

    float DegreeToRadians(float degrees)
    {
        return degrees * (PI/180.f);
    }

    float RadiansToDegrees(float radians)
    {
        return radians * (180.f/PI);
    }
}