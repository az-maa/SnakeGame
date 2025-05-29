#include"Apple.hpp"
sf::Color appleColor(247, 247, 157); 
Apple::Apple()
{
	Vector2f posInit(400,300);
	apple.setSize(Vector2f(20,20));
	apple.setFillColor(appleColor);
	apple.setPosition(posInit);
}
void Apple::setPosition(Vector2f newPosition)
{
	apple.setPosition(newPosition);
}
RectangleShape Apple::getApple()
{
	return apple;
}