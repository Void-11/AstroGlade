#include <initializer_list>
#include <utility>

#include "gameplay/GameAudio.h"
#include "widgets/MenuStyle.h"
#include "widgets/ScoreBriefingHUD.h"

namespace ly
{
	namespace
	{
		void CenterIcon(ImageWidget& icon, float centerX, float centerY)
		{
			const sf::Vector2f boundsCenter = icon.GetCenterPosition();
			const sf::Vector2f offset{ centerX - boundsCenter.x, centerY - boundsCenter.y };
			icon.SetWidgetLocation(icon.GetWidgetLocation() + offset);
		}

		float TextCenterY(const TextWidget& text)
		{
			return text.GetCenterPosition().y;
		}
	}

	ScoreBriefingHUD::ScoreBriefingHUD()
		: mTitleText{ "SCORING", MenuStyle::kTitleFontPath },
		mVanguardText{ "VANGUARD - 5" },
		mTwinBladeText{ "TWINBLADE - 10" },
		mHexagonText{ "HEXAGON - 15" },
		mUFOText{ "UFO - 20" },
		mBossText{ "BOSS - 100" },
		mMultiplierText{ "Multiplier rewards increase score up to x5" },
		mPromptText{ "SPACE / ENTER" },
		mVanguardIcon{ "SpaceShooterRedux/PNG/Enemies/enemyBlue.png" },
		mTwinBladeIcon{ "SpaceShooterRedux/PNG/Enemies/enemyBlack.png" },
		mHexagonIcon{ "SpaceShooterRedux/PNG/Enemies/enemyRed6.png" },
		mUFOIcon{ "SpaceShooterRedux/PNG/ufo.png" },
		mBossIcon{ "SpaceShooterRedux/PNG/Enemies/boss.png" },
		mStartButton{ ">> START RUN" }
	{
		mTitleText.SetTextSize(42);
		mTitleText.SetTextColor(MenuStyle::kMenuGreen);

		for (TextWidget* enemyText : { &mVanguardText, &mTwinBladeText, &mHexagonText, &mUFOText, &mBossText })
		{
			enemyText->SetTextSize(24);
			enemyText->SetTextColor(MenuStyle::kAstroWhite);
		}

		mMultiplierText.SetTextSize(18);
		mMultiplierText.SetTextColor(MenuStyle::kMenuGreen);
		mPromptText.SetTextSize(16);
		mPromptText.SetTextColor(MenuStyle::kMenuGreen);

		MenuStyle::ApplyMenuButtonStyle(mStartButton, 20);

		mVanguardIcon.SetImageScale({ 0.26f, 0.26f });
		mTwinBladeIcon.SetImageScale({ 0.25f, 0.25f });
		mHexagonIcon.SetImageScale({ 0.28f, 0.28f });
		mUFOIcon.SetImageScale({ 0.2f, 0.2f });
		mBossIcon.SetImageScale({ 0.14f, 0.14f });

		for (ImageWidget* enemyIcon : { &mVanguardIcon, &mTwinBladeIcon, &mHexagonIcon, &mUFOIcon, &mBossIcon })
		{
			enemyIcon->SetWidgetRotation(-90.f);
		}

		MenuStyle::ApplyPanelStyle(mPanel);
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

		return mStartButton.HandleEvent(event) || HUD::HandleEvent(event);
	}

	void ScoreBriefingHUD::Init(const sf::RenderWindow& windowRef)
	{
		const sf::Vector2u windowSize = windowRef.getSize();
		const sf::Vector2f panelSize{ 520.f, 560.f };
		const sf::Vector2f panelLocation{
			static_cast<float>(windowSize.x) / 2.f - panelSize.x / 2.f,
			static_cast<float>(windowSize.y) / 2.f - panelSize.y / 2.f
		};

		mPanel.setSize(panelSize);
		mPanel.setPosition(panelLocation);

		MenuStyle::CenterHorizontally(mTitleText, windowSize, panelLocation.y + 45.f);

		// Each icon sits centered left of its label, and the rows are then centered in the panel as one block.
		const float iconCenterX = panelLocation.x;
		const float textX = iconCenterX + 30.f;
		const float rowStartY = panelLocation.y + 130.f;
		const float rowSpacing = 50.f;

		const std::initializer_list<std::pair<TextWidget*, ImageWidget*>> rows{
			{ &mVanguardText, &mVanguardIcon },
			{ &mTwinBladeText, &mTwinBladeIcon },
			{ &mHexagonText, &mHexagonIcon },
			{ &mUFOText, &mUFOIcon },
			{ &mBossText, &mBossIcon }
		};

		float rowY = rowStartY;
		for (const auto& [text, icon] : rows)
		{
			text->SetWidgetLocation({ textX, rowY });
			CenterIcon(*icon, iconCenterX, TextCenterY(*text));
			rowY += rowSpacing;
		}

		MenuStyle::CenterGroupHorizontally(
			{
				&mVanguardIcon, &mVanguardText,
				&mTwinBladeIcon, &mTwinBladeText,
				&mHexagonIcon, &mHexagonText,
				&mUFOIcon, &mUFOText,
				&mBossIcon, &mBossText
			},
			panelLocation.x + panelSize.x / 2.f
		);

		MenuStyle::CenterHorizontally(mMultiplierText, windowSize, panelLocation.y + 405.f);
		MenuStyle::CenterHorizontally(mPromptText, windowSize, panelLocation.y + 455.f);

		MenuStyle::CenterHorizontally(mStartButton, windowSize, panelLocation.y + panelSize.y - 75.f);
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
