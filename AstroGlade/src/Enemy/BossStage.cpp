#include "Enemy/Boss.h"
#include "Enemy/BossStage.h"
#include "framework/World.h"

namespace ly
{
	BossStage::BossStage(World* world)
		: GameStage{ world }
	{
	}

	void BossStage::StartStage()
	{
		if (const shared<Boss> boss = GetWorld()->SpawnActor<Boss>().lock())
		{
			const sf::Vector2u windowSize = GetWorld()->GetWindowSize();
			boss->SetActorLocation({ static_cast<float>(windowSize.x) / 2.f, 200.f });
			boss->onActorDestroyed.BindAction(GetWeakRef(), &BossStage::BossDestroyed);
		}
	}

	void BossStage::BossDestroyed([[maybe_unused]] Actor* bossActor)
	{
		FinishStage();
	}
}
