#include "Player.h"

Player::Player(std::string name, Point::Color color):
	m_color(color) {
}
Point::Color Player::getColor() const
{
	return m_color;
}
void Player::changeColor()
{
	if (m_color == Point::Color::Red)
	{
		m_color = Point::Color::Black;
		
	}
	else
		m_color = Point::Color::Red;
	for (const auto& point : m_points)
	{
		point.setColor(m_color);
	}
	for (const auto& bridge : m_bridges)
	{
		bridge.setColor(m_color);
	}
}

std::string	Player::getName()const
{
	return m_name;
}


void Player::setName(std::string name)
{
	m_name = name;
}

std::vector<Point> Player::getPoints() const
{
	return m_points;
}
std::vector<Bridge> Player::getBridges() const
{
	return m_bridges;
}

void Player::addPoint(const Point& p)
{
	m_points.push_back(p);
}

void Player::addBridge(const Bridge& bridge)
{
	m_bridges.push_back(bridge);
}

void Player::removePoint(const Point& p)
{
	for (std::vector<Point>::iterator it = m_points.begin(); it != m_points.end();)
	{
		if (it->getCoordinates().first == p.getCoordinates().first && it->getCoordinates().second == p.getCoordinates().second)
		{
			it = m_points.erase(it);
		}
		else
		{
			++it;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
	os << player.m_name << std::endl;
	os << player.m_points.size() << std::endl;
	for (const auto& point : player.m_points) {
		os << point.getCoordinates().first << " " << point.getCoordinates().second << std::endl;
	}

	return os;
}

std::istream& operator>>(std::istream& is, Player& player) {
	std::getline(is, player.m_name);
	size_t numberOfPoints;
	is >> numberOfPoints;
	is.ignore(); 
	player.m_points.clear(); 
	for (size_t i = 0; i < numberOfPoints; ++i) {
		uint8_t x, y;
		is >> x >>y;
		Point p(x, y, player.getColor());
		player.m_points.push_back(p);
	}

	return is;
}

