#pragma once
#include "Core.h"
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

        World* GetWorld() const { return mOwningWorld; }
        bool IsActorOutOfWindowBounds() const;

        void SetEnablePhysics(bool enable);
        virtual void OnActorBeginOverlap(Actor* other);
        virtual void OnActorEndOverlap(Actor* other);
        
    private:
        
        World* mOwningWorld;
        bool mHasBeginPlay;

        sf::Sprite mSprite;
        shared<sf::Texture> mTexture;
        b2Body* mPhysicsBody;
        bool mPhysicsEnable;

        void CenterPivot();
        void InitializePhysics();
        void TerminatePhysics();
        void UpdatePhysicsBodyTransform();
    };
}
