#include "Enemy/ChaosStage.h"
#include "framework/World.h"
#include "Enemy/Vanguard.h"
#include "Enemy/TwinBlade.h"
#include "Enemy/Hexagon.h"
#include "framework/MathUtility.h"

namespace ly
{
    ChaosStage::ChaosStage(World* world) : GameStage{world}, mSpawned{0}, mTarget{25}, mTimer{0.f}
    {
    }

    void ChaosStage::StartStage()
    {
    }

    void ChaosStage::TickStage(float deltaTime)
    {
        mTimer += deltaTime;
        if (mSpawned < mTarget && mTimer > 0.4f)
        {
            mTimer = 0.f;
            SpawnRandomEnemy();
            ++mSpawned;
        }
        if (mSpawned >= mTarget)
        {
            FinishStage();
        }
    }

    void ChaosStage::StageFinished()
    {
    }

    void ChaosStage::SpawnRandomEnemy()
    {
        int r = (int)RandomRange(0.f, 3.f);
        switch (r)
        {
        case 0: GetWorld()->SpawnActor<Vanguard>(); break;
        case 1: GetWorld()->SpawnActor<TwinBlade>(); break;
        default: GetWorld()->SpawnActor<Hexagon>(); break;
        }
    }
}