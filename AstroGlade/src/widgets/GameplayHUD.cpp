#include <cmath>
#include <initializer_list>
#include <string>
#include <utility>

#include "framework/Actor.h"
#include "gameplay/GameAudio.h"
#include "player/Player.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "widgets/GameplayHUD.h"
#include "widgets/MenuStyle.h"

namespace ly
{
	namespace
	{
		// Moves widget by offset, landing on whole pixels so that text glyphs stay crisp.
		void MoveWidgetBy(Widget& widget, const sf::Vector2f& offset)
		{
			const sf::Vector2f location = widget.GetWidgetLocation() + offset;
			widget.SetWidgetLocation({ std::round(location.x), std::round(location.y) });
		}
	}

	GameplayHUD::GameplayHUD()
		: mFramerateText{ "Frame Rate:" },
		mPlayerLifeIcon{ "SpaceShooterRedux/PNG/playerShip_hud.png" },
		mPlayerLifeText{ "" },
		mPlayerScoreIcon{ "SpaceShooterRedux/PNG/Power-ups/star_gold.png" },
		mPlayerScoreText{ "" },
		mWinLoseText{ "", MenuStyle::kTitleFontPath },
		mFinalScoreText{ "" },
		mPauseText{ "PAUSED", MenuStyle::kTitleFontPath },
		mResumeButton{ ">> RESUME" },
		mRestartButton{ ">> RESTART" },
		mControlsButton{ ">> CONTROLS" },
		mQuitButton{ ">> QUIT" }
	{
		mFramerateText.SetTextSize(30);
		mPlayerLifeText.SetTextSize(20);
		mPlayerScoreText.SetTextSize(20);
		mPlayerHealthBar.SetForegroundColor(mHealthyHealthBarColor);
		mPlayerHealthBar.SetBackgroundColor({ 4, 10, 24, 220 });
		mPlayerHealthBar.SetTextColor(MenuStyle::kAstroWhite);
		mPlayerHealthBar.SetTextOutline({ 4, 10, 24, 255 }, 2.f);

		mScreenDim.setFillColor(MenuStyle::kScreenDim);
		mWinLoseText.SetTextColor(MenuStyle::kMenuGreen);
		mWinLoseText.SetVisibility(false);
		mFinalScoreText.SetTextColor(MenuStyle::kAstroWhite);
		mFinalScoreText.SetVisibility(false);
		mPauseText.SetTextColor(MenuStyle::kMenuGreen);
		mPauseText.SetVisibility(false);

		for (Button* button : { &mResumeButton, &mRestartButton, &mControlsButton, &mQuitButton })
		{
			MenuStyle::ApplyMenuButtonStyle(*button, 22);
			button->SetVisibility(false);
		}
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		if (mIsPaused || mIsGameFinished)
		{
			windowRef.draw(mScreenDim);
		}

		UpdateFrameRate();
		mFramerateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
		mPlayerLifeIcon.NativeDraw(windowRef);
		mPlayerLifeText.NativeDraw(windowRef);
		mPlayerScoreIcon.NativeDraw(windowRef);
		mPlayerScoreText.NativeDraw(windowRef);

		mWinLoseText.NativeDraw(windowRef);
		mFinalScoreText.NativeDraw(windowRef);
		mPauseText.NativeDraw(windowRef);
		mControlsPanel.Draw(windowRef);
		mResumeButton.NativeDraw(windowRef);
		mRestartButton.NativeDraw(windowRef);
		mControlsButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);
	}

	bool GameplayHUD::HandleEvent(const sf::Event& event)
	{
		if (mControlsPanel.IsVisible())
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				ReturnButtonClicked();
				return true;
			}

			return mControlsPanel.HandleEvent(event) || HUD::HandleEvent(event);
		}

		if (mIsPaused)
		{
			if (mResumeButton.HandleEvent(event)) return true;
			if (mControlsButton.HandleEvent(event)) return true;
		}

		if (mRestartButton.HandleEvent(event)) return true;
		if (mQuitButton.HandleEvent(event)) return true;

		return HUD::HandleEvent(event);
	}

	void GameplayHUD::Init(const sf::RenderWindow& windowRef)
	{
		const sf::Vector2u windowSize = windowRef.getSize();
		mWindowSize = windowSize;

		// The frame rate sits in the top left corner and the status row in the bottom left one, both mScreenMargin from the edges.
		const sf::FloatRect framerateBounds = mFramerateText.GetBounds();
		MoveWidgetBy(mFramerateText, { mScreenMargin - framerateBounds.left, mScreenMargin - framerateBounds.top });
		mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{
			mScreenMargin,
			static_cast<float>(windowSize.y) - mScreenMargin - mPlayerHealthBar.GetBounds().height
		});
		RefreshHealthBar();
		ConnectPlayerStatus();

		// The status row: health bar, life icon and count, then score icon and score, all centered on the middle of the bar.
		const sf::FloatRect healthBarBounds = mPlayerHealthBar.GetBounds();
		const float rowCenterY = healthBarBounds.top + healthBarBounds.height / 2.f;
		float nextLeft = healthBarBounds.left + healthBarBounds.width + mWidgetSpacing;

		const std::initializer_list<std::pair<Widget*, float>> statusRow{
			{ &mPlayerLifeIcon, mWidgetSpacing },
			{ &mPlayerLifeText, mWidgetSpacing * 4.f },
			{ &mPlayerScoreIcon, mWidgetSpacing },
			{ &mPlayerScoreText, 0.f }
		};

		for (const auto& [widget, spacingAfter] : statusRow)
		{
			const sf::FloatRect bounds = widget->GetBounds();
			MoveWidgetBy(*widget, { nextLeft - bounds.left, rowCenterY - (bounds.top + bounds.height / 2.f) });
			nextLeft += bounds.width + spacingAfter;
		}

		mScreenDim.setSize(sf::Vector2f{ windowSize });

		// The game over banner takes the place of the pause title, with the final score below it.
		mWinLoseText.SetTextSize(46);
		mFinalScoreText.SetTextSize(30);
		CenterGameOverTexts();

		mPauseText.SetTextSize(46);
		MenuStyle::CenterHorizontally(mPauseText, windowSize, 80.f);

		const sf::Vector2f buttonStep{ 0.f, mMenuButtonSpacing };
		MenuStyle::CenterHorizontally(mResumeButton, windowSize, static_cast<float>(windowSize.y) / 2.f - 30.f);
		mRestartButton.SetWidgetLocation(mResumeButton.GetWidgetLocation() + buttonStep);
		mControlsButton.SetWidgetLocation(mRestartButton.GetWidgetLocation() + buttonStep);
		mQuitButton.SetWidgetLocation(mControlsButton.GetWidgetLocation() + buttonStep);

		mControlsPanel.Layout(windowSize);

		mResumeButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::ResumeButtonClicked);
		mRestartButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::RestartButtonClicked);
		mControlsButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::ControlsButtonClicked);
		mQuitButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::QuitButtonClicked);
		mControlsPanel.GetReturnButton().onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::ReturnButtonClicked);
	}

	void GameplayHUD::PlayerHealthUpdated([[maybe_unused]] float amt, float currentHealth, float maxHealth)
	{
		mPlayerHealthBar.UpdateValue(currentHealth, maxHealth);
		const bool isCritical = currentHealth / maxHealth < mCriticalThreshold;
		mPlayerHealthBar.SetForegroundColor(isCritical ? mCriticalHealthBarColor : mHealthyHealthBarColor);
	}

	void GameplayHUD::PlayerLifeCountUpdated(int lifeCount)
	{
		mPlayerLifeText.SetString(std::to_string(lifeCount));
	}

	void GameplayHUD::PlayerScoreUpdated(int newScore)
	{
		std::string scoreText = std::to_string(newScore);
		if (const Player* const player = PlayerManager::Get().GetPlayer(); player && player->GetScoreMultiplier() > 1)
		{
			scoreText += " x" + std::to_string(player->GetScoreMultiplier());
		}

		mPlayerScoreText.SetString(scoreText);
	}

	void GameplayHUD::RefreshHealthBar()
	{
		const Player* const player = PlayerManager::Get().GetPlayer();
		if (!player)
		{
			return;
		}

		if (const shared<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship().lock())
		{
			playerSpaceship->onActorDestroyed.BindAction(GetWeakRef(), &GameplayHUD::PlayerSpaceshipDestroyed);
			HealthComponent& healthComp = playerSpaceship->GetHealthComp();
			healthComp.onHealthChanged.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);
			PlayerHealthUpdated(0.f, healthComp.GetHealth(), healthComp.GetMaxHealth());
		}
	}

	void GameplayHUD::ConnectPlayerStatus()
	{
		if (Player* const player = PlayerManager::Get().GetPlayer())
		{
			PlayerLifeCountUpdated(player->GetLifeCount());
			player->onLifeChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerLifeCountUpdated);

			PlayerScoreUpdated(player->GetScore());
			player->onScoreChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerScoreUpdated);
		}
	}

	void GameplayHUD::PlayerSpaceshipDestroyed([[maybe_unused]] Actor* actor)
	{
		RefreshHealthBar();
	}

	void GameplayHUD::UpdateFrameRate()
	{
		++mFramesSinceRateUpdate;
		const float elapsedTime = mFrameRateClock.getElapsedTime().asSeconds();
		if (elapsedTime >= mFrameRateUpdateInterval)
		{
			const int frameRate = static_cast<int>(static_cast<float>(mFramesSinceRateUpdate) / elapsedTime + 0.5f);
			mFramerateText.SetString("Frame Rate: " + std::to_string(frameRate));
			mFramesSinceRateUpdate = 0;
			mFrameRateClock.restart();
		}
	}

	void GameplayHUD::ResumeButtonClicked()
	{
		GameAudio::PlayUIButton();
		onResumeBtnClicked.Broadcast();
	}

	void GameplayHUD::RestartButtonClicked()
	{
		GameAudio::PlayUIButton();
		onRestartBtnClicked.Broadcast();
	}

	void GameplayHUD::ControlsButtonClicked()
	{
		GameAudio::PlayUIButton();
		SetControlsVisible(true);
	}

	void GameplayHUD::ReturnButtonClicked()
	{
		GameAudio::PlayUIButton();
		SetControlsVisible(false);
	}

	void GameplayHUD::QuitButtonClicked()
	{
		GameAudio::PlayUIButton();
		onQuitBtnClicked.Broadcast();
	}

	void GameplayHUD::SetPause(bool paused)
	{
		mIsPaused = paused;
		SetControlsVisible(false);
	}

	void GameplayHUD::SetControlsVisible(bool visible)
	{
		mControlsPanel.SetVisible(visible);

		const bool showPauseMenu = mIsPaused && !visible;
		mPauseText.SetVisibility(showPauseMenu);
		for (Button* button : { &mResumeButton, &mRestartButton, &mControlsButton, &mQuitButton })
		{
			button->SetVisibility(showPauseMenu);
		}
	}

	void GameplayHUD::GameFinished(bool playerWon)
	{
		mIsPaused = false;
		mIsGameFinished = true;
		SetControlsVisible(false);
		mWinLoseText.SetVisibility(true);
		mFinalScoreText.SetVisibility(true);

		// Only restart and quit remain, so they move up into the first two menu slots instead of leaving a gap.
		mRestartButton.SetWidgetLocation(mResumeButton.GetWidgetLocation());
		mQuitButton.SetWidgetLocation(mResumeButton.GetWidgetLocation() + sf::Vector2f{ 0.f, mMenuButtonSpacing });
		mRestartButton.SetVisibility(true);
		mQuitButton.SetVisibility(true);

		const Player* const player = PlayerManager::Get().GetPlayer();
		const int score = player ? player->GetScore() : 0;
		mFinalScoreText.SetString("SCORE: " + std::to_string(score));
		mWinLoseText.SetString(playerWon ? "YOU WIN!" : "YOU LOSE!");
		CenterGameOverTexts();
	}

	void GameplayHUD::CenterGameOverTexts()
	{
		MenuStyle::CenterHorizontally(mWinLoseText, mWindowSize, 80.f);
		MenuStyle::CenterHorizontally(mFinalScoreText, mWindowSize, 160.f);
	}
}
