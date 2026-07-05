#pragma once

#include <SFML/Graphics.hpp>

#include "framework/Delegate.h"
#include "widgets/Button.h"
#include "widgets/HUD.h"
#include "widgets/ImageWidget.h"
#include "widgets/TextWidget.h"

namespace ly
{
	class ScoreBriefingHUD : public HUD
	{
	public:
		ScoreBriefingHUD();

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual bool HandleEvent(const sf::Event& event) override;

		Delegate<> onStartRunClicked;
		Delegate<> onBackClicked;

	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;

		void StartRun();
		void Back();

		TextWidget mTitleText;
		TextWidget mVanguardText;
		TextWidget mTwinBladeText;
		TextWidget mHexagonText;
		TextWidget mUFOText;
		TextWidget mBossText;
		TextWidget mMultiplierText;
		TextWidget mPromptText;
		ImageWidget mVanguardIcon;
		ImageWidget mTwinBladeIcon;
		ImageWidget mHexagonIcon;
		ImageWidget mUFOIcon;
		ImageWidget mBossIcon;
		Button mStartButton;
		sf::RectangleShape mPanel;
		bool mTransitioning;
	};
}
