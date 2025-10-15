#pragma once
#include "gameplay/GameStage.h"

namespace ly
{
    class ChaosStage : public GameStage
    {
    public:
        ChaosStage(World* world);
        virtual void StartStage() override;
        virtual void TickStage(float deltaTime) override;
        virtual void StageFinished() override;
    private:
        int mSpawned;
        int mTarget;
        float mTimer;
        void SpawnRandomEnemy();
    };
}