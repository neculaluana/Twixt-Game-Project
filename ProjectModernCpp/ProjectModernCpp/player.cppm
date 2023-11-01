module;
#include<cstdint>
export module Player;
import<vector>;

namespace twixt {
	export class Player
	{
	public:
		Player(Color color);
		~Player() = default;
		Color getColor()const;
		std::vector<Point> getPoints()const;
		std::vector<Bridge> getBridges()const;
	private:

		Color m_color;
		std::vector<Point> m_points;
		std::vector<Bridge> m_bridges;

	};
}