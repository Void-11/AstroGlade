#pragma once
#include "framework/Object.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

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

    private:

        World* mOwningWorld;
        bool mHasBeginPlay;

        sf::Sprite mSprite;
        sf::Texture mTexture;
    };
}
