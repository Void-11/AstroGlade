#include <algorithm>

#include "gameplay/GameStage.h"
#include "framework/Actor.h"

namespace ly
{
	GameStage::GameStage(World* world)
		: mWorld{ world }
	{
	}

	void GameStage::StartStage()
	{
	}

	void GameStage::TickStage([[maybe_unused]] float deltaTime)
	{
		if (mSpawningFinished)
		{
			FinishStageIfTrackedActorsDestroyed();
		}
	}

	void GameStage::FinishStage()
	{
		if (mStageFinished)
		{
			return;
		}

		mStageFinished = true;
		StageFinished();
		ClearTrackedActors();
		onStageFinished.Broadcast();
	}

	void GameStage::TrackActor(const weak<Actor>& actor)
	{
		if (!actor.expired())
		{
			mTrackedActors.push_back(actor);
		}
	}

	void GameStage::FinishStageIfTrackedActorsDestroyed()
	{
		if (!HasActiveTrackedActors())
		{
			FinishStage();
		}
	}

	void GameStage::ClearTrackedActors()
	{
		mTrackedActors.clear();
	}

	void GameStage::FinishSpawning()
	{
		mSpawningFinished = true;
		FinishStageIfTrackedActorsDestroyed();
	}

	bool GameStage::HasActiveTrackedActors()
	{
		const auto isGone = [](const weak<Actor>& trackedActor)
		{
			const shared<Actor> actor = trackedActor.lock();
			return !actor || actor->IsPendingDestroy();
		};

		mTrackedActors.erase(std::remove_if(mTrackedActors.begin(), mTrackedActors.end(), isGone), mTrackedActors.end());
		return !mTrackedActors.empty();
	}

	void GameStage::StageFinished()
	{
	}
}
