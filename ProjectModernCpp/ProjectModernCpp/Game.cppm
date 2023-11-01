module;
#include <cstdint>

export module Game;

import Player;
import Board;

namespace twixt {
	export class Game {
	public:
		void changeCurrentPlayer();
		bool wonGame() const;
		bool drawGame() const;
	private:
		Player m_player1;
		Player m_player2;
		Player m_currentPlayer;
		Board m_board;
	};
}