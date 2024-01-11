#include "Player.h"

Player::Player(std::string name, Point::Color color, size_t maxPointsCount, size_t maxBridgesCount) :
	m_color(color), m_playerTurn(false) {
}

//Player::Player(std::string name, Point::Color color, size_t maxPointsCount, size_t maxBridgesCount)
//
//{
//}

Player::Player(const Player& other)
	: m_color(other.m_color), m_points(other.m_points), m_bridges(other.m_bridges), m_name(other.m_name),m_playerTurn(other.m_playerTurn){}

Player& Player::operator=(const Player& other) {
	if (this != &other) {
		m_color = other.m_color;
		m_points = other.m_points;
		m_bridges = other.m_bridges;
		m_name = other.m_name;
		m_playerTurn = other.m_playerTurn;
	}
	return *this;
}

Player::Player(Player&& other) noexcept
	: m_color(std::move(other.m_color)), m_points(std::move(other.m_points)), m_bridges(std::move(other.m_bridges)), m_name(std::move(other.m_name)),m_playerTurn(std::move(other.m_playerTurn)) {}


Player& Player::operator=(Player&& other) noexcept {
	if (this != &other) {
		m_color = std::move(other.m_color);
		m_points = std::move(other.m_points);
		m_bridges = std::move(other.m_bridges);
		m_name = std::move(other.m_name);
		m_playerTurn = std::move(other.m_playerTurn);
	}
	return *this;
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
	for ( auto& point : m_points)
	{
		point.setColor(m_color);
	}
	for ( auto& bridge : m_bridges)
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

uint8_t Player::getPointsSize()
{
	return m_points.size();
}

uint8_t Player::getBridgesSize()
{
	return m_bridges.size();
}

size_t Player::getMaxPointsCount()
{
	return m_maxPointsCount;
}

size_t Player::getMaxBridgesCount()
{
	return m_maxBridgesCount;
}

void Player::setMaxPointsCount(size_t maxPoints)
{
	m_maxPointsCount = maxPoints;
}

void Player::setMaxBridgesCount(size_t maxBridges)
{
	m_maxBridgesCount = maxBridges;
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

bool Player::getPlayerTurn()
{
	return m_playerTurn;
}

void Player::setPlayerTurn(bool turn)
{
	m_playerTurn = turn;
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

