#include"Engine.hpp"
void Engine::input()
{
	Event event;
	while(window.pollEvent(event))
	{
		//si on clique sur le bouton pour quiter la fenetre
		if(event.type==Event::Closed)
		{
			window.close();
		}
		//si on clique sur echape
		if(event.type==Event::KeyPressed)
		{
			//Quiter
			if(event.key.code==Keyboard::Escape)
			{
				window.close();
			}
			//Pause
			if(event.key.code==Keyboard::P)//On pause le jeu en cliquant sur la lettre 'P'
			{
				Pause();
			}
			//New Game
			if(currentGameState==GameState::GAMEOVER)
			{
				if(event.key.code==Keyboard::Enter)//Si le jeu s arreter apres colision avec le corps on tape Enter pour recommencer le jeu
				{
					startGame();
				}
			}
			//Direction
			if(event.key.code==Keyboard::Up)
			{
				addDirection(Direction::UP);
			}
			if(event.key.code==Keyboard::Down)
			{
				addDirection(Direction::DOWN);
			}
			if(event.key.code==Keyboard::Left)
			{
				addDirection(Direction::LEFT);
			}
			if(event.key.code==Keyboard::Right)
			{
				addDirection(Direction::RIGHT);
			}
		}
	}
}
void Engine::addDirection(int newDirection)
{
	if(directionQueue.empty())
	{
		directionQueue.emplace_back(newDirection);
	}
	else
	{
		if(directionQueue.back()!=newDirection)
		{
			directionQueue.emplace_back(newDirection);
		}
	}
}