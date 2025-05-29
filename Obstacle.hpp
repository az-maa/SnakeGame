#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP
#include<SFML/Graphics.hpp>
using namespace sf;
class Obstacle
{
	private:
	RectangleShape obstacle;
	public :
	Obstacle();
	RectangleShape getShape();
	void setPosition(Vector2f newPosition);
};
#endif