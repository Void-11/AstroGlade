#include "Enemy/Vanguard.h"
#include "Enemy/VanguardStage.h"
#include "Enemy/EnemySpaceship.h"
#include "framework/World.h"
#include "player/Reward.h"
#include "weapon/LaserShooter.h"
namespace ly
{
	VanguardStage::VanguardStage(World* world)
		: GameStage{world},
		mSpawnInterval{2.f},
		mSwitchInterval{5.f},
		mSpawnDistanceToEdge{100.f},
		mLeftSpawnLoc{0.0f, 0.0f},
		mMiddleSpawnLoc{0.0f, 0.0f},
		mRightSpawnLoc{0.0f, 0.0f},
		mSpawnLoc{0.0f,0.0f},
		mRowsToSpawn{3},
		mRowSpawnCount{0},
		mVarguardsPerRow{3},
		mCurrentRowVanguardCount{0},
		mVanguardsKilled{0},
		mGuaranteedWeaponRewardKillCount{3},
		mGuaranteedWeaponRewardSpawned{false},
		mFinishedSpawning{false}
	{

	}

	void VanguardStage::StartStage()
	{
		mFinishedSpawning = false;
		mRowSpawnCount = 0;
		mCurrentRowVanguardCount = 0;
		mVanguardsKilled = 0;
		mGuaranteedWeaponRewardSpawned = false;
		auto windowSize = GetWorld()->GetWindowSize();
		mLeftSpawnLoc = sf::Vector2f{ mSpawnDistanceToEdge, -100.f };
		mMiddleSpawnLoc = sf::Vector2f{ windowSize.x / 2.f, -100.f };
		mRightSpawnLoc = sf::Vector2f(windowSize.x - mSpawnDistanceToEdge, -100.f);

		SwithRow();
	}

	void VanguardStage::TickStage(float deltaTime)
	{
		(void)deltaTime;
		if (mFinishedSpawning)
		{
			FinishStageIfTrackedActorsDestroyed();
		}
	}

	void VanguardStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimerHandle);
		TimerManager::Get().ClearTimer(mSwitchTimerHandle);
		ClearTrackedActors();
	}

	void VanguardStage::SpawnVanguard()
	{
		if (mFinishedSpawning)
		{
			return;
		}

		weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetActorLocation(mSpawnLoc);
		newVanguard.lock()->onEnemyKilled.BindAction(GetWeakRef(), &VanguardStage::VanguardKilled);
		TrackActor(newVanguard);
		++mCurrentRowVanguardCount;
		if (mCurrentRowVanguardCount == mVarguardsPerRow)
		{
			TimerManager::Get().ClearTimer(mSpawnTimerHandle);
			mSwitchTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwithRow, mSwitchInterval, false);
			mCurrentRowVanguardCount = 0;
		}
	}

	void VanguardStage::SwithRow()
	{
		if (mRowSpawnCount == mRowsToSpawn)
		{
			mFinishedSpawning = true;
			TimerManager::Get().ClearTimer(mSpawnTimerHandle);
			TimerManager::Get().ClearTimer(mSwitchTimerHandle);
			FinishStageIfTrackedActorsDestroyed();
			return;
		}

		if (mRowSpawnCount == 0)
		{
			mSpawnLoc = mLeftSpawnLoc;
		}
		else if (mRowSpawnCount == 1)
		{
			mSpawnLoc = mMiddleSpawnLoc;
		}
		else
		{
			mSpawnLoc = mRightSpawnLoc;
		}

		mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);
		
		++mRowSpawnCount;
	}

	void VanguardStage::VanguardKilled(EnemySpaceship* enemy)
	{
		++mVanguardsKilled;
		if (mGuaranteedWeaponRewardSpawned || mVanguardsKilled < mGuaranteedWeaponRewardKillCount || !enemy)
		{
			return;
		}

		weak<Reward> reward = CreateThreewayShooterReward(GetWorld());
		if (!reward.expired())
		{
			reward.lock()->SetActorLocation(enemy->GetActorLocation());
		}

		enemy->SetRewardSpawnWeight(0.f);
		mGuaranteedWeaponRewardSpawned = true;
	}
}
