#include "background/BackgroundLayer.h"
#include "framework/MathUtility.h"
#include "framework/World.h"

namespace ly
{
    BackgroundLayer::BackgroundLayer(World* world)
        : Actor{world, ""}, mPaths{}, mCount{0}, mMinScale{1.f}, mMaxScale{1.f}, mMinVelocity{0.f, 0.f}, mMaxVelocity{0.f, 0.f}, mSpawned{false}
    {
    }

    void BackgroundLayer::BeginPlay()
    {
        Actor::BeginPlay();
    }

    void BackgroundLayer::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        if (!mSpawned && !mPaths.empty() && mCount > 0)
        {
            auto win = GetWindowSize();
            for (int i = 0; i < mCount; ++i)
            {
                int maxIndex = (int)mPaths.size() - 1;
                int idx = (int)RandomRange(0.f, (float)maxIndex);
                if (idx < 0) idx = 0;
                if (idx > maxIndex) idx = maxIndex;
                float sc = RandomRange(mMinScale, mMaxScale);
                sf::Vector2f vel{ RandomRange(mMinVelocity.x, mMaxVelocity.x), RandomRange(mMinVelocity.y, mMaxVelocity.y) };
                auto sprite = GetWorld()->SpawnActor<MovingSpriteActor>(mPaths[idx], vel, sc, sc);
                if (!sprite.expired())
                {
                    float x = RandomRange(0.f, (float)win.x);
                    float y = RandomRange(0.f, (float)win.y);
                    sprite.lock()->SetActorLocation({ x, y });
                }
            }
            mSpawned = true;
        }
    }

    void BackgroundLayer::SetAssets(const std::vector<std::string>& paths)
    {
        mPaths = paths;
    }
    void BackgroundLayer::SetSpriteCount(int count)
    {
        mCount = count;
    }
    void BackgroundLayer::SetSizes(float minScale, float maxScale)
    {
        mMinScale = minScale; mMaxScale = maxScale;
    }
    void BackgroundLayer::SetVelocities(const sf::Vector2f& minV, const sf::Vector2f& maxV)
    {
        mMinVelocity = minV; mMaxVelocity = maxV;
    }
}