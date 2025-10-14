#pragma once
#include "framework/Core.h"
#include "player/Player.h"

namespace ly
{
    class World;
    class PlayerManager
    {
    public:
        static PlayerManager& Get();

        Player* CreateNewPlayer();
        Player* GetPlayer();
        void Reset();

        // Spawns or respawns player spaceship
        weak<PlayerSpaceship> SpawnSpaceship(World* world);

        // Called when the current spaceship no longer exists
        void HandleSpaceshipDestroyed(World* world);

    private:
        PlayerManager();
        static unique<PlayerManager> sInstance;
        unique<Player> mPlayer;
    };
}
