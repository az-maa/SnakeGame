#include"Engine.hpp"
void Engine::update()
{
	//Update la position du serpent
	if(timeSinceLastMove.asSeconds()>=seconds(1.f/float(speed)).asSeconds())
	{
      Vector2f thisSectionPosition = snake[0].getPosition();//la position de la tete
      Vector2f lastSectionPosition=thisSectionPosition;
      if(!directionQueue.empty())
      {
      	switch(snakeDirection)
      	{
      		//on n a pas a faire un changement si la queue contenait deja la cle voulu
      	case Direction::UP:
      		if(directionQueue.front()!=Direction::DOWN)
      		{
      			snakeDirection= directionQueue.front();

      		}
      	break;
      case Direction::DOWN:
      		if(directionQueue.front()!=Direction::UP)
      		{
      			snakeDirection= directionQueue.front();

      		}
      	break;
      case Direction::RIGHT:
      		if(directionQueue.front()!=Direction::LEFT)
      		{
      			snakeDirection= directionQueue.front();

      		}
      	break;
      case Direction::LEFT:
      		if(directionQueue.front()!=Direction::RIGHT)
      		{
      			snakeDirection= directionQueue.front();

      		}
      	break;
      	}
      	//On supprime la cle qui vient d etre utiliser 
      	directionQueue.pop_front();
      }
      //On augmente le score a chaque fois que le snake move
      score+=snake.size()+(applesEatenTotal+1);
      scoreText.setString("Score :"+to_string(score));
      FloatRect scoreTextBounds=scoreText.getLocalBounds();
      scoreText.setPosition(Vector2f(resolution.x-scoreTextBounds.width-50,-9));
      //Si on a besoin d augmenter le serpent
      if(sectionsToAdd)
      {
      	addSnakeSection();
      	sectionsToAdd--;
      }
      //Mise a jour de la postion de la tete du serpent
      switch(snakeDirection)
      {
      case Direction::RIGHT:
      	snake[0].setPosition(Vector2f(thisSectionPosition.x+20,thisSectionPosition.y));
      	break;
      case Direction::DOWN:
      	snake[0].setPosition(Vector2f(thisSectionPosition.x,thisSectionPosition.y+20));
      	break;
      	 case Direction::LEFT:
      	snake[0].setPosition(Vector2f(thisSectionPosition.x-20,thisSectionPosition.y));
      	break;
      case Direction::UP:
      	snake[0].setPosition(Vector2f(thisSectionPosition.x,thisSectionPosition.y-20));
      	break;
      }
      //Mise a jour de la position de la queue du serpent
      for(int s=1;s<snake.size();s++)
      {
      	thisSectionPosition=snake[s].getPosition();
      	snake[s].setPosition(lastSectionPosition);
      	lastSectionPosition=thisSectionPosition;
      }
      for(auto & s : snake)
      {
      	s.update();
      }
      //Detecter si le serpent rencontre le fruit
      if(snake[0].getShape().getGlobalBounds().intersects(fruit.getApple().getGlobalBounds()))
      {
      	applesEatenThisLevel+=1;
      	applesEatenTotal+=1;
      	applesEatenText.setString("Apple: "+to_string(applesEatenTotal));
      
      	sectionsToAdd+=4;
      	speed++;
      	moveApple();
      }

      //Detection de la colusion avec le corps du serpent
      for(int s=1;s<snake.size();s++)
      {
      	if(snake[0].getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds()))
      	{
      		//Game Over 
      		currentGameState=GameState::GAMEOVER;
      	}
      }
      //Detection de la colusion avec les obstacles
       if(snake[0].getShape().getGlobalBounds().intersects(obstacle1.getShape().getGlobalBounds()))
      {
      	currentGameState=GameState::GAMEOVER;
      }
       if(snake[0].getShape().getGlobalBounds().intersects(obstacle2.getShape().getGlobalBounds()))
      {
      	currentGameState=GameState::GAMEOVER;
      }



//Detection de la colusion avec les murs
auto& head = snake.front();
Vector2f windowSize(window.getSize().x, window.getSize().y);

for (auto& w : wallSections) {
    if (head.getShape().getGlobalBounds().intersects(w.getShape().getGlobalBounds())) {
        Vector2f newPosition;

        // Teleporter le serpant a base de sa position
        switch (snakeDirection) {
            case Direction::UP:
                newPosition = Vector2f(head.getShape().getPosition().x, windowSize.y - head.getShape().getSize().y);
                break;
            case Direction::DOWN:
                newPosition = Vector2f(head.getShape().getPosition().x, 0 + head.getShape().getSize().y);
                break;
            case Direction::LEFT:
                newPosition = Vector2f(windowSize.x - head.getShape().getSize().x, head.getShape().getPosition().y);
                break;
            case Direction::RIGHT:
                newPosition = Vector2f(0 + head.getShape().getSize().x, head.getShape().getPosition().y);
                break;
        }

        // On place la tete a la nouvelle position
        head.getShape().setPosition(newPosition);

        // Mettre a jour les autres parties du serpent
        Vector2f lastSectionPosition = newPosition;
        for (int s = 1; s < snake.size(); ++s) {
            Vector2f thisSectionPosition = snake[s].getPosition();
            snake[s].setPosition(lastSectionPosition);
            lastSectionPosition = thisSectionPosition;
        }

        //Pour s assurer que le serpent continue de bouger
        switch (snakeDirection) {
            case Direction::UP:
                head.setPosition(Vector2f(newPosition.x, newPosition.y - 20));
                break;
            case Direction::DOWN:
                head.setPosition(Vector2f(newPosition.x, newPosition.y + 20));
                break;
            case Direction::LEFT:
                head.setPosition(Vector2f(newPosition.x - 20, newPosition.y));
                break;
            case Direction::RIGHT:
                head.setPosition(Vector2f(newPosition.x + 20, newPosition.y));
                break;
        }

        break; //Pour quitter la boucle
    }
}


      //Apres chaque mise a jour le temps doit etre mis a zero
      timeSinceLastMove=Time::Zero;
	}//End if
}
