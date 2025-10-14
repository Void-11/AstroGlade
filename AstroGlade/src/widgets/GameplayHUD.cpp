#include "widgets/GameplayHUD.h"
#include "framework/AssetManager.h"
#include "framework/World.h"
#include "player/PlayerManager.h"
#include <SFML/Graphics/Text.hpp>
#include "widgets/Button.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    GameplayHUD::GameplayHUD(World* owningWorld)
        : Actor{owningWorld, ""},
          mFont{},
          mFpsText{},
          mScore{0},
          mLives{3},
          mGameOver{false},
          mWin{false},
          mLifeIconTex{},
          mLifeIcon{},
          mHealthBarBack{},
          mHealthBarFront{},
          mRestartBtn{},
          mQuitBtn{}
    {
    }

    void GameplayHUD::BeginPlay()
    {
        Actor::BeginPlay();
        mFont = AssetManager::Get().LoadFont("Bonus/kenvector_future.ttf");
        mLifeIconTex = AssetManager::Get().LoadTexture("PNG/pickups/playerLife1_blue.png");
        if (mLifeIconTex)
        {
            mLifeIcon.setTexture(*mLifeIconTex);
            mLifeIcon.setScale(0.75f, 0.75f);
            mLifeIcon.setPosition(10.f, 10.f);
        }

        // Subscribe to player events
        // Buttons
        mRestartBtn = GetWorld()->SpawnActor<Button>("Restart");
        if (!mRestartBtn.expired())
        {
            mRestartBtn.lock()->SetWidgetLocation({ 400.f, 300.f });
            mRestartBtn.lock()->onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::RestartClicked);
        }
        mQuitBtn = GetWorld()->SpawnActor<Button>("Quit");
        if (!mQuitBtn.expired())
        {
            mQuitBtn.lock()->SetWidgetLocation({ 400.f, 350.f });
            mQuitBtn.lock()->onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::QuitClicked);
        }
        if (PlayerManager::Get().GetPlayer())
        {
            PlayerManager::Get().GetPlayer()->onLifeChange.BindAction(GetWeakRef(), &GameplayHUD::SetLives);
            PlayerManager::Get().GetPlayer()->onScoreChange.BindAction(GetWeakRef(), &GameplayHUD::SetScore);
        }
    }

    void GameplayHUD::Tick(float deltaTime)
    {
        Actor::Tick(deltaTime);
        int fps = int(1.f / (deltaTime > 0.f ? deltaTime : 0.0001f));
        mFpsText = "FPS: " + std::to_string(fps);
    }

    void GameplayHUD::RenderOverlay(sf::RenderWindow& window)
    {
        DrawHealthBar(window);
        // Draw life icon
        if (mLifeIconTex)
        {
            window.draw(mLifeIcon);
        }

        if (mFont)
        {
            sf::Text text;
            text.setFont(*mFont);
            text.setCharacterSize(20);

            // FPS
            text.setString(mFpsText);
            text.setPosition(60.f, 8.f);
            window.draw(text);

            // Lives
            text.setString("Lives: " + std::to_string(mLives));
            text.setPosition(10.f, 40.f);
            window.draw(text);

            // Score
            text.setString("Score: " + std::to_string(mScore));
            text.setPosition(10.f, 64.f);
            window.draw(text);

            if (mGameOver)
            {
                std::string result = mWin ? "You Win!" : "You Lose!";
                sf::Text big;
                big.setFont(*mFont);
                big.setCharacterSize(40);
                big.setString(result);
                auto winSize = window.getSize();
                big.setPosition(winSize.x / 2.f - big.getLocalBounds().width / 2.f, 100.f);
                window.draw(big);

                sf::Text finalScore;
                finalScore.setFont(*mFont);
                finalScore.setCharacterSize(30);
                finalScore.setString("Score: " + std::to_string(mScore));
                finalScore.setPosition(winSize.x / 2.f - finalScore.getLocalBounds().width / 2.f, 150.f);
                window.draw(finalScore);
            }
        }
    }

    void GameplayHUD::DrawHealthBar(sf::RenderWindow& window)
    {
        // Very simple health bar (requires a current spaceship)
        auto player = PlayerManager::Get().GetPlayer();
        if (!player || player->GetCurrentSpaceship().expired()) return;
        auto sp = player->GetCurrentSpaceship();
        float health = sp.lock()->GetHealthComp().GetHealth();
        float maxH = sp.lock()->GetHealthComp().GetMaxHealth();
        float pct = (maxH > 0) ? (health / maxH) : 0.f;

        mHealthBarBack.setSize({ 200.f, 16.f });
        mHealthBarBack.setFillColor(sf::Color(80, 80, 80, 200));
        mHealthBarBack.setPosition(10.f, window.getSize().y - 30.f);

        mHealthBarFront.setSize({ 200.f * pct, 16.f });
        mHealthBarFront.setFillColor(pct < 0.3f ? sf::Color(220, 50, 50, 220) : sf::Color(60, 200, 60, 220));
        mHealthBarFront.setPosition(10.f, window.getSize().y - 30.f);

        window.draw(mHealthBarBack);
        window.draw(mHealthBarFront);
    }

    void GameplayHUD::SetGameOver(bool won)
    {
        mGameOver = true;
        mWin = won;
    }

    void GameplayHUD::SetScore(int score)
    {
        mScore = score;
    }

    void GameplayHUD::RestartClicked()
    {
        onRestartBtnClicked.Broadcast();
    }

    void GameplayHUD::QuitClicked()
    {
        onQuitBtnClicked.Broadcast();
    }

    void GameplayHUD::SetLives(int lives)
    {
        mLives = lives;
    }
}
