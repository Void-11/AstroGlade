#include "widgets/ScoreBriefingHUD.h"
#include "gameplay/GameAudio.h"

namespace ly
{
	namespace
	{
		void CenterText(TextWidget& text, const sf::Vector2u& windowSize, float y)
		{
			text.SetWidgetLocation({ windowSize.x / 2.f - text.GetBounds().width / 2.f, y });
		}

		void CenterIcon(ImageWidget& icon, float centerX, float centerY)
		{
			sf::FloatRect bounds = icon.GetBounds();
			sf::Vector2f boundsCenter{ bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f };
			sf::Vector2f offset{ centerX - boundsCenter.x, centerY - boundsCenter.y };
			icon.SetWidgetLocation(icon.GetWidgetLocation() + offset);
		}

		float TextCenterY(TextWidget& text)
		{
			sf::FloatRect bounds = text.GetBounds();
			return bounds.top + bounds.height / 2.f;
		}
	}

	ScoreBriefingHUD::ScoreBriefingHUD()
		: mTitleText{"SCORING", "SpaceShooterRedux/Bonus/Oxanium-ExtraBold.ttf"},
		mVanguardText{"VANGUARD - 5"},
		mTwinBladeText{"TWINBLADE - 10"},
		mHexagonText{"HEXAGON - 15"},
		mUFOText{"UFO - 20"},
		mBossText{"BOSS - 100"},
		mMultiplierText{"Multiplier rewards increase score up to x5"},
		mPromptText{"SPACE / ENTER"},
		mVanguardIcon{"SpaceShooterRedux/PNG/Enemies/enemyBlue.png"},
		mTwinBladeIcon{"SpaceShooterRedux/PNG/Enemies/enemyBlack.png"},
		mHexagonIcon{"SpaceShooterRedux/PNG/Enemies/enemyRed6.png"},
		mUFOIcon{"SpaceShooterRedux/PNG/ufo.png"},
		mBossIcon{"SpaceShooterRedux/PNG/Enemies/boss.png"},
		mStartButton{">> START RUN"},
		mPanel{},
		mTransitioning{false}
	{
		const sf::Color astroWhite{245, 248, 255, 255};
		const sf::Color scoreGreen{40, 255, 95, 255};
		const sf::Color panelFill{0, 0, 0, 165};
		const sf::Color transparent{255, 255, 255, 0};
		const sf::Color hoverGlow{0, 255, 90, 55};
		const sf::Color downGlow{0, 180, 65, 90};

		mTitleText.SetTextSize(42);
		mTitleText.SetTextColor(scoreGreen);
		mVanguardText.SetTextSize(24);
		mTwinBladeText.SetTextSize(24);
		mHexagonText.SetTextSize(24);
		mUFOText.SetTextSize(24);
		mBossText.SetTextSize(24);
		mMultiplierText.SetTextSize(18);
		mPromptText.SetTextSize(16);

		mVanguardText.SetTextColor(astroWhite);
		mTwinBladeText.SetTextColor(astroWhite);
		mHexagonText.SetTextColor(astroWhite);
		mUFOText.SetTextColor(astroWhite);
		mBossText.SetTextColor(astroWhite);
		mMultiplierText.SetTextColor(scoreGreen);
		mPromptText.SetTextColor(scoreGreen);

		mStartButton.SetTextSize(20);
		mStartButton.SetButtonColors(transparent, hoverGlow, downGlow);
		mStartButton.SetTextColors(astroWhite, scoreGreen, scoreGreen);

		mVanguardIcon.SetImageScale({0.26f, 0.26f});
		mTwinBladeIcon.SetImageScale({0.25f, 0.25f});
		mHexagonIcon.SetImageScale({0.28f, 0.28f});
		mUFOIcon.SetImageScale({0.2f, 0.2f});
		mBossIcon.SetImageScale({0.14f, 0.14f});

		mVanguardIcon.SetWidgetRotation(-90.f);
		mTwinBladeIcon.SetWidgetRotation(-90.f);
		mHexagonIcon.SetWidgetRotation(-90.f);
		mUFOIcon.SetWidgetRotation(-90.f);
		mBossIcon.SetWidgetRotation(-90.f);

		mPanel.setFillColor(panelFill);
		mPanel.setOutlineColor(sf::Color{0, 255, 90, 220});
		mPanel.setOutlineThickness(2.f);
	}

	void ScoreBriefingHUD::Draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mPanel);
		mTitleText.NativeDraw(windowRef);
		mVanguardIcon.NativeDraw(windowRef);
		mVanguardText.NativeDraw(windowRef);
		mTwinBladeIcon.NativeDraw(windowRef);
		mTwinBladeText.NativeDraw(windowRef);
		mHexagonIcon.NativeDraw(windowRef);
		mHexagonText.NativeDraw(windowRef);
		mUFOIcon.NativeDraw(windowRef);
		mUFOText.NativeDraw(windowRef);
		mBossIcon.NativeDraw(windowRef);
		mBossText.NativeDraw(windowRef);
		mMultiplierText.NativeDraw(windowRef);
		mPromptText.NativeDraw(windowRef);
		mStartButton.NativeDraw(windowRef);
	}

	bool ScoreBriefingHUD::HandleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Return)
			{
				StartRun();
				return true;
			}

			if (event.key.code == sf::Keyboard::Escape)
			{
				Back();
				return true;
			}
		}

		return mStartButton.HandleEvent(event) ||
			   HUD::HandleEvent(event);
	}

	void ScoreBriefingHUD::Init(const sf::RenderWindow& windowRef)
	{
		sf::Vector2u windowSize = windowRef.getSize();
		const sf::Vector2f panelSize{520.f, 560.f};
		const sf::Vector2f panelLocation{
			windowSize.x / 2.f - panelSize.x / 2.f,
			windowSize.y / 2.f - panelSize.y / 2.f
		};

		mPanel.setSize(panelSize);
		mPanel.setPosition(panelLocation);

		CenterText(mTitleText, windowSize, panelLocation.y + 45.f);
		const float iconCenterX = panelLocation.x + 185.f;
		const float textX = panelLocation.x + 215.f;
		const float rowStartY = panelLocation.y + 130.f;
		const float rowSpacing = 50.f;
		mVanguardText.SetWidgetLocation({textX, rowStartY});
		mTwinBladeText.SetWidgetLocation({textX, rowStartY + rowSpacing});
		mHexagonText.SetWidgetLocation({textX, rowStartY + rowSpacing * 2.f});
		mUFOText.SetWidgetLocation({textX, rowStartY + rowSpacing * 3.f});
		mBossText.SetWidgetLocation({textX, rowStartY + rowSpacing * 4.f});
		CenterIcon(mVanguardIcon, iconCenterX, TextCenterY(mVanguardText));
		CenterIcon(mTwinBladeIcon, iconCenterX, TextCenterY(mTwinBladeText));
		CenterIcon(mHexagonIcon, iconCenterX, TextCenterY(mHexagonText));
		CenterIcon(mUFOIcon, iconCenterX, TextCenterY(mUFOText));
		CenterIcon(mBossIcon, iconCenterX, TextCenterY(mBossText));
		CenterText(mMultiplierText, windowSize, panelLocation.y + 405.f);
		CenterText(mPromptText, windowSize, panelLocation.y + 455.f);

		mStartButton.SetWidgetLocation({ windowSize.x / 2.f - mStartButton.GetBounds().width / 2.f, panelLocation.y + panelSize.y - 75.f });
		mStartButton.onButtonClicked.BindAction(GetWeakRef(), &ScoreBriefingHUD::StartRun);
	}

	void ScoreBriefingHUD::StartRun()
	{
		if (mTransitioning)
		{
			return;
		}

		mTransitioning = true;
		GameAudio::PlayUIButton();
		onStartRunClicked.Broadcast();
	}

	void ScoreBriefingHUD::Back()
	{
		if (mTransitioning)
		{
			return;
		}

		mTransitioning = true;
		GameAudio::PlayUIButton();
		onBackClicked.Broadcast();
	}
}
