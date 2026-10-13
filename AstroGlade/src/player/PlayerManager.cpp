#include <cstddef>

#include "player/PlayerManager.h"

namespace ly
{
	namespace
	{
		Player* FindPlayer(const List<unique<Player>>& players, int playerIndex)
		{
			if (playerIndex < 0 || static_cast<std::size_t>(playerIndex) >= players.size())
			{
				return nullptr;
			}

			return players[static_cast<std::size_t>(playerIndex)].get();
		}
	}

	PlayerManager& PlayerManager::Get()
	{
		static PlayerManager playerManager;
		return playerManager;
	}

	Player& PlayerManager::CreateNewPlayer()
	{
		return *mPlayers.emplace_back(std::make_unique<Player>());
	}

	Player* PlayerManager::GetPlayer(int playerIndex)
	{
		return FindPlayer(mPlayers, playerIndex);
	}

	const Player* PlayerManager::GetPlayer(int playerIndex) const
	{
		return FindPlayer(mPlayers, playerIndex);
	}

	void PlayerManager::Reset()
	{
		mPlayers.clear();
	}
}
