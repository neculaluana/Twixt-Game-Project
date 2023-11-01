module;
#include <cstdint>

export module Game;

import Player;
import Board;
import Point;
import Bridge;

namespace twixt {
	export class Game {
	public:
		Game() = default;
		void startNewGame();
		void loadGame();
		bool isPointPossible(uint8_t x, uint8_t y);
		void makePoint();
		void makeBridges();
		void changeCurrentPlayer();
		bool wonGame() const;
		bool drawGame() const;
		~Game() = default;
	private:
		Player m_playerRed;
		Player m_playerBlack;
		Player m_currentPlayer;
		Board m_board;
	};
}