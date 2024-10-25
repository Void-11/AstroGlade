#include "framework/Actor.h"
#include "framework/Core.h"

namespace ly
{
    Actor::Actor(World* owningWorld, const std::string& texturePath)
        :mOwningWorld(owningWorld),
        mHasBeginPlay{false},
        mSprite{},
        mTexture{}
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
        LOG("Actor Begin Play")
    }

    void Actor::Tick(float deltaTime)
    {
        LOG("Actor Ticking")
    }

    void Actor::SetTexture(const std::string& texturePath)
    {
        mTexture.loadFromFile(texturePath);
        mSprite.setTexture(mTexture);

        int textureWidth = mTexture.getSize().x;
        int textureHeight = mTexture.getSize().y;
        mSprite.setTextureRect(sf::IntRect{sf::Vector2i{},sf::Vector2i{textureWidth,textureHeight}});
    }

    void Actor::Render(sf::RenderWindow& window)
    {
        if(IsPendingDestroy())
            return;
        
        window.draw(mSprite);
    }
}
