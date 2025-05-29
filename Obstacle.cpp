#include"Obstacle.hpp"
sf::Color obstacleColor(255, 111, 97);  // Vibrant Coral (#FF6F61)
Obstacle ::Obstacle()
{
    Vector2f posInit(500,600);
    obstacle.setSize(Vector2f(40.f,200.f));
	obstacle.setFillColor(obstacleColor);
	obstacle.setPosition(posInit);
}
void Obstacle::setPosition(Vector2f newPosition)
{
	obstacle.setPosition(newPosition);
}
RectangleShape Obstacle::getShape()
{
	return obstacle;
}
