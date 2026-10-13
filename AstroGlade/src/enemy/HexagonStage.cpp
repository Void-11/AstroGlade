#include <initializer_list>

#include "enemy/Hexagon.h"
#include "enemy/HexagonStage.h"
#include "framework/World.h"

namespace ly
{
	HexagonStage::HexagonStage(World* world)
		: GameStage{ world },
		mMidSpawnLoc{ static_cast<float>(world->GetWindowSize().x) / 2.f, -100.f },
		mLeftSpawnLoc{ static_cast<float>(world->GetWindowSize().x) / 2.f - mSideSpawnOffset, -100.f - mSideSpawnOffset },
		mRightSpawnLoc{ static_cast<float>(world->GetWindowSize().x) / 2.f + mSideSpawnOffset, -100.f - mSideSpawnOffset }
	{
	}

	void HexagonStage::StartStage()
	{
		mSpawnTimer = TimerManager::Get().SetTimer(GetWeakRef(), &HexagonStage::SpawnHexagon, mSpawnInterval, true);
	}

	void HexagonStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimer);
	}

	void HexagonStage::SpawnHexagon()
	{
		if (IsSpawningFinished())
		{
			return;
		}

		for (const sf::Vector2f& spawnLocation : { mMidSpawnLoc, mLeftSpawnLoc, mRightSpawnLoc })
		{
			const weak<Hexagon> newHexagon = GetWorld()->SpawnActor<Hexagon>();
			if (const shared<Hexagon> hexagon = newHexagon.lock())
			{
				hexagon->SetActorLocation(spawnLocation);
			}
			TrackActor(newHexagon);
		}

		if (++mCurrentSpawnCount == mSpawnGroupAmt)
		{
			TimerManager::Get().ClearTimer(mSpawnTimer);
			FinishSpawning();
		}
	}
}
