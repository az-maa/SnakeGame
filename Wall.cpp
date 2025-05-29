#include"Wall.hpp"

sf::Color wallColor(241, 195, 163);    // Peachy Beige (#F1C3A3)
Wall::Wall(Vector2f position,Vector2f size)
{
	wallShape.setSize(size);
	wallShape.setFillColor(wallColor);
	wallShape.setPosition(position);
}
RectangleShape Wall::getShape()
{
	return wallShape;
}