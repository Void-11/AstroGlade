#include "Enemy/SpawnLocations.h"
#include "Enemy/UFO.h"
#include "Enemy/UFOStage.h"
#include "framework/World.h"
#include "gameplay/ResolutionScale.h"

namespace ly
{
	UFOStage::UFOStage(World* world)
		: GameStage{ world }
	{
	}

	void UFOStage::StartStage()
	{
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &UFOStage::SpawnUFO, mSpawnInterval, true);
	}

	void UFOStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimer);
	}

	void UFOStage::SpawnUFO()
	{
		if (IsSpawningFinished())
		{
			return;
		}

		const sf::Vector2u windowSize = GetWorld()->GetWindowSize();
		const sf::Vector2f spawnLoc = RandomSideSpawnLocation(windowSize);
		const sf::Vector2f spawnVelocity = ScaleToResolution(DirectionToWindowCenter(spawnLoc, windowSize) * mUFOSpeed, windowSize);

		const weak<UFO> newUFO = GetWorld()->SpawnActor<UFO>(spawnVelocity);
		if (const shared<UFO> ufo = newUFO.lock())
		{
			ufo->SetActorLocation(spawnLoc);
		}
		TrackActor(newUFO);

		if (++mCurrentSpawnAmt == mSpawnAmt)
		{
			TimerManager::Get().ClearTimer(mSpawnTimer);
			FinishSpawning();
		}
	}
}
