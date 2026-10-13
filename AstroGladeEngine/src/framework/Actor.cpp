#include <box2d/b2_body.h>

#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: mOwningWorld{owningWorld}
	{
		SetTexture(texturePath);
	}

	Actor::~Actor()
	{
		// RAII: an actor never leaves a physics body behind, even if it was not destroyed explicitly.
		UninitializePhysics();
	}

	void Actor::BeginPlayInternal()
	{
		if (!mHasBeganPlay)
		{
			mHasBeganPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy())
		{
			Tick(deltaTime);
		}
	}

	void Actor::BeginPlay()
	{
	}

	void Actor::Tick([[maybe_unused]] float deltaTime)
	{
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		mTexture = AssetManager::Get().LoadTexture(texturePath);
		if (!mTexture) return;

		mSprite.setTexture(*mTexture);

		const sf::Vector2u textureSize = mTexture->getSize();
		mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{ static_cast<int>(textureSize.x), static_cast<int>(textureSize.y) } });
		CenterPivot(); 
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy())
			return;

		window.draw(mSprite);
	}

	void Actor::SetActorLocation(const sf::Vector2f& newLoc)
	{
		mSprite.setPosition(newLoc);
		UpdatePhysicsBodyTransform();
	}

	void Actor::SetActorRotation(float newRot)
	{
		mSprite.setRotation(newRot);
		UpdatePhysicsBodyTransform();
	}
	
	void Actor::AddActorLocationOffset(const sf::Vector2f& offsetAmt)
	{
		SetActorLocation(GetActorLocation() + offsetAmt);
	}
	
	void Actor::AddActorRotationOffset(float offsetAmt)
	{
		SetActorRotation(GetActorRotation() + offsetAmt);
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return mSprite.getPosition();
	}
	
	float Actor::GetActorRotation() const
	{
		return mSprite.getRotation();
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation() + 90.f);
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return mOwningWorld->GetWindowSize();
	}

	void Actor::SetTextureRepeated(bool repeated)
	{
		if (mTexture) { mTexture->setRepeated(repeated); }
	}

	void Actor::InitializePhysics()
	{
		if (!mPhysicBody)
		{
			mPhysicBody = PhysicsSystem::Get().AddListener(this);
		}
	}

	void Actor::UninitializePhysics()
	{
		if (mPhysicBody)
		{
			PhysicsSystem::Get().RemoveListener(mPhysicBody);
			mPhysicBody = nullptr;
		}
	}

	void Actor::UpdatePhysicsBodyTransform()
	{
		if (mPhysicBody)
		{
			const float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			const sf::Vector2f location = GetActorLocation();
			const b2Vec2 pos{ location.x * physicsScale, location.y * physicsScale };
			const float rotation = DegreesToRadians(GetActorRotation());

			mPhysicBody->SetTransform(pos, rotation);
		}
	}

	void Actor::CenterPivot()
	{
		// Local bounds ignore the current scale and rotation, so the pivot stays right whenever this runs.
		const sf::FloatRect localBounds = mSprite.getLocalBounds();
		mSprite.setOrigin(localBounds.width / 2.f, localBounds.height / 2.f);
	}

	bool Actor::IsActorOutOfWindowBounds(float allowance) const
	{
		const sf::Vector2u windowSize = GetWindowSize();
		const float windowWidth = static_cast<float>(windowSize.x);
		const float windowHeight = static_cast<float>(windowSize.y);

		const sf::FloatRect bounds = GetActorGlobalBounds();
		const sf::Vector2f actorPos = GetActorLocation();

		return actorPos.x < -bounds.width - allowance
			|| actorPos.x > windowWidth + bounds.width + allowance
			|| actorPos.y < -bounds.height - allowance
			|| actorPos.y > windowHeight + bounds.height + allowance;
	}

	void Actor::SetEnablePhysics(bool enable)
	{
		mPhysicsEnabled = enable;
		if (mPhysicsEnabled)
		{
			InitializePhysics();
		}
		else
		{
			UninitializePhysics();
		}
	}

	void Actor::OnActorBeginOverlap([[maybe_unused]] Actor* other)
	{
		
	}

	void Actor::OnActorEndOverlap([[maybe_unused]] Actor* other)
	{

	}

	void Actor::Destroy()
	{
		UninitializePhysics();
		onActorDestroyed.Broadcast(this);
		Object::Destroy();
	}

	bool Actor::IsOtherHostile(Actor* other) const
	{
		if (other == nullptr) return false;

		if (GetTeamID() == GetNeutralTeamID() || other->GetTeamID() == GetNeutralTeamID())
		{
			return false;
		}

		return GetTeamID() != other->GetTeamID();
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return mSprite.getGlobalBounds();
	}

	void Actor::ApplyDamage([[maybe_unused]] float amt)
	{

	}
}
