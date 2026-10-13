#ifndef ASTROGLADE_GAME_GAMEPLAY_HEALTHCOMPONENT_H
#define ASTROGLADE_GAME_GAMEPLAY_HEALTHCOMPONENT_H

#include "framework/Delegate.h"

namespace ly
{
	class HealthComponent
	{
	public:
		HealthComponent(float health, float maxHealth);

		void ChangeHealth(float amt);
		[[nodiscard]] float GetHealth() const { return mHealth; }
		[[nodiscard]] float GetMaxHealth() const { return mMaxHealth; }
		void SetInitialHealth(float health, float maxHealth);

		// Each health delegate receives (change amount, current health, max health).
		Delegate<float, float, float> onHealthChanged;
		Delegate<float, float, float> onTakenDamage;
		Delegate<> onHealthEmpty;

	private:
		void TakenDamage(float amt);
		void HealthEmpty();

		float mHealth;
		float mMaxHealth;
	};
}

#endif // ASTROGLADE_GAME_GAMEPLAY_HEALTHCOMPONENT_H
