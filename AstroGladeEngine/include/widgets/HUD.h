#ifndef ASTROGLADE_ENGINE_WIDGETS_HUD_H
#define ASTROGLADE_ENGINE_WIDGETS_HUD_H

#include <SFML/Graphics.hpp>

#include "framework/Object.h"

namespace ly
{
	// Base class for the screen space user interface of a World.
	// Init runs once, on the first frame, when the render window is available.
	class HUD : public Object
	{
	public:
		virtual void Draw(sf::RenderWindow& windowRef) = 0;
		void NativeInit(const sf::RenderWindow& windowRef);
		[[nodiscard]] bool HasInit() const { return mAlreadyInit; }
		virtual bool HandleEvent(const sf::Event& event);
		virtual void Tick(float deltaTime);

	protected:
		HUD() = default;

	private:
		virtual void Init(const sf::RenderWindow& windowRef);
		bool mAlreadyInit = false;
	};
}

#endif // ASTROGLADE_ENGINE_WIDGETS_HUD_H
