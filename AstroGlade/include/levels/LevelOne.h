#pragma once
#include "framework/World.h"
#include "framework/TimerManager.h"

namespace ly
{
    class PlayerSpaceship;
    class GameplayHUD;
    class LevelOne : public World
    {
    public:
        
       LevelOne(Application* owningApp);
        
    private:
        
        virtual void BeginPlay() override;
        virtual void Tick(float deltaTime) override;
        virtual void InitGameStages() override;
        virtual void AllGameStageFinished() override;

        void SpawnCosmetics();
        void SetupPlayer();
        void CheckRespawn();
        void GameOver();
        void QuitGame();
        void Restart();

        weak<PlayerSpaceship> mPlayerSpaceship;
        weak<GameplayHUD> mGameplayHUD;

        TimerHandle timerHandle_Test;
    };
}
