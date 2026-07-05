#include "Enemy/ChaosStage.h"
#include "Enemy/Vanguard.h"
#include "Enemy/TwinBlade.h"
#include "Enemy/Hexagon.h"
#include "Enemy/UFO.h"

#include "framework/MathUtility.h"
#include "framework/World.h"

#include "weapon/LaserShooter.h"
namespace ly
{
	namespace
	{
		constexpr float kChaosEnemyHealth = 100.f;

		template<typename EnemyType>
		void SetChaosEnemyHealth(const weak<EnemyType>& enemy)
		{
			if (!enemy.expired())
			{
				enemy.lock()->GetHealthComp().SetInitialHealth(kChaosEnemyHealth, kChaosEnemyHealth);
			}
		}
	}

	ChaosStage::ChaosStage(World* world)
		: GameStage{world},
		mSpawnInterval{4.f},
		mMinSpawnInterval{0.8f},
		mSpawnIntervalDecrement{0.5f},
		mSpawnIntervalDecrmentInterval{5.f},
		mStageDuration{60.f},
		mFinishedSpawning{false}
	{
	}

	void ChaosStage::StartStage()
	{
		mFinishedSpawning = false;
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
		mDifficultTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::IncreseDifficulity, mSpawnIntervalDecrmentInterval, true);
		mStageDurationTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::StageDurationReached, mStageDuration);
	}

	void ChaosStage::TickStage(float deltaTime)
	{
		(void)deltaTime;
		if (mFinishedSpawning)
		{
			FinishStageIfTrackedActorsDestroyed();
		}
	}

	void ChaosStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mDifficultTimerHandle);
		TimerManager::Get().ClearTimer(mSpawnTimer);
		TimerManager::Get().ClearTimer(mStageDurationTimer);
		ClearTrackedActors();
	}
	void ChaosStage::SpawnVanguard()
	{
		if (mFinishedSpawning)
		{
			return;
		}

		weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		newVanguard.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		SetChaosEnemyHealth(newVanguard);
		TrackActor(newVanguard);
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnTwinBlade, mSpawnInterval);
	}
	void ChaosStage::SpawnTwinBlade()
	{
		if (mFinishedSpawning)
		{
			return;
		}

		weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
		newTwinBlade.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		SetChaosEnemyHealth(newTwinBlade);
		TrackActor(newTwinBlade);
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnHexgon, mSpawnInterval);
	}
	
	void ChaosStage::SpawnHexgon()
	{
		if (mFinishedSpawning)
		{
			return;
		}

		weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
		newHexagon.lock()->SetActorLocation(GetRandomSpawnLocationTop());
		SetChaosEnemyHealth(newHexagon);
		TrackActor(newHexagon);
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnUFO, mSpawnInterval);
	}

	void ChaosStage::SpawnUFO()
	{
		if (mFinishedSpawning)
		{
			return;
		}

		sf::Vector2f spawnLoc = GetRandomSpawnLocationSide();

		auto windowSize = GetWorld()->GetWindowSize();
		sf::Vector2f center = sf::Vector2f{ windowSize.x / 2.f, windowSize.y / 2.f };
		sf::Vector2f dirToCenter = center - spawnLoc;
		Normalize(dirToCenter);
		
		weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(dirToCenter * 200.f);
		newUFO.lock()->SetActorLocation(spawnLoc);
		SetChaosEnemyHealth(newUFO);
		TrackActor(newUFO);

		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
	}

	void ChaosStage::IncreseDifficulity()
	{
		if (mFinishedSpawning)
		{
			return;
		}

		mSpawnInterval -= mSpawnIntervalDecrement;
		if (mSpawnInterval < mMinSpawnInterval)
		{
			mSpawnInterval = mMinSpawnInterval;
		}
	}

	void ChaosStage::StageDurationReached()
	{
		mFinishedSpawning = true;
		TimerManager::Get().ClearTimer(mDifficultTimerHandle);
		TimerManager::Get().ClearTimer(mSpawnTimer);
		FinishStageIfTrackedActorsDestroyed();
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationTop() const
	{
		auto windowSize = GetWorld()->GetWindowSize();
		float spawnX = RandomRange(100.f, windowSize.x - 100.f);
		float spawnY = -100.f;

		return { spawnX, spawnY };
	}

	sf::Vector2f ChaosStage::GetRandomSpawnLocationSide() const
	{
		auto windowSize = GetWorld()->GetWindowSize();
		float spawnLeft = RandomRange(-1, 1);
		float spawnLocX = 0;

		if (spawnLeft < 0)
		{
			spawnLocX = windowSize.x + 100.f;
		}
		else
		{
			spawnLocX = -100.f;
		}

		float spawnLocY = RandomRange(0, windowSize.y);
		return sf::Vector2f{ spawnLocX, spawnLocY };
	}
}
