#ifndef ASTROGLADE_ENGINE_FRAMEWORK_ACTOR_H
#define ASTROGLADE_ENGINE_FRAMEWORK_ACTOR_H

#include <string>

#include <SFML/Graphics.hpp>

#include "framework/Core.h"
#include "framework/Delegate.h"
#include "framework/Object.h"
class b2Body;

namespace ly
{
	class World;
	class Actor : public Object
	{
	public:
		explicit Actor(World* owningWorld, const std::string& texturePath = "");
		~Actor() override;
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		void SetTexture(const std::string& texturePath);
		virtual void Render(sf::RenderWindow& window);

		void SetActorLocation(const sf::Vector2f& newLoc);
		void SetActorRotation(float newRot);
		void AddActorLocationOffset(const sf::Vector2f& offsetAmt);
		void AddActorRotationOffset(float offsetAmt);

		[[nodiscard]] sf::Vector2f GetActorLocation() const;
		[[nodiscard]] float GetActorRotation() const;
		[[nodiscard]] sf::Vector2f GetActorForwardDirection() const;
		[[nodiscard]] sf::Vector2f GetActorRightDirection() const;
		[[nodiscard]] sf::FloatRect GetActorGlobalBounds() const;

		[[nodiscard]] sf::Vector2u GetWindowSize() const;

		const World* GetWorld() const { return mOwningWorld; }
		World* GetWorld() { return mOwningWorld; }

		[[nodiscard]] bool IsActorOutOfWindowBounds(float allowance = 10.f) const;

		void SetEnablePhysics(bool enable);
		virtual void OnActorBeginOverlap(Actor* other);
		virtual void OnActorEndOverlap(Actor* other);
		void Destroy() override;
		static constexpr uint8 GetNeutralTeamID() { return kNeutralTeamID; }

		void SetTeamID(uint8 teamID) { mTeamID = teamID; }

		[[nodiscard]] uint8 GetTeamID() const { return mTeamID; }
		[[nodiscard]] bool IsOtherHostile(Actor* other) const;

		virtual void ApplyDamage(float amt);

		sf::Sprite& GetSprite() { return mSprite; }
		const sf::Sprite& GetSprite() const { return mSprite; }
		Delegate<Actor*> onActorDestroyed;
		void SetTextureRepeated(bool repeated);
	private:
		void InitializePhysics();
		void UninitializePhysics();
		void UpdatePhysicsBodyTransform();
		void CenterPivot();

		static constexpr uint8 kNeutralTeamID = 255;
		
		World* mOwningWorld;
		bool mHasBeganPlay = false;

		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;
		
		b2Body* mPhysicBody = nullptr;
		bool mPhysicsEnabled = false;

		uint8 mTeamID = kNeutralTeamID;
	};
}

#endif // ASTROGLADE_ENGINE_FRAMEWORK_ACTOR_H
