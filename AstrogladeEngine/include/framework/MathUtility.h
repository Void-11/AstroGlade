#pragma once
#include <SFML/Graphics.hpp>

namespace ly
{
    sf::Vector2f RotationToVector(float rotation);
    float DegreeToRadians(float degrees);
    float RadiansToDegrees(float radians);

    template<typename T>
    float GetVectorLength(sf::Vector2<T>& vector)
    {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y);
    }

    template<typename T>
    sf::Vector2<T>& ScaleVector(sf::Vector2<T>& vectorToScale, float amount)
    {
        vectorToScale.x *= amount;
        vectorToScale.y *= amount;
        return vectorToScale;
    }

    template<typename T>
    sf::Vector2<T>& Normalize(sf::Vector2<T>& vector)
    {
        float vectorLength = GetVectorLength<T>(vector);
        if(vectorLength == 0.f) return sf::Vector2<T>{};

        ScaleVector(vector, 1.0/vectorLength);

        return vector;
    }

    sf::Color LerpColor(const sf::Color& a, const sf::Color& b, float alpha);

    sf::Vector2f LerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha);

    float LerpFloat(float a, float b, float alpha);
}
