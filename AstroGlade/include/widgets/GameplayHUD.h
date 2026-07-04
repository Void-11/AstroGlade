#pragma once
#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGuage.h"
#include "widgets/ImageWidget.h"
#include "widgets/Button.h"

namespace ly
{
	class Actor;
	class GameplayHUD : public HUD
	{
	public:
		GameplayHUD();

		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void Tick(float deltaTime) override;
		virtual bool HandleEvent(const sf::Event& event) override;

		void GameFinished(bool playerWon);
		void SetPause(bool paused);
		void RefreshHealthBar();
		Delegate<> onRestartBtnClicked;
		Delegate<> onQuitBtnClicked;
		Delegate<> onResumeBtnClicked;
	private:
		virtual void Init(const sf::RenderWindow& windowRef) override;
		void ConnectPlayerStatus();
		void PlayerHealthUpdated(float amt, float currentHealth, float maxHealth);
		void PlayerLifeCountUpdated(int amt);
		void PlayerScoreUpdated(int newScore);
		void PlayerSpaceshipDestoryed(Actor* actor);
		void UpdateFrameRate();
		void ResumeButtonClicked();
		void RestartButtonClicked();
		void ControlsButtonClicked();
		void ReturnButtonClicked();
		void QuitButtonClicked();
		void SetControlsVisible(bool visible);
		TextWidget mFramerateText;
		ValueGauge mPlayerHealthBar;
		ImageWidget mPlayerLifeIcon;
		TextWidget mPlayerLifeText;

		ImageWidget mPlayerScoreIcon;
		TextWidget mPlayerScoreText;

		sf::Color mHealthyHealthBarColor;
		sf::Color mCriticalHealthBarColor;
		float mCriticalThreshold;

		float mWidgetSpaceing;
	
		TextWidget mWinLoseText;
		TextWidget mFinalScoreText;
		TextWidget mPauseText;
		TextWidget mControlsTitleText;
		TextWidget mControlsKeysText;
		TextWidget mControlsActionsText;
		Button mResumeButton;
		Button mRestartButton;
		Button mControlsButton;
		Button mQuitButton;
		Button mReturnButton;
		sf::RectangleShape mControlsPanel;
		bool mShowingControls;
		bool mIsPaused;

		sf::Vector2u mWindowSize;
		sf::Clock mFrameRateClock;
		int mFramesSinceRateUpdate;
		float mFrameRateUpdateInterval;
	};
}
