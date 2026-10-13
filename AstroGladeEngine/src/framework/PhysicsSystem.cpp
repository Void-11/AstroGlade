#include <cstdint>

#include <box2d/b2_body.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include "framework/MathUtility.h"
namespace ly
{
	namespace
	{
		// Box2D stores user data as an integer, so actors round-trip through std::uintptr_t.
		// The unavoidable reinterpret_casts are kept in these two helpers (CG I.30).
		std::uintptr_t ToUserData(Actor* actor)
		{
			return reinterpret_cast<std::uintptr_t>(actor);
		}

		Actor* GetFixtureActor(b2Fixture* fixture)
		{
			if (!fixture || !fixture->GetBody())
			{
				return nullptr;
			}

			return reinterpret_cast<Actor*>(fixture->GetBody()->GetUserData().pointer);
		}

		bool CanReceiveOverlap(const Actor* actor)
		{
			return actor && !actor->IsPendingDestroy();
		}

		unique<b2World> CreatePhysicsWorld(b2ContactListener& contactListener)
		{
			auto physicsWorld = std::make_unique<b2World>(b2Vec2{ 0.f, 0.f });
			physicsWorld->SetContactListener(&contactListener);
			physicsWorld->SetAllowSleeping(false);
			return physicsWorld;
		}
	}

	PhysicsSystem& PhysicsSystem::Get()
	{
		static PhysicsSystem physicsSystem;
		return physicsSystem;
	}

	void PhysicsSystem::Step(float deltaTime)
	{
		ProcessPendingRemoveListeners();
		mPhysicsWorld->Step(deltaTime, kVelocityIterations, kPositionIterations);
	}

	b2Body* PhysicsSystem::AddListener(Actor* listener)
	{
		if (listener->IsPendingDestroy()) return nullptr;

		const sf::Vector2f location = listener->GetActorLocation();

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.userData.pointer = ToUserData(listener);
		bodyDef.position.Set(location.x * GetPhysicsScale(), location.y * GetPhysicsScale());
		bodyDef.angle = DegreesToRadians(listener->GetActorRotation());

		b2Body* body = mPhysicsWorld->CreateBody(&bodyDef);

		b2PolygonShape shape;
		const sf::FloatRect bound = listener->GetActorGlobalBounds();
		shape.SetAsBox(bound.width / 2.f * GetPhysicsScale(), bound.height / 2.f * GetPhysicsScale());

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;

		body->CreateFixture(&fixtureDef);

		return body;
	}

	void PhysicsSystem::RemoveListener(b2Body* bodyToRemove)
	{
		// Detach the actor right away; the body itself is destroyed before the next step.
		bodyToRemove->GetUserData().pointer = ToUserData(nullptr);
		mPendingRemoveListeners.insert(bodyToRemove);
	}

	void PhysicsSystem::Reset()
	{
		mPendingRemoveListeners.clear();
		mPhysicsWorld = CreatePhysicsWorld(mContactListener);
	}

	PhysicsSystem::PhysicsSystem()
		: mPhysicsWorld{ CreatePhysicsWorld(mContactListener) }
	{
	}

	void PhysicsSystem::ProcessPendingRemoveListeners()
	{
		for (b2Body* listener : mPendingRemoveListeners)
		{
			mPhysicsWorld->DestroyBody(listener);
		}

		mPendingRemoveListeners.clear();
	}

	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		Actor* actorA = GetFixtureActor(contact->GetFixtureA());
		Actor* actorB = GetFixtureActor(contact->GetFixtureB());

		if (CanReceiveOverlap(actorA))
		{
			actorA->OnActorBeginOverlap(actorB);
		}

		if (CanReceiveOverlap(actorB))
		{
			actorB->OnActorBeginOverlap(actorA);
		}
	}

	void PhysicsContactListener::EndContact(b2Contact* contact)
	{
		Actor* actorA = GetFixtureActor(contact->GetFixtureA());
		Actor* actorB = GetFixtureActor(contact->GetFixtureB());

		if (CanReceiveOverlap(actorA))
		{
			actorA->OnActorEndOverlap(actorB);
		}

		if (CanReceiveOverlap(actorB))
		{
			actorB->OnActorEndOverlap(actorA);
		}
	}
}
