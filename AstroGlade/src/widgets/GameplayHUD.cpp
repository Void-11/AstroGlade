#include "framework/Actor.h"
#include "widgets/GameplayHUD.h"
#include "player/Player.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
namespace ly
{
	GameplayHUD::GameplayHUD()
		:mFramerateText{"Frame Rate:"},
		mPlayerHealthBar{},
		mPlayerLifeIcon{ "SpaceShooterRedux/PNG/playerShip_hud.png" },
		mPlayerLifeText{ "" },
		mPlayerScoreIcon{ "SpaceShooterRedux/PNG/Power-ups/star_gold.png" },
		mPlayerScoreText{ "" },
		mHealthyHealthBarColor{40,255,95,255},
		mCriticalHealthBarColor{255,0,0,255},
		mCriticalThreshold{0.3},
		mWidgetSpaceing{10.f},
		mWinLoseText{""},
		mFinalScoreText{""},
		mPauseText{"PAUSED", "SpaceShooterRedux/Bonus/Oxanium-ExtraBold.ttf"},
		mControlsTitleText{"CONTROLS", "SpaceShooterRedux/Bonus/Oxanium-ExtraBold.ttf"},
		mControlsKeysText{"W\nA\nS\nD\nSPACE\nESC"},
		mControlsActionsText{"MOVE UP\nMOVE LEFT\nMOVE DOWN\nMOVE RIGHT\nSHOOT\nPAUSE/MENU"},
		mResumeButton{">> RESUME"},
		mRestartButton{">> RESTART"},
		mControlsButton{">> CONTROLS"},
		mQuitButton{">> QUIT"},
		mReturnButton{">> RETURN"},
		mShowingControls{false},
		mIsPaused{false},
		mWindowSize{}
	{
		const sf::Color astroWhite{245, 248, 255, 255};
		const sf::Color menuGreen{40, 255, 95, 255};
		const sf::Color transparent{255, 255, 255, 0};
		const sf::Color hoverGlow{0, 255, 90, 55};
		const sf::Color downGlow{0, 180, 65, 90};

		mFramerateText.SetTextSize(30);
		mPlayerLifeText.SetTextSize(20);
		mPlayerScoreText.SetTextSize(20);
		mPlayerHealthBar.SetForegroundColor(mHealthyHealthBarColor);
		mPlayerHealthBar.SetBackgroundColor({4, 10, 24, 220});
		mPlayerHealthBar.SetTextColor({4, 10, 24, 255});

		mWinLoseText.SetVisibility(false);
		mFinalScoreText.SetVisibility(false);
		mPauseText.SetTextColor(menuGreen);
		mPauseText.SetVisibility(false);
		mControlsTitleText.SetTextSize(36);
		mControlsTitleText.SetTextColor(menuGreen);
		mControlsTitleText.SetVisibility(false);
		mControlsKeysText.SetTextSize(22);
		mControlsKeysText.SetTextColor(menuGreen);
		mControlsKeysText.SetVisibility(false);
		mControlsActionsText.SetTextSize(22);
		mControlsActionsText.SetTextColor(astroWhite);
		mControlsActionsText.SetVisibility(false);
		mResumeButton.SetTextSize(22);
		mResumeButton.SetVisibility(false);
		mRestartButton.SetTextSize(22);
		mRestartButton.SetVisibility(false);
		mControlsButton.SetTextSize(22);
		mControlsButton.SetVisibility(false);
		mQuitButton.SetTextSize(22);
		mQuitButton.SetVisibility(false);
		mReturnButton.SetTextSize(18);
		mReturnButton.SetVisibility(false);

		mResumeButton.SetButtonColors(transparent, hoverGlow, downGlow);
		mRestartButton.SetButtonColors(transparent, hoverGlow, downGlow);
		mControlsButton.SetButtonColors(transparent, hoverGlow, downGlow);
		mQuitButton.SetButtonColors(transparent, hoverGlow, downGlow);
		mReturnButton.SetButtonColors(transparent, hoverGlow, downGlow);

		mResumeButton.SetTextColors(astroWhite, menuGreen, menuGreen);
		mRestartButton.SetTextColors(astroWhite, menuGreen, menuGreen);
		mControlsButton.SetTextColors(astroWhite, menuGreen, menuGreen);
		mQuitButton.SetTextColors(astroWhite, menuGreen, menuGreen);
		mReturnButton.SetTextColors(astroWhite, menuGreen, menuGreen);

		mControlsPanel.setFillColor(sf::Color{0, 0, 0, 165});
		mControlsPanel.setOutlineColor(sf::Color{0, 255, 90, 220});
		mControlsPanel.setOutlineThickness(2.f);
	}
	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mWindowSize = windowRef.getSize();
		mFramerateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
		mPlayerLifeIcon.NativeDraw(windowRef);
		mPlayerLifeText.NativeDraw(windowRef);
		mPlayerScoreIcon.NativeDraw(windowRef);
		mPlayerScoreText.NativeDraw(windowRef);

		mWinLoseText.NativeDraw(windowRef);
		mFinalScoreText.NativeDraw(windowRef);
		mPauseText.NativeDraw(windowRef);
		if (mShowingControls)
		{
			windowRef.draw(mControlsPanel);
		}
		mControlsTitleText.NativeDraw(windowRef);
		mControlsKeysText.NativeDraw(windowRef);
		mControlsActionsText.NativeDraw(windowRef);
		mResumeButton.NativeDraw(windowRef);
		mRestartButton.NativeDraw(windowRef);
		mControlsButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);
		mReturnButton.NativeDraw(windowRef);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		int frameRate = int(1 / deltaTime);
		std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
		mFramerateText.SetString(frameRateStr);
	}

	bool GameplayHUD::HandleEvent(const sf::Event& event)
	{
		if (mShowingControls)
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				ReturnButtonClicked();
				return true;
			}

			if (mReturnButton.HandleEvent(event)) return true;
			return HUD::HandleEvent(event);
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
		auto windowSize = windowRef.getSize();
		mWindowSize = windowSize;
		mPlayerHealthBar.SetWidgetLocation(sf::Vector2f{ 20.f, windowSize.y - 50.f });
		RefreshHealthBar();
		ConnectPlayerStatus();

		sf::Vector2f nextWidgetPos = mPlayerHealthBar.GetWidgetLocation();
		const float rowCenterY = nextWidgetPos.y + mPlayerHealthBar.GetBounds().height / 2.f;

	nextWidgetPos += sf::Vector2f{ mPlayerHealthBar.GetBounds().width + mWidgetSpaceing, 0.f };
		mPlayerLifeIcon.SetWidgetLocation({nextWidgetPos.x, rowCenterY - mPlayerLifeIcon.GetBounds().height / 2.f});

	nextWidgetPos += sf::Vector2f{ mPlayerLifeIcon.GetBounds().width + mWidgetSpaceing, 0.f };
		mPlayerLifeText.SetWidgetLocation(nextWidgetPos);

	nextWidgetPos += sf::Vector2f{ mPlayerLifeText.GetBounds().width + mWidgetSpaceing * 4, -2.f };
		mPlayerScoreIcon.SetWidgetLocation({nextWidgetPos.x, rowCenterY - mPlayerScoreIcon.GetBounds().height / 2.f});

	nextWidgetPos += sf::Vector2f{ mPlayerScoreIcon.GetBounds().width + mWidgetSpaceing, 0.f };
		mPlayerScoreText.SetWidgetLocation(nextWidgetPos);

		mWinLoseText.SetTextSize(40);
		//mWinLoseText.SetString("You Win!");
	mWinLoseText.SetWidgetLocation({ windowSize.x / 2.f - mWinLoseText.GetBounds().width / 2.f, 100.f });
		
		//mFinalScoreText.SetString("score: " + std::to_string(100));
		mFinalScoreText.SetTextSize(40);
	mFinalScoreText.SetWidgetLocation({ windowSize.x / 2.f - mFinalScoreText.GetBounds().width / 2.f, 200.f });

	mPauseText.SetTextSize(46);
	mPauseText.SetWidgetLocation({ windowSize.x / 2.f - mPauseText.GetBounds().width / 2.f, 80.f });

	mResumeButton.SetWidgetLocation({ windowSize.x / 2.f - mResumeButton.GetBounds().width / 2.f, windowSize.y / 2.f - 30.f });
	mRestartButton.SetWidgetLocation(mResumeButton.GetWidgetLocation() + sf::Vector2f{ 0.f, 58.f });
		mControlsButton.SetWidgetLocation(mRestartButton.GetWidgetLocation() + sf::Vector2f{ 0.f, 58.f });
		mQuitButton.SetWidgetLocation(mControlsButton.GetWidgetLocation() + sf::Vector2f{ 0.f, 58.f });
		const sf::Vector2f panelSize{ 640.f, 420.f };
		const sf::Vector2f panelLocation{
			windowSize.x / 2.f - panelSize.x / 2.f,
			windowSize.y / 2.f - panelSize.y / 2.f
		};
		mControlsPanel.setSize(panelSize);
		mControlsPanel.setPosition(panelLocation);
		mControlsTitleText.SetWidgetLocation({ windowSize.x / 2.f - mControlsTitleText.GetBounds().width / 2.f, panelLocation.y + 45.f });
		mControlsKeysText.SetWidgetLocation({ panelLocation.x + 150.f, panelLocation.y + 125.f });
		mControlsActionsText.SetWidgetLocation({ panelLocation.x + 310.f, panelLocation.y + 125.f });
		mReturnButton.SetWidgetLocation({ windowSize.x / 2.f - mReturnButton.GetBounds().width / 2.f, panelLocation.y + panelSize.y - 65.f });
		mResumeButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::ResumeButtonClicked);
		mRestartButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::RestartButtonClicked);
		mControlsButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::ControlsButtonClicked);
		mQuitButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::QuitButtonClicked);
		mReturnButton.onButtonClicked.BindAction(GetWeakRef(), &GameplayHUD::ReturnButtonClicked);
	}
	void GameplayHUD::PlayerHealthUpdated(float amt, float currentHealth, float maxHealth)
	{
		mPlayerHealthBar.UpdateValue(currentHealth, maxHealth);
		if (currentHealth / maxHealth < mCriticalThreshold)
		{
			mPlayerHealthBar.SetForegroundColor(mCriticalHealthBarColor);
		}
		else
		{
			mPlayerHealthBar.SetForegroundColor(mHealthyHealthBarColor);
		}
	}

	void GameplayHUD::PlayerLifeCountUpdated(int amt)
	{
		mPlayerLifeText.SetString(std::to_string(amt));
	}

	void GameplayHUD::PlayerScoreUpdated(int newScore)
	{
		mPlayerScoreText.SetString(std::to_string(newScore));
	}

	void GameplayHUD::RefreshHealthBar()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player && !player->GetCurrentSpaceship().expired())
		{
			weak<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
			playerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameplayHUD::PlayerSpaceshipDestoryed);
			HealthComponent& healthComp = player->GetCurrentSpaceship().lock()->GetHealthComp();
			healthComp.onHealthChanged.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);
			PlayerHealthUpdated(0, healthComp.GetHealth(), healthComp.GetMaxHealth());
		}
	}

	void GameplayHUD::ConnectPlayerStatus()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player)
		{
			int lifeCount = player->GetLifeCount();
			mPlayerLifeText.SetString(std::to_string(lifeCount));
			player->onLifeChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerLifeCountUpdated);

			int playerScore = player->GetScore();
			mPlayerScoreText.SetString(std::to_string(playerScore));
			player->onScoreChange.BindAction(GetWeakRef(), &GameplayHUD::PlayerScoreUpdated);
		}
	}
	void GameplayHUD::PlayerSpaceshipDestoryed(Actor* actor)
	{
		RefreshHealthBar();
	}

	void GameplayHUD::ResumeButtonClicked()
	{
		onResumeBtnClicked.Broadcast();
	}

	void GameplayHUD::RestartButtonClicked()
	{
		onRestartBtnClicked.Broadcast();
	}

	void GameplayHUD::ControlsButtonClicked()
	{
		SetControlsVisible(true);
	}

	void GameplayHUD::ReturnButtonClicked()
	{
		SetControlsVisible(false);
	}

	void GameplayHUD::QuitButtonClicked()
	{
		onQuitBtnClicked.Broadcast();
	}

	void GameplayHUD::SetPause(bool paused)
	{
		mIsPaused = paused;
		SetControlsVisible(false);
		mResumeButton.SetVisibility(paused);
		mRestartButton.SetVisibility(paused);
		mControlsButton.SetVisibility(paused);
		mQuitButton.SetVisibility(paused);
		mPauseText.SetVisibility(paused);
	}

	void GameplayHUD::SetControlsVisible(bool visible)
	{
		mShowingControls = visible;
		mControlsTitleText.SetVisibility(visible);
		mControlsKeysText.SetVisibility(visible);
		mControlsActionsText.SetVisibility(visible);
		mReturnButton.SetVisibility(visible);

		mPauseText.SetVisibility(mIsPaused && !visible);
		mResumeButton.SetVisibility(mIsPaused && !visible);
		mRestartButton.SetVisibility(mIsPaused && !visible);
		mControlsButton.SetVisibility(mIsPaused && !visible);
		mQuitButton.SetVisibility(mIsPaused && !visible);
	}

	void GameplayHUD::GameFinished(bool playerWon)
	{
	mIsPaused = false;
	SetControlsVisible(false);
	mWinLoseText.SetVisibility(true);
	mFinalScoreText.SetVisibility(true);
	mPauseText.SetVisibility(false);
	mResumeButton.SetVisibility(false);
	mRestartButton.SetVisibility(true);
	mControlsButton.SetVisibility(false);
	mQuitButton.SetVisibility(true);
		
		int score = PlayerManager::Get().GetPlayer()->GetScore();
		mFinalScoreText.SetString("score: " + std::to_string(score));
		if (playerWon)
		{
			mWinLoseText.SetString("You Win!");

		}
		else
		{
			mWinLoseText.SetString("You Lose!");
		}
	mWinLoseText.SetWidgetLocation({ mWindowSize.x / 2.f - mWinLoseText.GetBounds().width / 2.f, 100.f });
	mFinalScoreText.SetWidgetLocation({ mWindowSize.x / 2.f - mFinalScoreText.GetBounds().width / 2.f, 200.f });
	}
}
