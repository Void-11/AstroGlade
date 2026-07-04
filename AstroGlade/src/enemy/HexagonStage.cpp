#include "Enemy/Hexagon.h"
#include "Enemy/HexagonStage.h"
#include "framework/World.h"

#include "weapon/LaserShooter.h"

namespace ly
{
	HexagonStage::HexagonStage(World* world)
		: GameStage{world},
		mSpawnInterval{5.f},
		mSideSpawnOffset{80.f},
		mSpawnGroupAmt{5},
		mCurrentSpawnCount{0},
		mFinishedSpawning{false},
		mMidSpawnLoc{world->GetWindowSize().x/2.f, -100.f},
		mRightSpawnLoc{world->GetWindowSize().x/2.f + mSideSpawnOffset, -100.f - mSideSpawnOffset},
		mLeftSpawnLoc{world->GetWindowSize().x/2.f - mSideSpawnOffset, -100.f - mSideSpawnOffset}
	{
	}
	
	void HexagonStage::StartStage()
	{
		mFinishedSpawning = false;
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &HexagonStage::SpawnHexagon, mSpawnInterval, true);
	}

	void HexagonStage::TickStage(float deltaTime)
	{
		(void)deltaTime;
		if (mFinishedSpawning)
		{
			FinishStageIfTrackedActorsDestroyed();
		}
	}
	
	void HexagonStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimer);
		ClearTrackedActors();
	}

	void HexagonStage::SpawnHexagon()
	{
		if (mFinishedSpawning)
		{
			return;
		}

		weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(mMidSpawnLoc);
		TrackActor(newHexagon);

		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(mLeftSpawnLoc);
		TrackActor(newHexagon);
		newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(mRightSpawnLoc);
		TrackActor(newHexagon);
	
		if (++mCurrentSpawnCount == mSpawnGroupAmt)
		{
			mFinishedSpawning = true;
			TimerManager::Get().ClearTimer(mSpawnTimer);
			FinishStageIfTrackedActorsDestroyed();
		}
	}
}
