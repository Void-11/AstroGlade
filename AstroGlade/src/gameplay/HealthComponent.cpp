#include <algorithm>

#include "gameplay/HealthComponent.h"

namespace ly
{
	HealthComponent::HealthComponent(float health, float maxHealth)
		: mHealth{ health },
		mMaxHealth{ maxHealth }
	{
	}

	void HealthComponent::ChangeHealth(float amt)
	{
		if (amt == 0.f) return;
		if (mHealth == 0.f) return;

		mHealth = std::clamp(mHealth + amt, 0.f, mMaxHealth);

		onHealthChanged.Broadcast(amt, mHealth, mMaxHealth);

		if (amt < 0.f)
		{
			TakenDamage(-amt);
			if (mHealth <= 0.f)
			{
				HealthEmpty();
			}
		}
	}

	void HealthComponent::SetInitialHealth(float health, float maxHealth)
	{
		mHealth = health;
		mMaxHealth = maxHealth;
	}

	void HealthComponent::TakenDamage(float amt)
	{
		onTakenDamage.Broadcast(amt, mHealth, mMaxHealth);
	}

	void HealthComponent::HealthEmpty()
	{
		onHealthEmpty.Broadcast();
	}
}
