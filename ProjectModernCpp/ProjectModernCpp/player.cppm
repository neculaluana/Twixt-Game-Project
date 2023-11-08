module;
export module Player;
#include<cstdint>
import<vector>;
import<string>;
import Point;
import Bridge;

namespace twixt {
	export class Player
	{
	public:
		Player(Point::Color color);
		~Player() = default;
		Point::Color getColor()const;
		void changeColor();
		std::vector<Point> getPoints()const;
		std::vector<Bridge> getBridges()const;
		std::string	getName()const;
		void setName(std::string name);

	private:

		Point::Color m_color;
		std::vector<Point> m_points;
		std::vector<Bridge> m_bridges;
		std::string m_name;

	};
}