#include "widgets/MainMenuHUD.h"
#include "gameplay/GameAudio.h"

namespace ly
{
	MainMenuHUD::MainMenuHUD()
		: mTitleAstroText{"ASTRO", "SpaceShooterRedux/Bonus/Oxanium-ExtraBold.ttf"},
		mTitleGladeText{"GLADE", "SpaceShooterRedux/Bonus/Oxanium-ExtraBold.ttf"},
		mControlsTitleText{"CONTROLS", "SpaceShooterRedux/Bonus/Oxanium-ExtraBold.ttf"},
		mControlsKeysText{"W / UP\nA / LEFT\nS / DOWN\nD / RIGHT\nSPACE\nESC"},
		mControlsActionsText{"MOVE UP\nMOVE LEFT\nMOVE DOWN\nMOVE RIGHT\nSHOOT\nPAUSE/MENU"},
		mStartButton{">> START"},
		mControlsButton{">> CONTROLS"},
		mQuitButton{">> QUIT"},
		mBackButton{">> RETURN"},
		mShowingControls{false}
	{
		const sf::Color astroWhite{245, 248, 255, 255};
		const sf::Color gladeGreen{0, 255, 80, 255};
		const sf::Color menuGreen{40, 255, 95, 255};
		const sf::Color transparent{255, 255, 255, 0};
		const sf::Color hoverGlow{0, 255, 90, 55};
		const sf::Color downGlow{0, 180, 65, 90};

		mTitleAstroText.SetTextSize(44);
		mTitleAstroText.SetTextColor(astroWhite);
		mTitleGladeText.SetTextSize(58);
		mTitleGladeText.SetTextColor(gladeGreen);
		mControlsTitleText.SetTextSize(36);
		mControlsTitleText.SetTextColor(menuGreen);
		mControlsKeysText.SetTextSize(22);
		mControlsKeysText.SetTextColor(menuGreen);
		mControlsActionsText.SetTextSize(22);
		mControlsActionsText.SetTextColor(astroWhite);
		mStartButton.SetTextSize(22);
		mControlsButton.SetTextSize(22);
		mQuitButton.SetTextSize(22);
		mBackButton.SetTextSize(18);

		mStartButton.SetButtonColors(transparent, hoverGlow, downGlow);
		mControlsButton.SetButtonColors(transparent, hoverGlow, downGlow);
		mQuitButton.SetButtonColors(transparent, hoverGlow, downGlow);
		mBackButton.SetButtonColors(transparent, hoverGlow, downGlow);

		mStartButton.SetTextColors(astroWhite, menuGreen, menuGreen);
		mControlsButton.SetTextColors(astroWhite, menuGreen, menuGreen);
		mQuitButton.SetTextColors(astroWhite, menuGreen, menuGreen);
		mBackButton.SetTextColors(astroWhite, menuGreen, menuGreen);

		mControlsPanel.setFillColor(sf::Color{0, 0, 0, 165});
		mControlsPanel.setOutlineColor(sf::Color{0, 255, 90, 220});
		mControlsPanel.setOutlineThickness(2.f);
		SetControlsVisible(false);
	}
	void MainMenuHUD::Draw(sf::RenderWindow& windowRef)
	{
		mTitleAstroText.NativeDraw(windowRef);
		mTitleGladeText.NativeDraw(windowRef);
		if (mShowingControls)
		{
			windowRef.draw(mControlsPanel);
		}
		mControlsTitleText.NativeDraw(windowRef);
		mControlsKeysText.NativeDraw(windowRef);
		mControlsActionsText.NativeDraw(windowRef);
		mStartButton.NativeDraw(windowRef);
		mControlsButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);
		mBackButton.NativeDraw(windowRef);
	}
	bool MainMenuHUD::HandleEvent(const sf::Event& event)
	{
		if (mShowingControls)
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				BackButtonClicked();
				return true;
			}

			return mBackButton.HandleEvent(event) ||
				   HUD::HandleEvent(event);
		}

		return mStartButton.HandleEvent(event) ||
			   mControlsButton.HandleEvent(event) ||
			   mQuitButton.HandleEvent(event) ||
			   HUD::HandleEvent(event);
	}

	void MainMenuHUD::Init(const sf::RenderWindow& windowRef)
	{
		sf::Vector2u windowSize = windowRef.getSize();
		mTitleAstroText.SetWidgetLocation({ windowSize.x / 2.f - mTitleAstroText.GetBounds().width / 2.f, 60.f });
		mTitleGladeText.SetWidgetLocation({ windowSize.x / 2.f - mTitleGladeText.GetBounds().width / 2.f, 120.f });

		mStartButton.SetWidgetLocation({ windowSize.x / 2.f - mStartButton.GetBounds().width / 2.f, windowSize.y / 2.f - 5.f });
		mControlsButton.SetWidgetLocation(mStartButton.GetWidgetLocation() + sf::Vector2f{0.f, 58.f});
		mQuitButton.SetWidgetLocation(mControlsButton.GetWidgetLocation() + sf::Vector2f{0.f, 58.f});

		const sf::Vector2f panelSize{640.f, 420.f};
		const sf::Vector2f panelLocation{
			windowSize.x / 2.f - panelSize.x / 2.f,
			windowSize.y / 2.f - panelSize.y / 2.f
		};
		mControlsPanel.setSize(panelSize);
		mControlsPanel.setPosition(panelLocation);
		mControlsTitleText.SetWidgetLocation({ windowSize.x / 2.f - mControlsTitleText.GetBounds().width / 2.f, panelLocation.y + 45.f });
		mControlsKeysText.SetWidgetLocation({ panelLocation.x + 150.f, panelLocation.y + 125.f });
		mControlsActionsText.SetWidgetLocation({ panelLocation.x + 310.f, panelLocation.y + 125.f });
		mBackButton.SetWidgetLocation({ windowSize.x / 2.f - mBackButton.GetBounds().width / 2.f, panelLocation.y + panelSize.y - 65.f });
		mStartButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::StartButtonClicked);
		mControlsButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::ControlsButtonClicked);
		mQuitButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::QuitButtonClicked);
		mBackButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::BackButtonClicked);
	}
	void MainMenuHUD::StartButtonClicked()
	{
		GameAudio::PlayUIButton();
		onStartButtonClicked.Broadcast();
	}
	void MainMenuHUD::ControlsButtonClicked()
	{
		GameAudio::PlayUIButton();
		SetControlsVisible(true);
	}
	void MainMenuHUD::BackButtonClicked()
	{
		GameAudio::PlayUIButton();
		SetControlsVisible(false);
	}
	void MainMenuHUD::QuitButtonClicked()
	{
		GameAudio::PlayUIButton();
		onQuitButtonClicked.Broadcast();
	}
	void MainMenuHUD::SetControlsVisible(bool visible)
	{
		mShowingControls = visible;
		mTitleAstroText.SetVisibility(!visible);
		mTitleGladeText.SetVisibility(!visible);
		mStartButton.SetVisibility(!visible);
		mControlsButton.SetVisibility(!visible);
		mQuitButton.SetVisibility(!visible);

		mControlsTitleText.SetVisibility(visible);
		mControlsKeysText.SetVisibility(visible);
		mControlsActionsText.SetVisibility(visible);
		mBackButton.SetVisibility(visible);
	}
}
