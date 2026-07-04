#include "gameplay/GameStage.h"
#include "framework/Core.h"
#include "framework/Actor.h"
namespace ly
{
	GameStage::GameStage(World* world)
		: mWorld{world},
		mStageFinished{false},
		mTrackedActors{}
	{

	}
	
	void GameStage::StartStage()
	{
		LOG("Stage Started");
	}
	
	void GameStage::TickStage(float deltaTime)
	{
		
	}
	
	void GameStage::FinishStage()
	{
		if (mStageFinished)
		{
			return;
		}

		mStageFinished = true;
		StageFinished();
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

	bool GameStage::HasActiveTrackedActors()
	{
		for (auto iter = mTrackedActors.begin(); iter != mTrackedActors.end();)
		{
			shared<Actor> actor = iter->lock();
			if (!actor || actor->IsPendingDestroy())
			{
				iter = mTrackedActors.erase(iter);
			}
			else
			{
				++iter;
			}
		}

		return !mTrackedActors.empty();
	}

	void GameStage::StageFinished()
	{
		LOG("Stage Finished");
	}
}
