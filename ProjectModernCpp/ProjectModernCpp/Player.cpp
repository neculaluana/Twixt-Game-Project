module Player;
using namespace twixt;

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
		m_color = Point::Color::Black;
	else
		m_color = Point::Color::Red;
}

std::string Player::getName()const
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
