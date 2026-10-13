#include "widgets/HUD.h"

namespace ly
{
	void HUD::NativeInit(const sf::RenderWindow& windowRef)
	{
		if (!mAlreadyInit)
		{
			mAlreadyInit = true;
			Init(windowRef);
		}
	}

	bool HUD::HandleEvent([[maybe_unused]] const sf::Event& event)
	{
		return false;
	}

	void HUD::Init([[maybe_unused]] const sf::RenderWindow& windowRef)
	{
	}

	void HUD::Tick([[maybe_unused]] float deltaTime)
	{
	}
}
