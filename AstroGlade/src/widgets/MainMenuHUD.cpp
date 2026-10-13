#include <initializer_list>

#include "gameplay/GameAudio.h"
#include "widgets/MainMenuHUD.h"
#include "widgets/MenuStyle.h"

namespace ly
{
	MainMenuHUD::MainMenuHUD()
		: mTitleAstroText{ "ASTRO", MenuStyle::kTitleFontPath },
		mTitleGladeText{ "GLADE", MenuStyle::kTitleFontPath },
		mStartButton{ ">> START" },
		mControlsButton{ ">> CONTROLS" },
		mQuitButton{ ">> QUIT" }
	{
		mTitleAstroText.SetTextSize(44);
		mTitleAstroText.SetTextColor(MenuStyle::kAstroWhite);
		mTitleGladeText.SetTextSize(58);
		mTitleGladeText.SetTextColor(MenuStyle::kGladeGreen);

		for (Button* button : { &mStartButton, &mControlsButton, &mQuitButton })
		{
			MenuStyle::ApplyMenuButtonStyle(*button, 22);
		}

		SetControlsVisible(false);
	}

	void MainMenuHUD::Draw(sf::RenderWindow& windowRef)
	{
		mTitleAstroText.NativeDraw(windowRef);
		mTitleGladeText.NativeDraw(windowRef);
		mControlsPanel.Draw(windowRef);
		mStartButton.NativeDraw(windowRef);
		mControlsButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);
	}

	bool MainMenuHUD::HandleEvent(const sf::Event& event)
	{
		if (mControlsPanel.IsVisible())
		{
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				BackButtonClicked();
				return true;
			}

			return mControlsPanel.HandleEvent(event) || HUD::HandleEvent(event);
		}

		return mStartButton.HandleEvent(event)
			|| mControlsButton.HandleEvent(event)
			|| mQuitButton.HandleEvent(event)
			|| HUD::HandleEvent(event);
	}

	void MainMenuHUD::Init(const sf::RenderWindow& windowRef)
	{
		const sf::Vector2u windowSize = windowRef.getSize();
		MenuStyle::CenterHorizontally(mTitleAstroText, windowSize, 60.f);
		MenuStyle::CenterHorizontally(mTitleGladeText, windowSize, 120.f);

		MenuStyle::CenterHorizontally(mStartButton, windowSize, static_cast<float>(windowSize.y) / 2.f - 5.f);
		mControlsButton.SetWidgetLocation(mStartButton.GetWidgetLocation() + sf::Vector2f{ 0.f, 58.f });
		mQuitButton.SetWidgetLocation(mControlsButton.GetWidgetLocation() + sf::Vector2f{ 0.f, 58.f });

		mControlsPanel.Layout(windowSize);

		mStartButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::StartButtonClicked);
		mControlsButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::ControlsButtonClicked);
		mQuitButton.onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::QuitButtonClicked);
		mControlsPanel.GetReturnButton().onButtonClicked.BindAction(GetWeakRef(), &MainMenuHUD::BackButtonClicked);
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
		mTitleAstroText.SetVisibility(!visible);
		mTitleGladeText.SetVisibility(!visible);
		mStartButton.SetVisibility(!visible);
		mControlsButton.SetVisibility(!visible);
		mQuitButton.SetVisibility(!visible);

		mControlsPanel.SetVisible(visible);
	}
}
