#include "Enemy/EnemySpaceship.h"
#include "player/PlayerManager.h"
#include "framework/MathUtility.h"
#include "player/Reward.h"
#include "framework/World.h"
#include "framework/MathUtility.h"

namespace ly
{
    EnemySpaceship::EnemySpaceship(World* owningWorld, const std::string& texturePath, float collisionDamage)
        : Spaceship{owningWorld, texturePath}, mCollisionDamage{collisionDamage}
    {
        SetTeamID(2);
    }

    void EnemySpaceship::Tick(float deltaTime)
    {
        Spaceship::Tick(deltaTime);

        // Enemies keep their stage-defined facing (like LightYears). No auto-aim rotation here.

        if(IsActorOutOfWindowBounds(GetActorGlobalBounds().width))
        {
            Destroy();
        }
    }

    void EnemySpaceship::OnActorBeginOverlap(Actor* other)
    {
        Spaceship::OnActorBeginOverlap(other);
        if (IsOtherHostile(other))
        {
            other->ApplyDamage(mCollisionDamage);
        }
    }

    // Add score and drop reward on death
    void EnemySpaceship::Blow()
    {
        // Add score
        if (auto player = PlayerManager::Get().GetPlayer())
        {
            player->AddScore(10);
        }
        // Drop a reward sometimes (30% chance)
        float r = RandomRange(0.f, 1.f);
        if (r < 0.3f)
        {
            // spawn a simple reward
            auto reward = GetWorld()->SpawnActor<Reward>(GetActorLocation());
            (void)reward;
        }
        Spaceship::Blow();
    }
}
