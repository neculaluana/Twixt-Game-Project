#include "Player.h"

Player::Player(std::string name, Point::Color color, size_t maxPointsCount, size_t maxBridgesCount) :
	m_color(color), m_playerTurn(false) {
}



Player::Player(const Player& other)
	: m_color(other.m_color), m_points(other.m_points), m_bridges(other.m_bridges), m_name(other.m_name), m_playerTurn(other.m_playerTurn) {}

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
	: m_color(std::move(other.m_color)), m_points(std::move(other.m_points)), m_bridges(std::move(other.m_bridges)), m_name(std::move(other.m_name)), m_playerTurn(std::move(other.m_playerTurn)) {}


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
	for (auto& point : m_points)
	{
		point.setColor(m_color);
	}
	for (auto& bridge : m_bridges)
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
void Player::serialize(json& j) const {
	j["m_color"] = static_cast<int>(m_color);
	j["m_points"] = json::array();
	for (const Point& point : m_points) {
		json pointJson;
		pointJson = point.serialize();
		j["m_points"].push_back(pointJson);
	}
	j["m_bridges"] = json::array();
	for (const Bridge& bridge : m_bridges) {
		json bridgeJson;
		bridge.serialize(bridgeJson);
		j["m_bridges"].push_back(bridgeJson);
	}
	j["m_name"] = m_name;
	j["m_playerTurn"] = m_playerTurn;
	j["m_maxPointsCount"] = m_maxPointsCount;
	j["m_maxBridgesCount"] = m_maxBridgesCount;
}
void Player::deserialize(const json& j) {
	if (j.contains("m_color")) {
		m_color = static_cast<Point::Color>(j["m_color"].get<int>());
	}
	if (j.contains("m_points") && j["m_points"].is_array()) {
		m_points.clear();
		for (const json& pointJson : j["m_points"]) {
			Point point;
			point.deserialize(pointJson);
			m_points.push_back(point);
		}
	}
	if (j.contains("m_bridges") && j["m_bridges"].is_array()) {
		m_bridges.clear();
		for (const json& bridgeJson : j["m_bridges"]) {
			Bridge bridge;
			bridge.deserialize(bridgeJson);
			m_bridges.push_back(bridge);
		}
	}
	if (j.contains("m_name")) {
		m_name = j["m_name"].get<std::string>();
	}
	if (j.contains("m_playerTurn")) {
		m_playerTurn = j["m_playerTurn"].get<bool>();
	}
	if (j.contains("m_maxPointsCount")) {
		m_maxPointsCount = j["m_maxPointsCount"].get<size_t>();
	}
	if (j.contains("m_maxBridgesCount")) {
		m_maxBridgesCount = j["m_maxBridgesCount"].get<size_t>();
	}
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

void Player::removeBridge(const Bridge& b)
{
	for (std::vector<Bridge>::iterator it = m_bridges.begin(); it != m_bridges.end();)
	{
		if (it->getStartPoint() == b.getStartPoint() && it->getEndPoint() == b.getEndPoint())
		{
			it = m_bridges.erase(it);
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

bool Player::getfirstMoveMade()
{
	return m_firstMoveMade;
}

void Player::setfirstMoveMade(bool moveMade)
{
	m_firstMoveMade = moveMade;
}

void Player::popFirstPoint()
{
	m_points.pop_back();
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
	for (size_t index = 0; index < numberOfPoints; ++index) {
		uint8_t x, y;
		is >> x >> y;
		Point p(x, y, player.getColor());
		player.m_points.push_back(p);
	}

	return is;
}

