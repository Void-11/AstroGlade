#pragma once
#include "Core.h"
#include "box2d/b2_types.h"
#include "framework/Object.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class b2Body;

namespace ly
{
    class World;
    class Actor : public Object
    {
    public:

        Actor(World* owningWorld, const std::string& texturePath = "");
        
        virtual ~Actor();
        
        void BeginPlayIternal();
        void TickInternal(float deltaTime);
        virtual void BeginPlay();
        virtual void Tick(float deltaTime);
        void SetTexture(const std::string& texturePath);
        void Render(sf::RenderWindow& window);

        void SetActorLocation(const sf::Vector2f& newLocation);
        void SetActorRotation(float newRotation);
        void AddActorLocationOffset(const sf::Vector2f& offSetAmt);
        void AddActorRotationOffset(float offSetAmt);
        sf::Vector2f GetActorLocation() const;
        float GetActorRotation() const;
        sf::Vector2f GetActorForwardDirection() const;
        sf::Vector2f GetActorRightDirection() const;
        sf::FloatRect GetActorGlobalBounds() const;

        sf::Vector2u GetWindowSize() const;

        const World* GetWorld() const { return mOwningWorld; }
        World* GetWorld() { return mOwningWorld; }
        bool IsActorOutOfWindowBounds() const;

        void SetEnablePhysics(bool enable);
        virtual void OnActorBeginOverlap(Actor* other);
        virtual void OnActorEndOverlap(Actor* other);

        virtual void Destroy() override;
        
        static uint8 GetNeturalTeamID() { return neturalTeamID; }
        void SetTeamID(uint8 teamID) { mTeamID = teamID; }
        uint8 GetTeamID() const { return mTeamID; }
        bool IsOtherHostile(Actor* other) const;

        virtual void ApplyDamage(float amount);

        sf::Sprite& GetSprite() { return mSprite; }
        const sf::Sprite& GetSprite() const { return mSprite; }
        
    private:
        
        World* mOwningWorld;
        bool mHasBeginPlay;

        sf::Sprite mSprite;
        shared<sf::Texture> mTexture;
        b2Body* mPhysicsBody;
        bool mPhysicsEnable;

        uint8 mTeamID;
        const static uint8 neturalTeamID = 255;

        void CenterPivot();
        void InitializePhysics();
        void TerminatePhysics();
        void UpdatePhysicsBodyTransform();
    };
}
