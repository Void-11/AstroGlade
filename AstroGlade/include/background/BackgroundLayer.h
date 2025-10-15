#pragma once
#include "framework/Actor.h"
#include "background/MovingSpriteActor.h"

namespace ly
{
    class BackgroundLayer : public Actor
    {
    public:
        BackgroundLayer(World* world);
        virtual void BeginPlay() override;
        virtual void Tick(float deltaTime) override;

        void SetAssets(const std::vector<std::string>& paths);
        void SetSpriteCount(int count);
        void SetSizes(float minScale, float maxScale);
        void SetVelocities(const sf::Vector2f& minV, const sf::Vector2f& maxV);

    private:
        std::vector<std::string> mPaths;
        int mCount;
        float mMinScale;
        float mMaxScale;
        sf::Vector2f mMinVelocity;
        sf::Vector2f mMaxVelocity;
        bool mSpawned;
    };
}