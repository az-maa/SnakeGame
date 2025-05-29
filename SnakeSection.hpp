#ifndef SNAKESECTION_HPP
#define SNAKESECTION_HPP
#include<SFML/Graphics.hpp>
using namespace sf;
class SnakeSection
{
	private:
	Vector2f position;
	RectangleShape section;
	public:
	SnakeSection(Vector2f posInit);
	Vector2f getPosition();
	RectangleShape getShape();
	void setPosition(Vector2f newPosition);
	void update();
};
#endif