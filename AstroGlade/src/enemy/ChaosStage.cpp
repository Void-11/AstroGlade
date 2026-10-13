#include <algorithm>

#include "enemy/ChaosStage.h"
#include "enemy/Hexagon.h"
#include "enemy/SpawnLocations.h"
#include "enemy/TwinBlade.h"
#include "enemy/UFO.h"
#include "enemy/Vanguard.h"
#include "framework/World.h"
#include "gameplay/ResolutionScale.h"

namespace ly
{
	namespace
	{
		constexpr float kChaosEnemyHealth = 100.f;

		// Chaos UFOs are deliberately slow, so they linger on screen and keep firing, which makes the stage harder.
		// The speed was tuned by playing fullscreen at 2560x1440, where it is 200 px/s. Converted to reference-window
		// units per axis, it scales like every other speed, so the stage is equally hard on every screen.
		constexpr float kChaosUFOTunedSpeed = 200.f;
		constexpr float kChaosUFOTuningWindowWidth = 2560.f;
		constexpr float kChaosUFOTuningWindowHeight = 1440.f;
		constexpr float kChaosUFOSpeedX = kChaosUFOTunedSpeed * kReferenceWindowWidth / kChaosUFOTuningWindowWidth;
		constexpr float kChaosUFOSpeedY = kChaosUFOTunedSpeed * kReferenceWindowHeight / kChaosUFOTuningWindowHeight;

		// Places a freshly spawned chaos enemy and gives it the shared chaos health.
		template<typename EnemyType>
		void SetUpChaosEnemy(const weak<EnemyType>& enemy, const sf::Vector2f& location)
		{
			if (const shared<EnemyType> spawnedEnemy = enemy.lock())
			{
				spawnedEnemy->SetActorLocation(location);
				spawnedEnemy->GetHealthComp().SetInitialHealth(kChaosEnemyHealth, kChaosEnemyHealth);
			}
		}
	}

	ChaosStage::ChaosStage(World* world)
		: GameStage{ world }
	{
	}

	void ChaosStage::StartStage()
	{
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
		mDifficultTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::IncreaseDifficulty, mSpawnIntervalDecrementInterval, true);
		mStageDurationTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::StageDurationReached, mStageDuration);
	}

	void ChaosStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mDifficultTimerHandle);
		TimerManager::Get().ClearTimer(mSpawnTimer);
		TimerManager::Get().ClearTimer(mStageDurationTimer);
	}

	void ChaosStage::SpawnVanguard()
	{
		if (IsSpawningFinished())
		{
			return;
		}

		const weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		SetUpChaosEnemy(newVanguard, RandomTopSpawnLocation(GetWorld()->GetWindowSize()));
		TrackActor(newVanguard);
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnTwinBlade, mSpawnInterval);
	}

	void ChaosStage::SpawnTwinBlade()
	{
		if (IsSpawningFinished())
		{
			return;
		}

		const weak<TwinBlade> newTwinBlade = GetWorld()->SpawnActor<TwinBlade>();
		SetUpChaosEnemy(newTwinBlade, RandomTopSpawnLocation(GetWorld()->GetWindowSize()));
		TrackActor(newTwinBlade);
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnHexagon, mSpawnInterval);
	}

	void ChaosStage::SpawnHexagon()
	{
		if (IsSpawningFinished())
		{
			return;
		}

		const weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
		SetUpChaosEnemy(newHexagon, RandomTopSpawnLocation(GetWorld()->GetWindowSize()));
		TrackActor(newHexagon);
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnUFO, mSpawnInterval);
	}

	void ChaosStage::SpawnUFO()
	{
		if (IsSpawningFinished())
		{
			return;
		}

		const sf::Vector2u windowSize = GetWorld()->GetWindowSize();
		const sf::Vector2f spawnLoc = RandomSideSpawnLocation(windowSize);
		const sf::Vector2f direction = DirectionToWindowCenter(spawnLoc, windowSize);
		const sf::Vector2f velocity = ScaleToResolution({ direction.x * kChaosUFOSpeedX, direction.y * kChaosUFOSpeedY }, windowSize);

		const weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(velocity);
		SetUpChaosEnemy(newUFO, spawnLoc);
		TrackActor(newUFO);

		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &ChaosStage::SpawnVanguard, mSpawnInterval);
	}

	void ChaosStage::IncreaseDifficulty()
	{
		if (IsSpawningFinished())
		{
			return;
		}

		mSpawnInterval = std::max(mSpawnInterval - mSpawnIntervalDecrement, mMinSpawnInterval);
	}

	void ChaosStage::StageDurationReached()
	{
		TimerManager::Get().ClearTimer(mDifficultTimerHandle);
		TimerManager::Get().ClearTimer(mSpawnTimer);
		FinishSpawning();
	}
}
