#ifndef ASTROGLADE_GAME_PLAYER_PLAYERMANAGER_H
#define ASTROGLADE_GAME_PLAYER_PLAYERMANAGER_H

#include "framework/Core.h"
#include "player/Player.h"

namespace ly
{
	// Owns the players of the current game session.
	class PlayerManager
	{
	public:
		[[nodiscard]] static PlayerManager& Get();

		PlayerManager(const PlayerManager&) = delete;
		PlayerManager& operator=(const PlayerManager&) = delete;

		Player& CreateNewPlayer();
		[[nodiscard]] Player* GetPlayer(int playerIndex = 0);
		[[nodiscard]] const Player* GetPlayer(int playerIndex = 0) const;
		void Reset();

	private:
		PlayerManager() = default;

		// Players are heap allocated so the references handed out stay valid as the list grows.
		List<unique<Player>> mPlayers;
	};
}

#endif // ASTROGLADE_GAME_PLAYER_PLAYERMANAGER_H
