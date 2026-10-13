#ifndef ASTROGLADE_ENGINE_FRAMEWORK_PHYSICSSYSTEM_H
#define ASTROGLADE_ENGINE_FRAMEWORK_PHYSICSSYSTEM_H

#include <box2d/b2_world.h>

#include "framework/Core.h"
namespace ly
{
	class Actor;

	class PhysicsContactListener : public b2ContactListener
	{
		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
	};

	class PhysicsSystem
	{
	public:
		[[nodiscard]] static PhysicsSystem& Get();

		PhysicsSystem(const PhysicsSystem&) = delete;
		PhysicsSystem& operator=(const PhysicsSystem&) = delete;

		void Step(float deltaTime);
		[[nodiscard]] b2Body* AddListener(Actor* listener);
		void RemoveListener(b2Body* bodyToRemove);

		[[nodiscard]] float GetPhysicsScale() const { return kPhysicsScale; }

		// Discards every body by rebuilding the physics world. Called when a new World starts playing.
		void Reset();

	private:
		PhysicsSystem();

		void ProcessPendingRemoveListeners();

		static constexpr float kPhysicsScale = 0.01f;
		static constexpr int kVelocityIterations = 8;
		static constexpr int kPositionIterations = 3;

		// Declared before the world so it outlives the world that points to it.
		PhysicsContactListener mContactListener;
		unique<b2World> mPhysicsWorld;

		Set<b2Body*> mPendingRemoveListeners;
	};
}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_PHYSICSSYSTEM_H
