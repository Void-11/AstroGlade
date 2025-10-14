#pragma once
#include "framework/Actor.h"
#include "framework/MathUtility.h"

namespace ly
{
    class MovingSpriteActor : public Actor
    {
    public:
        MovingSpriteActor(World* world, const std::string& texturePath, const sf::Vector2f& velocity, float minScale = 1.f, float maxScale = 1.f)
            : Actor{world, texturePath}, mVelocity{velocity}
        {
            float sc = RandomRange(minScale, maxScale);
            GetSprite().setScale(sc, sc);
        }

        virtual void Tick(float deltaTime) override
        {
            Actor::Tick(deltaTime);
            AddActorLocationOffset(mVelocity * deltaTime);
            auto win = GetWindowSize();
            auto b = GetActorGlobalBounds();
            if (GetActorLocation().y - b.height > win.y + 50.f)
            {
                // recycle to top
                float x = RandomRange(0.f, (float)win.x);
                SetActorLocation({x, -50.f});
            }
        }
    private:
        sf::Vector2f mVelocity;
    };
}
