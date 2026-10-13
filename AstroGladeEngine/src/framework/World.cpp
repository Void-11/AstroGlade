#include <algorithm>
#include <typeinfo>
#include <utility>

#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/Log.h"
#include "gameplay/GameStage.h"
#include "widgets/HUD.h"
namespace ly
{
	World::World(Application* owningApp)
		: mOwningApp{owningApp}
	{

	}

	void World::BeginPlayInternal()
	{
		if (!mBeganPlay)
		{
			mBeganPlay = true;
			BeginPlay();
			InitGameStages();
			StartStages();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		// Take the pending list first: actors spawned while beginning play are queued for the
		// next tick instead of invalidating this loop.
		for (const shared<Actor>& actor : std::exchange(mPendingActors, {}))
		{
			mActors.push_back(actor);
			actor->BeginPlayInternal();
		}

		if (!mIsPaused)
		{
			for (const shared<Actor>& actor : mActors)
			{
				actor->TickInternal(deltaTime);
				if (mIsPaused)
				{
					break;
				}
			}

			if (!mIsPaused && mCurrentStage != mGameStages.end())
			{
				// Hold a reference: finishing the stage removes it from mGameStages.
				const shared<GameStage> currentStage = *mCurrentStage;
				currentStage->TickStage(deltaTime);
			}

			if (!mIsPaused)
			{
				Tick(deltaTime);
			}
		}

		if (mHUD)
		{
			if (!mHUD->HasInit())
			{
				mHUD->NativeInit(mOwningApp->GetWindow());
			}
			mHUD->Tick(deltaTime);
		}

	}

	void World::Render(sf::RenderWindow& window)
	{
		for (const shared<Actor>& actor : mActors)
		{
			actor->Render(window);
		}

		RenderHUD(window);
	}

	sf::Vector2u World::GetWindowSize() const
	{
		return mOwningApp->GetWindowSize();
	}

	void World::CleanCycle()
	{
		mActors.erase(
			std::remove_if(mActors.begin(), mActors.end(), [](const shared<Actor>& actor) { return actor->IsPendingDestroy(); }),
			mActors.end());
	}

	void World::AddStage(const shared<GameStage>& newStage)
	{
		mGameStages.push_back(newStage);
	}

	bool World::DispatchEvent(const sf::Event& event)
	{
		if (mHUD)
		{
			return mHUD->HandleEvent(event);
		}
		return false;
	}

	void World::BeginPlay()
	{

	}

	void World::Tick([[maybe_unused]] float deltaTime)
	{

	}

	void World::RenderHUD(sf::RenderWindow& window)
	{
		if (mHUD)
		{
			mHUD->Draw(window);
		}
	}

	void World::InitGameStages()
	{

	}

	void World::AllGameStageFinished()
	{
		LogDebug("All stages finished");
	}

	void World::OnGameStageStarted([[maybe_unused]] GameStage& startedStage)
	{
	}

	void World::OnGameStageFinished([[maybe_unused]] GameStage& finishedStage)
	{
	}

	void World::NextGameStage()
	{
		if (mCurrentStage == mGameStages.end())
		{
			return;
		}

		LogDebug("Stage finished: ", typeid(**mCurrentStage).name());
		OnGameStageFinished(**mCurrentStage);

		mCurrentStage = mGameStages.erase(mCurrentStage);
		if (mCurrentStage != mGameStages.end())
		{
			BeginStage(**mCurrentStage);
		}
		else
		{
			AllGameStageFinished();
		}
	}

	void World::StartStages()
	{
		mCurrentStage = mGameStages.begin();
		if (mCurrentStage != mGameStages.end())
		{
			BeginStage(**mCurrentStage);
		}
	}

	void World::BeginStage(GameStage& stage)
	{
		// Logged here rather than in GameStage::StartStage, which the stages override without calling.
		LogDebug("Stage started: ", typeid(stage).name());
		OnGameStageStarted(stage);
		stage.StartStage();
		stage.onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
	}
}
