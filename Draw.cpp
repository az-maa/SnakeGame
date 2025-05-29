#include"Engine.hpp"
sf::Color windowColor(214, 139, 206);  // Pinkish Lavender (#D68BCE)
void Engine::Draw()
{
	window.clear(windowColor);
	//Dessiner les murs
	for(auto & w: wallSections)
	{
		window.draw(w.getShape());
	}

	//Dessiner le fruit
	window.draw(fruit.getApple());
	//Pour dessiner le serpent
	for(auto & s: snake)//La boucle for itere sur chaque element s dans snake(le conteneur)
	{
		window.draw(s.getShape());

	}
	//Dessiner les obstacles
    window.draw(obstacle1.getShape());
	window.draw(obstacle2.getShape());
	//Dessiner le text
	window.draw(titleText);
	window.draw(currentLevelText);
	window.draw(scoreText);
	//Dessiner le score
	window.draw(applesEatenText);


	//Dessine Game Over
	if(currentGameState==GameState::GAMEOVER)
	{
		window.draw(gameOverText);
		window.draw(pressEnterText);
		window.draw(bestScore1);
		window.draw(bestScore2);
		window.draw(bestScore3);
		window.draw(bestScore4);
		window.draw(bestScore5);
	}
	window.display();

}