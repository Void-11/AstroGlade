#ifndef ASTROGLADE_GAME_WIDGETS_MAINMENUHUD_H
#define ASTROGLADE_GAME_WIDGETS_MAINMENUHUD_H

#include "framework/Delegate.h"
#include "widgets/Button.h"
#include "widgets/ControlsPanel.h"
#include "widgets/HUD.h"
#include "widgets/TextWidget.h"

namespace ly
{
	class MainMenuHUD : public HUD
	{
	public:
		MainMenuHUD();

		void Draw(sf::RenderWindow& windowRef) override;
		bool HandleEvent(const sf::Event& event) override;

		Delegate<> onStartButtonClicked;
		Delegate<> onQuitButtonClicked;

	private:
		void Init(const sf::RenderWindow& windowRef) override;

		void StartButtonClicked();
		void ControlsButtonClicked();
		void BackButtonClicked();
		void QuitButtonClicked();
		void SetControlsVisible(bool visible);

		TextWidget mTitleAstroText;
		TextWidget mTitleGladeText;
		Button mStartButton;
		Button mControlsButton;
		Button mQuitButton;
		ControlsPanel mControlsPanel;
	};
}

#endif // ASTROGLADE_GAME_WIDGETS_MAINMENUHUD_H
