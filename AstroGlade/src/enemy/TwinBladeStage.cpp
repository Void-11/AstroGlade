#include "Enemy/TwinBladeStage.h"
#include "Enemy/TwinBlade.h"
#include "framework/World.h"

#include "weapon/LaserShooter.h"
namespace ly
{
	TwinBladeStage::TwinBladeStage(World* world)
		: GameStage{world},
		mSpawnInterval{1.5f},
		mSpawnDistanceToCenter{100.f},
		mLeftSpawnLoc{world->GetWindowSize().x/2.f - mSpawnDistanceToCenter, -100.f},
		mRightSpawnLoc{world->GetWindowSize().x/2.f + mSpawnDistanceToCenter, -100.f},
		mSpawnLoc{mLeftSpawnLoc},
		mSpawnAmt{10},
		mCurrentSpawnCount{0},
		mFinishedSpawning{false}
	{
	}

	void TwinBladeStage::StartStage()
	{
		mFinishedSpawning = false;
		mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &TwinBladeStage::SpawnTwinBlade, mSpawnInterval, true);
	}

	void TwinBladeStage::TickStage(float deltaTime)
	{
		(void)deltaTime;
		if (mFinishedSpawning)
		{
			FinishStageIfTrackedActorsDestroyed();
		}
	}

	void TwinBladeStage::SpawnTwinBlade()
	{
		if (mFinishedSpawning)
		{
			return;
		}

		weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
		newTwinBlade.lock()->SetActorLocation(mSpawnLoc);
		TrackActor(newTwinBlade);
		if (mSpawnLoc == mLeftSpawnLoc)
		{
			mSpawnLoc = mRightSpawnLoc;
		}
		else
		{
			mSpawnLoc = mLeftSpawnLoc;
		}

		++mCurrentSpawnCount;
		if (mCurrentSpawnCount == mSpawnAmt)
		{
			mFinishedSpawning = true;
			TimerManager::Get().ClearTimer(mSpawnTimerHandle);
			FinishStageIfTrackedActorsDestroyed();
		}
	}

	void TwinBladeStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimerHandle);
		ClearTrackedActors();
	}
}
