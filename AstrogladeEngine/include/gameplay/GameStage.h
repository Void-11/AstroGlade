#pragma once

#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
	class Actor;
	class World;
	class GameStage : public Object
	{
	public:
		GameStage(World* world);
		const World* GetWorld() const { return mWorld; }
		World* GetWorld() { return mWorld; }

		Delegate<> onStageFinished;

		virtual void StartStage();
		virtual void TickStage(float deltaTime);
		void FinishStage();
		bool IsStageFinished() const { return mStageFinished; }
	protected:
		void TrackActor(const weak<Actor>& actor);
		void FinishStageIfTrackedActorsDestroyed();
		void ClearTrackedActors();
	private:
		World* mWorld;
		bool mStageFinished;
		List<weak<Actor>> mTrackedActors;
		virtual void StageFinished();
		bool HasActiveTrackedActors();
	};
}
