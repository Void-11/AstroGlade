#include "widgets/Button.h"
#include "framework/AssetManager.h"

namespace ly
{
    Button::Button(World* world, const std::string& labelText)
        : Actor{world, ""},
          mPosition{0.f, 0.f},
          mRect{},
          mFont{},
          mText{},
          mHovered{false}
    {
        mRect.setSize({140.f, 40.f});
        mRect.setFillColor(sf::Color(80, 80, 160, 200));
        mRect.setOutlineThickness(2);
        mRect.setOutlineColor(sf::Color::White);
        SetText(labelText);
    }

    void Button::BeginPlay()
    {
        Actor::BeginPlay();
        mFont = AssetManager::Get().LoadFont("Bonus/kenvector_future.ttf");
        if (mFont)
        {
            mText.setFont(*mFont);
            mText.setCharacterSize(20);
        }
    }

    void Button::RenderOverlay(sf::RenderWindow& window)
    {
        mRect.setPosition(mPosition);
        mRect.setFillColor(mHovered ? sf::Color(100, 100, 200, 220) : sf::Color(80, 80, 160, 200));
        window.draw(mRect);

        auto bounds = mText.getLocalBounds();
        mText.setPosition(mPosition.x + (mRect.getSize().x - bounds.width) / 2.f,
                          mPosition.y + (mRect.getSize().y - bounds.height) / 2.f - 6.f);
        window.draw(mText);
    }

    bool Button::HandleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2f mouse{(float)event.mouseMove.x, (float)event.mouseMove.y};
            mHovered = mRect.getGlobalBounds().contains(mouse);
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mouse{(float)event.mouseButton.x, (float)event.mouseButton.y};
            if (mRect.getGlobalBounds().contains(mouse))
            {
                onButtonClicked.Broadcast();
                return true;
            }
        }
        return false;
    }

    void Button::SetText(const std::string& text)
    {
        mText.setString(text);
    }
}