#include "player/PlayerManager.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    unique<PlayerManager> PlayerManager::sInstance{nullptr};

    PlayerManager& PlayerManager::Get()
    {
        if (!sInstance)
        {
            sInstance = unique<PlayerManager>{ new PlayerManager };
        }
        return *sInstance;
    }

    PlayerManager::PlayerManager() : mPlayer{ nullptr }
    {
    }

    Player* PlayerManager::CreateNewPlayer()
    {
        mPlayer = unique<Player>{ new Player };
        return mPlayer.get();
    }

    Player* PlayerManager::GetPlayer()
    {
        return mPlayer.get();
    }

    void PlayerManager::Reset()
    {
        if (!mPlayer)
        {
            mPlayer = unique<Player>{ new Player };
        }
        mPlayer->Reset();
    }

    weak<PlayerSpaceship> PlayerManager::SpawnSpaceship(World* world)
    {
        if (!mPlayer)
        {
            mPlayer = unique<Player>{ new Player };
        }

        auto windowSize = world->GetWindowSize();
        weak<PlayerSpaceship> sp = world->SpawnActor<PlayerSpaceship>();
        if (!sp.expired())
        {
            sp.lock()->SetActorLocation(sf::Vector2f(windowSize.x / 2.f, windowSize.y - 110.f));
            sp.lock()->SetActorRotation(0.f);
        }
        mPlayer->SetCurrentSpaceship(sp);
        return sp;
    }

    void PlayerManager::HandleSpaceshipDestroyed(World* world)
    {
        if (!mPlayer)
        {
            return;
        }
        int lives = mPlayer->GetLifeCount();
        if (lives > 0)
        {
            mPlayer->SetLifeCount(lives - 1);
            mPlayer->onLifeChange.Broadcast(mPlayer->GetLifeCount());
            SpawnSpaceship(world);
        }
        // else: no respawn, game over handled by level
    }
}
