#include "widgets/ControlsPanel.h"
#include "widgets/MenuStyle.h"

namespace ly
{
	ControlsPanel::ControlsPanel()
		: mTitleText{ "CONTROLS", MenuStyle::kTitleFontPath },
		mKeysText{ "W / UP\nA / LEFT\nS / DOWN\nD / RIGHT\nSPACE\nLEFT SHIFT\nESC" },
		mActionsText{ "MOVE UP\nMOVE LEFT\nMOVE DOWN\nMOVE RIGHT\nSHOOT\nHOLD BOOST\nPAUSE/MENU" },
		mReturnButton{ ">> RETURN" }
	{
		mTitleText.SetTextSize(36);
		mTitleText.SetTextColor(MenuStyle::kMenuGreen);
		mKeysText.SetTextSize(22);
		mKeysText.SetTextColor(MenuStyle::kMenuGreen);
		mActionsText.SetTextSize(22);
		mActionsText.SetTextColor(MenuStyle::kAstroWhite);
		MenuStyle::ApplyMenuButtonStyle(mReturnButton, 18);
		MenuStyle::ApplyPanelStyle(mPanel);

		SetVisible(false);
	}

	void ControlsPanel::Layout(const sf::Vector2u& windowSize)
	{
		const sf::Vector2f panelSize{ kPanelWidth, kPanelHeight };
		const sf::Vector2f panelLocation{
			static_cast<float>(windowSize.x) / 2.f - panelSize.x / 2.f,
			static_cast<float>(windowSize.y) / 2.f - panelSize.y / 2.f
		};

		mPanel.setSize(panelSize);
		mPanel.setPosition(panelLocation);
		MenuStyle::CenterHorizontally(mTitleText, windowSize, panelLocation.y + 45.f);
		// The key and action columns read as one table, centered in the panel as a whole.
		mKeysText.SetWidgetLocation({ panelLocation.x, panelLocation.y + 125.f });
		mActionsText.SetWidgetLocation({ panelLocation.x + kActionColumnOffset, panelLocation.y + 125.f });
		MenuStyle::CenterGroupHorizontally({ &mKeysText, &mActionsText }, panelLocation.x + panelSize.x / 2.f);
		MenuStyle::CenterHorizontally(mReturnButton, windowSize, panelLocation.y + panelSize.y - 65.f);
	}

	void ControlsPanel::Draw(sf::RenderWindow& windowRef)
	{
		if (!mIsVisible)
		{
			return;
		}

		windowRef.draw(mPanel);
		mTitleText.NativeDraw(windowRef);
		mKeysText.NativeDraw(windowRef);
		mActionsText.NativeDraw(windowRef);
		mReturnButton.NativeDraw(windowRef);
	}

	bool ControlsPanel::HandleEvent(const sf::Event& event)
	{
		return mIsVisible && mReturnButton.HandleEvent(event);
	}

	void ControlsPanel::SetVisible(bool visible)
	{
		mIsVisible = visible;
		mTitleText.SetVisibility(visible);
		mKeysText.SetVisibility(visible);
		mActionsText.SetVisibility(visible);
		mReturnButton.SetVisibility(visible);
	}
}
