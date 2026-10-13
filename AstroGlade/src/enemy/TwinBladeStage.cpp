#include "enemy/TwinBlade.h"
#include "enemy/TwinBladeStage.h"
#include "framework/World.h"

namespace ly
{
	TwinBladeStage::TwinBladeStage(World* world)
		: GameStage{ world },
		mLeftSpawnLoc{ static_cast<float>(world->GetWindowSize().x) / 2.f - mSpawnDistanceToCenter, -100.f },
		mRightSpawnLoc{ static_cast<float>(world->GetWindowSize().x) / 2.f + mSpawnDistanceToCenter, -100.f },
		mSpawnLoc{ mLeftSpawnLoc }
	{
	}

	void TwinBladeStage::StartStage()
	{
		mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &TwinBladeStage::SpawnTwinBlade, mSpawnInterval, true);
	}

	void TwinBladeStage::SpawnTwinBlade()
	{
		if (IsSpawningFinished())
		{
			return;
		}

		const weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
		if (const shared<TwinBlade> twinBlade = newTwinBlade.lock())
		{
			twinBlade->SetActorLocation(mSpawnLoc);
		}
		TrackActor(newTwinBlade);

		mSpawnLoc = (mSpawnLoc == mLeftSpawnLoc) ? mRightSpawnLoc : mLeftSpawnLoc;

		++mCurrentSpawnCount;
		if (mCurrentSpawnCount == mSpawnAmt)
		{
			TimerManager::Get().ClearTimer(mSpawnTimerHandle);
			FinishSpawning();
		}
	}

	void TwinBladeStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimerHandle);
	}
}
