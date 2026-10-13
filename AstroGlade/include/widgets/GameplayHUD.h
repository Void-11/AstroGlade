#ifndef ASTROGLADE_GAME_WIDGETS_GAMEPLAYHUD_H
#define ASTROGLADE_GAME_WIDGETS_GAMEPLAYHUD_H

#include "framework/Delegate.h"
#include "widgets/Button.h"
#include "widgets/ControlsPanel.h"
#include "widgets/HUD.h"
#include "widgets/ImageWidget.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"

namespace ly
{
	class Actor;

	// The in-game overlay: health, lives, score and frame rate, plus the pause and game over menus.
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		void Draw(sf::RenderWindow& windowRef) override;
		bool HandleEvent(const sf::Event& event) override;

		void GameFinished(bool playerWon);
		void SetPause(bool paused);
		void RefreshHealthBar();

		Delegate<> onRestartBtnClicked;
		Delegate<> onQuitBtnClicked;
		Delegate<> onResumeBtnClicked;

	private:
		void Init(const sf::RenderWindow& windowRef) override;
		void ConnectPlayerStatus();
		void PlayerHealthUpdated(float amt, float currentHealth, float maxHealth);
		void PlayerLifeCountUpdated(int lifeCount);
		void PlayerScoreUpdated(int newScore);
		void PlayerSpaceshipDestroyed(Actor* actor);
		void UpdateFrameRate();
		void ResumeButtonClicked();
		void RestartButtonClicked();
		void ControlsButtonClicked();
		void ReturnButtonClicked();
		void QuitButtonClicked();
		void SetControlsVisible(bool visible);
		void CenterGameOverTexts();

		TextWidget mFramerateText;
		ValueGauge mPlayerHealthBar;
		ImageWidget mPlayerLifeIcon;
		TextWidget mPlayerLifeText;

		ImageWidget mPlayerScoreIcon;
		TextWidget mPlayerScoreText;

		sf::Color mHealthyHealthBarColor{ 40, 255, 95, 255 };
		sf::Color mCriticalHealthBarColor{ 255, 0, 0, 255 };
		// The health bar turns red below this fraction of the maximum health.
		float mCriticalThreshold = 0.3f;

		float mWidgetSpacing = 10.f;
		// Distance between the HUD and the window edges.
		float mScreenMargin = 20.f;

		sf::RectangleShape mScreenDim;
		TextWidget mWinLoseText;
		TextWidget mFinalScoreText;
		TextWidget mPauseText;
		Button mResumeButton;
		Button mRestartButton;
		Button mControlsButton;
		Button mQuitButton;
		// Vertical distance between the tops of consecutive menu buttons.
		float mMenuButtonSpacing = 58.f;
		ControlsPanel mControlsPanel;
		bool mIsPaused = false;
		bool mIsGameFinished = false;

		sf::Vector2u mWindowSize;
		sf::Clock mFrameRateClock;
		int mFramesSinceRateUpdate = 0;
		float mFrameRateUpdateInterval = 0.25f;
	};
}

#endif // ASTROGLADE_GAME_WIDGETS_GAMEPLAYHUD_H
