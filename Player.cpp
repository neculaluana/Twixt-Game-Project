#pragma once
#include"Player.h"
Player::Player(Color color) :
	m_color(color) {
}
Color Player::getColor() const
{
	return m_color;
}
std::vector<Point> Player::getPoints() const
{
	return m_points;
}
std::vector<Bridge> Player::getBridges() const
{
	return m_bridges;
}
;
