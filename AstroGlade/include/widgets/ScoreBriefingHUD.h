#ifndef ASTROGLADE_GAME_WIDGETS_SCOREBRIEFINGHUD_H
#define ASTROGLADE_GAME_WIDGETS_SCOREBRIEFINGHUD_H

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

		void Draw(sf::RenderWindow& windowRef) override;
		bool HandleEvent(const sf::Event& event) override;

		Delegate<> onStartRunClicked;
		Delegate<> onBackClicked;

	private:
		void Init(const sf::RenderWindow& windowRef) override;

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
		// Set once the player leaves the briefing, so a double press cannot load two worlds.
		bool mTransitioning = false;
	};
}

#endif // ASTROGLADE_GAME_WIDGETS_SCOREBRIEFINGHUD_H
