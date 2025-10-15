#include "player/Reward.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    Reward::Reward(World* w, const sf::Vector2f& spawnLoc, RewardType type)
        : Actor{w, "PNG/pickups/playerLife1_blue.png"}, mType{type}
    {
        SetActorLocation(spawnLoc);
    }

    void Reward::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        auto player = PlayerManager::Get().GetPlayer();
        if (!player || player->GetCurrentSpaceship().expired()) return;
        auto sp = player->GetCurrentSpaceship();
        auto pos = sp.lock()->GetActorLocation();
        auto my = GetActorLocation();
        float dx = pos.x - my.x;
        float dy = pos.y - my.y;
        if (dx*dx + dy*dy < 40*40)
        {
            // apply reward
            switch (mType)
            {
            case RewardType::Health:
                sp.lock()->GetHealthComp().ModifyHealth(+25.f);
                break;
            case RewardType::ThreeWay:
            {
                // add two angled extra lasers
                sp.lock()->EnableThreeWayShooter();
                break;
            }
            case RewardType::FrontalWiper:
            {
                // add a wider fan
                sp.lock()->EnableFrontalWiper();
                break;
            }
            case RewardType::Life:
                if (player) { player->SetLifeCount(player->GetLifeCount() + 1); player->onLifeChange.Broadcast(player->GetLifeCount()); }
                break;
            }
            Destroy();
        }
    }
}