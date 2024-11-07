#include "framework/Actor.h"
#include "box2d/b2_body.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath)
        :mOwningWorld(owningWorld),
        mHasBeginPlay{false},
        mSprite{},
        mTexture{},
        mPhysicsBody{nullptr},
        mPhysicsEnable{false}
    {
        SetTexture(texturePath);
    }
    

    Actor::~Actor()
    {
        LOG("Actor Destroyed")
    }

    void Actor::BeginPlayIternal()
    {
        if(!mHasBeginPlay)
        {
            mHasBeginPlay = true;
            BeginPlay();
        }
    }

    void Actor::TickInternal(float deltaTime)
    {
        if(!IsPendingDestroy())
        {
            Tick(deltaTime);
        }
    }

    void Actor::BeginPlay()
    {
       
    }

    void Actor::Tick(float deltaTime)
    {
      
    }

    void Actor::SetTexture(const std::string& texturePath)
    {
        mTexture = AssetManager::Get().LoadTexture(texturePath);
        if(!mTexture) return;
        
        mSprite.setTexture(*mTexture);

        int textureWidth = mTexture->getSize().x;
        int textureHeight = mTexture->getSize().y;
        mSprite.setTextureRect(sf::IntRect{sf::Vector2i{},sf::Vector2i{textureWidth,textureHeight}});
        CenterPivot();
    }

    void Actor::Render(sf::RenderWindow& window)
    {
        if(IsPendingDestroy())
            return;
        
        window.draw(mSprite);
    }

    void Actor::SetActorLocation(const sf::Vector2f& newLocation)
    {
        mSprite.setPosition(newLocation);
        UpdatePhysicsBodyTransform();
    }

    void Actor::SetActorRotation(float newRotation)
    {
        mSprite.setRotation(newRotation);
        UpdatePhysicsBodyTransform();
    }

    void Actor::AddActorLocationOffset(const sf::Vector2f& offSetAmt)
    {
        SetActorLocation(GetActorLocation() + offSetAmt);
    }

    void Actor::AddActorRotationOffset(float offSetAmt)
    {
        SetActorRotation(GetActorRotation() + offSetAmt);
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

    sf::FloatRect Actor::GetActorGlobalBounds() const
    {
        return mSprite.getGlobalBounds();
    }

    sf::Vector2u Actor::GetWindowSize() const
    {
        return mOwningWorld->GetWindowSize();
    }

    bool Actor::IsActorOutOfWindowBounds() const
    {
        float windowWidth = GetWorld()->GetWindowSize().x;
        float windowHeight = GetWorld()->GetWindowSize().y;

        float width = GetActorGlobalBounds().width;
        float height = GetActorGlobalBounds().height;

        sf::Vector2f actorPosition = GetActorLocation();

        if(actorPosition.x < -width)
        {
            return true;
        }
        if(actorPosition.x > windowWidth + width)
        {
            return true;
        }
        if(actorPosition.y < -height)
        {
            return true;
        }
        if(actorPosition.y > windowHeight + height)
        {
            return true;
        }
        return false;
    }

    void Actor::SetEnablePhysics(bool enable)
    {
        mPhysicsEnable = enable;
        if (mPhysicsEnable)
        {
            InitializePhysics();
        }
        else
        {
            TerminatePhysics();
        }
    }

    void Actor::OnActorBeginOverlap(Actor* other)
    {
       LOG("Overlapped")
    }

    void Actor::OnActorEndOverlap(Actor* other)
    {
        LOG("Overlapped Finished")
    }

    void Actor::CenterPivot()
    {
        sf::FloatRect bound = mSprite.getGlobalBounds();
        mSprite.setOrigin(bound.width/2.f, bound.height/2.f);
    }

    void Actor::InitializePhysics()
    {
        if(!mPhysicsBody)
        {
            mPhysicsBody = PhysicsSystem::Get().AddListener(this);
        }
    }

    void Actor::TerminatePhysics()
    {
        if(mPhysicsBody)
        {
            PhysicsSystem::Get().RemoveListener(mPhysicsBody);
        }
    }

    void Actor::UpdatePhysicsBodyTransform()
    {
        if(mPhysicsBody)
        {
            float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
            b2Vec2 pos{GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale};
            float rotation = DegreeToRadians(GetActorRotation());

            mPhysicsBody->SetTransform(pos, rotation);
        }
    }
}
