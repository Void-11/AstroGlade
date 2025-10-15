#pragma once
#include "gameplay/GameStage.h"

namespace ly
{
    class BossStage : public GameStage
    {
    public:
        BossStage(World* world);
        virtual void StartStage() override;
        virtual void TickStage(float deltaTime) override;
        virtual void StageFinished() override;
    private:
        weak<class Boss> mBoss;
    };
}