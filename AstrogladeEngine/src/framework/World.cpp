#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"
namespace ly
{
	World::World(Application* owningApp)
		: mOwningApp{owningApp},
		mBeginPlay{false},
		mActors{},
		mPendingActors{},
		mGameStages{},
		mCurrentStage{mGameStages.end()}
	{

	}
	void World::BeginPlayInternal()
	{
		if (!mBeginPlay)
		{
			mBeginPlay = true;
			BeginPlay();
			InitGameStages();
			StartStages();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		for (shared<Actor> actor : mPendingActors)
		{
			mActors.push_back(actor);
			actor->BeginPlayIternal();
		}
		mPendingActors.clear();
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			iter->get()->TickInternal(deltaTime);
			++iter;
		}
		
		if (mCurrentStage != mGameStages.end())
		{
			mCurrentStage->get()->TickStage(deltaTime);
		}

		Tick(deltaTime);
	}
	void World::Render(sf::RenderWindow& window)
	{
		for (auto& actor : mActors)
		{
			actor->Render(window);
		}
		for (auto& actor : mActors)
		{
			actor->RenderOverlay(window);
		}
	}

	bool World::HandleEvent(const sf::Event& event)
	{
		bool handled = false;
		for (auto& actor : mActors)
		{
			handled = actor->HandleEvent(event) || handled;
		}
		return handled;
	}
	World::~World()
	{
	}
	sf::Vector2u World::GetWindowSize() const
	{
		return mOwningApp->GetWindowSize();
	}
	void World::CleanCycle()
	{
		for (auto iter = mActors.begin(); iter != mActors.end();)
		{
			if (iter->get()->IsPendingDestroy())
			{
				iter = mActors.erase(iter);
			}
			else
			{
				++iter;
			}
		}
		
	}

	void World::AddStage(const shared<GameStage>& newStage)
	{
		mGameStages.push_back(newStage);
	}
	void World::BeginPlay()
	{
	}
	void World::Tick(float deltaTime)
	{
	}
	void World::InitGameStages()
	{
	}

	void World::AllGameStageFinished()
	{

		LOG("All Stage Finished");
	}

	void World::NextGameStage()
	{
		if (mGameStages.empty() || mCurrentStage == mGameStages.end())
		{
			AllGameStageFinished();
			return;
		}
		mCurrentStage = mGameStages.erase(mCurrentStage);
		if (mCurrentStage != mGameStages.end())
		{
			mCurrentStage->get()->StartStage();
			mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
		}
		else
		{
			AllGameStageFinished();
		}
	}

	void World::StartStages()
	{
		// Reset iterator to a valid state relative to the current container
		mCurrentStage = mGameStages.end();
		if (mGameStages.empty())
		{
			return;
		}
		mCurrentStage = mGameStages.begin();
		mCurrentStage->get()->StartStage();
		mCurrentStage->get()->onStageFinished.BindAction(GetWeakRef(), &World::NextGameStage);
	}
}
