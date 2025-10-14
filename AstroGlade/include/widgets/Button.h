#pragma once
#include "framework/Actor.h"
#include "framework/Delegate.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace ly
{
    class Button : public Actor
    {
    public:
        Button(World* world, const std::string& labelText = "Button");
        virtual void BeginPlay() override;
        virtual void RenderOverlay(sf::RenderWindow& window) override;
        virtual bool HandleEvent(const sf::Event& event) override;

        void SetWidgetLocation(const sf::Vector2f& pos) { mPosition = pos; }
        sf::Vector2f GetWidgetLocation() const { return mPosition; }
        void SetText(const std::string& text);

        Delegate<> onButtonClicked;

    private:
        sf::Vector2f mPosition;
        sf::RectangleShape mRect;
        shared<sf::Font> mFont;
        sf::Text mText;
        bool mHovered;
    };
}