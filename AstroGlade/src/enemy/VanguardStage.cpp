#include "enemy/EnemySpaceship.h"
#include "enemy/Vanguard.h"
#include "enemy/VanguardStage.h"
#include "framework/World.h"
#include "player/Reward.h"

namespace ly
{
	VanguardStage::VanguardStage(World* world)
		: GameStage{ world }
	{
	}

	void VanguardStage::StartStage()
	{
		mRowSpawnCount = 0;
		mCurrentRowVanguardCount = 0;
		mVanguardsKilled = 0;
		mGuaranteedWeaponRewardSpawned = false;

		const auto windowWidth = static_cast<float>(GetWorld()->GetWindowSize().x);
		mLeftSpawnLoc = sf::Vector2f{ mSpawnDistanceToEdge, -100.f };
		mMiddleSpawnLoc = sf::Vector2f{ windowWidth / 2.f, -100.f };
		mRightSpawnLoc = sf::Vector2f{ windowWidth - mSpawnDistanceToEdge, -100.f };

		SwitchRow();
	}

	void VanguardStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimerHandle);
		TimerManager::Get().ClearTimer(mSwitchTimerHandle);
	}

	void VanguardStage::SpawnVanguard()
	{
		if (IsSpawningFinished())
		{
			return;
		}

		const weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		if (const shared<Vanguard> vanguard = newVanguard.lock())
		{
			vanguard->SetActorLocation(mSpawnLoc);
			vanguard->onEnemyKilled.BindAction(GetWeakRef(), &VanguardStage::VanguardKilled);
		}
		TrackActor(newVanguard);

		++mCurrentRowVanguardCount;
		if (mCurrentRowVanguardCount == mVanguardsPerRow)
		{
			TimerManager::Get().ClearTimer(mSpawnTimerHandle);
			mSwitchTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);
			mCurrentRowVanguardCount = 0;
		}
	}

	void VanguardStage::SwitchRow()
	{
		if (mRowSpawnCount == mRowsToSpawn)
		{
			TimerManager::Get().ClearTimer(mSpawnTimerHandle);
			TimerManager::Get().ClearTimer(mSwitchTimerHandle);
			FinishSpawning();
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

		if (const shared<Reward> reward = CreateThreewayShooterReward(GetWorld()).lock())
		{
			reward->SetActorLocation(enemy->GetActorLocation());
		}

		enemy->SetRewardSpawnWeight(0.f);
		mGuaranteedWeaponRewardSpawned = true;
	}
}
