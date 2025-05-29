#include"SnakeSection.hpp"
sf::Color snakeColor(161, 227, 216);   // Pastel Mint Green (#A1E3D8)
SnakeSection::SnakeSection(Vector2f posInit)
{
	section.setSize(Vector2f(20,20));
	section.setFillColor(snakeColor);
	section.setPosition(posInit);
	position=posInit;
}
Vector2f SnakeSection::getPosition()
{
	return position;
}
void SnakeSection::setPosition(Vector2f newPosition)
{
	position=newPosition;
}
RectangleShape SnakeSection::getShape()
{
	return section;
}
void SnakeSection::update()
{
	section.setPosition(position);
}