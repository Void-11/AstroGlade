#pragma once
#include "framework/Actor.h"
#include "framework/Delegate.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace ly
{
    class GameplayHUD : public Actor
    {
    public:
        GameplayHUD(World* owningWorld);
        virtual void BeginPlay() override;
        virtual void Tick(float deltaTime) override;
        virtual void RenderOverlay(sf::RenderWindow& window) override;

        void SetGameOver(bool won);
        void SetScore(int score);
        void SetLives(int lives);

        Delegate<> onRestartBtnClicked;
        Delegate<> onQuitBtnClicked;

    private:
        shared<sf::Font> mFont;
        std::string mFpsText;
        int mScore;
        int mLives;
        bool mGameOver;
        bool mWin;

        // Preloaded icons (optional, can be expanded)
        shared<sf::Texture> mLifeIconTex;
        sf::Sprite mLifeIcon;

        // Health bar rectangles
        sf::RectangleShape mHealthBarBack;
        sf::RectangleShape mHealthBarFront;

        // Buttons
        weak<class Button> mRestartBtn;
        weak<class Button> mQuitBtn;

        void DrawHealthBar(sf::RenderWindow& window);
        void RestartClicked();
        void QuitClicked();
    };
}
