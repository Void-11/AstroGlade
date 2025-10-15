#include "Enemy/BossStage.h"
#include "enemy/Boss.h"
#include "framework/World.h"

namespace ly
{
    BossStage::BossStage(World* world) : GameStage{world}
    {
    }

    void BossStage::StartStage()
    {
        mBoss = GetWorld()->SpawnActor<Boss>();
    }

    void BossStage::TickStage(float deltaTime)
    {
        (void)deltaTime;
        if (mBoss.expired())
        {
            FinishStage();
        }
    }

    void BossStage::StageFinished()
    {
    }
}