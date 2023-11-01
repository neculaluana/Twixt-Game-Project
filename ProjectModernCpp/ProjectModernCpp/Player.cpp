module Player;
using namespace twixt;

Player::Player(Color color) :
	m_color(color) {
}
Color Player::getColor() const
{
	return m_color;
}
void Player::changeColor()
{
	if (m_color == Color::Red)
		m_color = Color::Black;
	else
		m_color = Color::Red;
}

std::string getName()const
{
	return m_name;
}

void setName(std::string name)
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
