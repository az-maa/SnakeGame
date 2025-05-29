#include"Engine.hpp"
sf::Color scoreColor(255, 45, 149);    // Hot Pink (#FF2D95)
sf::Color gameOverColor(255, 215, 0);  // Bright Yellow (#FFD700)
sf::Color bestScoreColor(184, 156, 255); // Lilac Purple (#B89CFF)
sf::Color enterTextColor(255, 182, 193); // Light Pink (#FFB6C1)


Engine :: Engine()
{
	resolution = Vector2f(800,600);
	window.create(VideoMode(resolution.x,resolution.y),"Jeu de Serpent",Style::Resize|Style::Close);
    window.setFramerateLimit(FPS);
    maxLevels=0;
    scores={0,0,0,0,0};
    checkLevelFiles();
    startGame();
    mainFont.loadFromFile("font.ttf");
    setupText(&titleText,mainFont,"Jeu de Serpent",28,scoreColor);
    FloatRect titleTextBounds=titleText.getLocalBounds();//Pour pouvoir centrer le text au milieu
    titleText.setPosition(Vector2f(resolution.x/2-titleTextBounds.width/2,-9));
    FloatRect currentLevelTextBounds=currentLevelText.getGlobalBounds();
    setupText(&applesEatenText,mainFont,"Apple : 0",28,scoreColor);
    applesEatenText.setPosition(
    	Vector2f(currentLevelTextBounds.left+currentLevelTextBounds.width+20,-9));
    setupText(&scoreText,mainFont,"Score",28,scoreColor);
    FloatRect scoreTextBounds=scoreText.getLocalBounds();
    scoreText.setPosition(Vector2f(resolution.x-scoreTextBounds.width-50,-9));
    setupText(&gameOverText,mainFont,"GAME OVER",80,gameOverColor);
    FloatRect gameOverTextBounds=gameOverText.getLocalBounds();
    gameOverText.setPosition(Vector2f(resolution.x/2-gameOverTextBounds.width/2,100));
    gameOverText.setOutlineColor(Color::Black);
    gameOverText.setOutlineThickness(2);

    setupText(&pressEnterText,mainFont,"Press ENTER to try Again",40,enterTextColor);

    
    FloatRect pressEnterTextBounds=pressEnterText.getLocalBounds();
    pressEnterText.setPosition(Vector2f(resolution.x/2-pressEnterTextBounds.width/2,200));
    pressEnterText.setOutlineColor(Color::Black);
    pressEnterText.setOutlineThickness(2);


    setupText(&bestScore1,mainFont,"Player 1 ",30,bestScoreColor);
    FloatRect bestScore1Bounds=bestScore1.getLocalBounds();
    bestScore1.setPosition(Vector2f(resolution.x/2-bestScore1Bounds.width/2,300));
    bestScore1.setOutlineColor(Color::Black);
    bestScore1.setOutlineThickness(2);

    setupText(&bestScore2,mainFont,"Player 2",30,bestScoreColor);
    FloatRect bestScore2Bounds=bestScore2.getLocalBounds();
    bestScore2.setPosition(Vector2f(resolution.x/2-bestScore2Bounds.width/2,350));
    bestScore2.setOutlineColor(Color::Black);
    bestScore2.setOutlineThickness(2);

    setupText(&bestScore3,mainFont,"Player 3",30,bestScoreColor);
    FloatRect bestScore3Bounds=bestScore3.getLocalBounds();
    bestScore3.setPosition(Vector2f(resolution.x/2-bestScore3Bounds.width/2,400));
    bestScore3.setOutlineColor(Color::Black);
    bestScore3.setOutlineThickness(2);

    setupText(&bestScore4,mainFont,"Player 4",30,bestScoreColor);
    FloatRect bestScore4Bounds=bestScore4.getLocalBounds();
    bestScore4.setPosition(Vector2f(resolution.x/2-bestScore4Bounds.width/2,450));
    bestScore4.setOutlineColor(Color::Black);
    bestScore4.setOutlineThickness(2);

    setupText(&bestScore5,mainFont,"Player 5",30,bestScoreColor);
    FloatRect bestScore5Bounds=bestScore5.getLocalBounds();
    bestScore5.setPosition(Vector2f(resolution.x/2-bestScore5Bounds.width/2,500));
    bestScore5.setOutlineColor(Color::Black);
    bestScore5.setOutlineThickness(2);


    
}
//On definie la methode qui va creer le premier serpent
void Engine::newSnake()
{
snake.clear();//si jamais il y avait un autre serpent auparavent il sera effece
snake.emplace_back(Vector2f(100,100));
snake.emplace_back(Vector2f(80,100));
snake.emplace_back(Vector2f(60,100));
}
void Engine::addSnakeSection()
{
	//Pour ajouter une partie au serpant
	Vector2f newSectionPosition=snake[snake.size()-1].getPosition();//la position de la nouvelle section a ajouter est la postion de la derniere section -1 (les indices commencent par 0)
    snake.emplace_back(newSectionPosition);
}
void Engine::moveApple()
{
	//Trouve ou placer notre fruit
	//Il ne faut pas que notre fruit soit dans un mur ou a l interieur de notre serpant
	//On divise notre fenetre en sections
	Vector2f appleResolution = Vector2f(resolution.x/20-2,resolution.y/20-2);
	Vector2f newAppleLocation;
	bool badLocation=false;
	do
	{
		badLocation=false;
		newAppleLocation.x=(float)(rand()%(int)appleResolution.x)*20;
		newAppleLocation.y=(float)(rand()%(int)appleResolution.y)*20;
		//S assurer que la position generer ne coincide pas avec celle du serpent
		 for(auto &s :snake)
		 {
		 	if(s.getShape().getGlobalBounds()
		 		.intersects(Rect<float>(newAppleLocation.x,newAppleLocation.y,20,20)))
		 	{
		 		badLocation=true;
		 		break;
		 	}
		 }
		 //Faire le teste sur la position avec les murs
		 for(auto &w : wallSections)
		 {
		 	if(w.getShape().getGlobalBounds()
		 		.intersects(Rect<float>(newAppleLocation.x,newAppleLocation.y,20,20)))
		 	{
		 		badLocation=true;
		 		break;
		 	}
		 }
		 //IL ne faut pas qur la position genere de la pomme soit identique a celle des obstacles
		 	 if(obstacle1.getShape().getGlobalBounds().intersects((Rect<float>(newAppleLocation.x,newAppleLocation.y,20,20))))
		 {
		 	badLocation=true;
		 	break;
		 }
		 	if(obstacle2.getShape().getGlobalBounds().intersects((Rect<float>(newAppleLocation.x,newAppleLocation.y,20,20))))
		 {
		 	badLocation=true;
		 	break;
		 }
		 }

	while(badLocation);
	fruit.setPosition(newAppleLocation);

}
void Engine::addObstacle()
{

	Vector2f o1Resolution = Vector2f(resolution.x/20-2,resolution.y/20-2);
	Vector2f newo1Location;
	bool badLocation=false;
	do
	{
		badLocation=false;
		newo1Location.x=(float)(rand()%(int)o1Resolution.x)*20;
		newo1Location.y=(float)(rand()%(int)o1Resolution.y)*20;
		//S assurer que la position generer ne coincide pas avec celle du serpent
		 for(auto &s :snake)
		 {
		 	if(s.getShape().getGlobalBounds()
		 		.intersects(Rect<float>(newo1Location.x,newo1Location.y,20,20)))
		 	{
		 		badLocation=true;
		 		break;
		 	}
		 }
		 //Faire le teste sur la position avec les murs
		 for(auto &w : wallSections)
		 {
		 	if(w.getShape().getGlobalBounds()
		 		.intersects(Rect<float>(newo1Location.x,newo1Location.y,20,20)))
		 	{
		 		badLocation=true;
		 		break;
		 	}
		 }
		 //S assurer que la position de l obstacle ne coincide pas avec celle du fruit
		 if(fruit.getApple().getGlobalBounds().intersects((Rect<float>(newo1Location.x,newo1Location.y,20,20))))
		 {
		 	badLocation=true;
		 	break;
		 }
		 if(obstacle2.getShape().getGlobalBounds().intersects((Rect<float>(newo1Location.x,newo1Location.y,20,20))))
		 {
		 	badLocation=true;
		 	break;
		 }

	}while(badLocation);
	obstacle1.setPosition(newo1Location);
	//ON fait la meme chose pour le deuxieme obstacle
	Vector2f o2Resolution = Vector2f(resolution.x/20-2,resolution.y/20-2);
	Vector2f newo2Location;
	bool badLocation2=false;
	do
	{
		badLocation2=false;
		newo2Location.x=(float)(rand()%(int)o2Resolution.x)*20;
		newo2Location.y=(float)(rand()%(int)o2Resolution.y)*20;
		//S assurer que la position generer ne coincide pas avec celle du serpant
		 for(auto &s :snake)
		 {
		 	if(s.getShape().getGlobalBounds()
		 		.intersects(Rect<float>(newo2Location.x,newo2Location.y,20,20)))
		 	{
		 		badLocation2=true;
		 		break;
		 	}
		 }
		 //Faire le teste sur la position avec les murs
		 for(auto &w : wallSections)
		 {
		 	if(w.getShape().getGlobalBounds()
		 		.intersects(Rect<float>(newo2Location.x,newo2Location.y,20,20)))
		 	{
		 		badLocation2=true;
		 		break;
		 	}
		 }
		 //S assurer que la position de l obstacle ne coincide pas avec celle du fruit
		 if(fruit.getApple().getGlobalBounds().intersects((Rect<float>(newo2Location.x,newo2Location.y,20,20))))
		 {
		 	badLocation2=true;
		 	break;
		 }
		 //POur que les deux obstacles ne possede pas la meme position
		 if(obstacle1.getShape().getGlobalBounds().intersects((Rect<float>(newo2Location.x,newo2Location.y,20,20))))
		 {
		 	badLocation2=true;
		 	break;
		 }
		 if (obstacle1.getShape().getGlobalBounds().intersects(obstacle2.getShape().getGlobalBounds())) {
         badLocation2 = true;
         }



	}while(badLocation2);
	obstacle2.setPosition(newo2Location);

}
void Engine::Pause()
{
	if(currentGameState==GameState::RUNNING)
	{
		lastGameState=currentGameState;
		currentGameState=GameState::PAUSED;
	}
	else if(currentGameState==GameState::PAUSED)
	{
		currentGameState=lastGameState;
	}
}
void Engine::startGame()
{

	score=0;
	speed=2;
    snakeDirection = Direction::RIGHT;
    timeSinceLastMove=Time::Zero;
    sectionsToAdd=0;
    directionQueue.clear();
    currentLevel=1;//A chaque fois qu on commence le jeux il sera au niveau 1
    applesEatenThisLevel=0;
    applesEatenTotal=0;
    loadLevel(currentLevel);
    srand(time(NULL));
    newSnake();
    addObstacle();
    moveApple();
    currentGameState=GameState::RUNNING;
    lastGameState=currentGameState;

 
    FloatRect currentLevelTextBounds=currentLevelText.getGlobalBounds();
    setupText(&applesEatenText,mainFont,"Apple  :"+to_string(applesEatenThisLevel),28,scoreColor);
    applesEatenText.setPosition(
    	Vector2f(currentLevelTextBounds.left+currentLevelTextBounds.width+20,-9));
    scoreText.setString("Score :"+to_string(score));
    FloatRect scoreTextBounds=scoreText.getLocalBounds();
    scoreText.setPosition(Vector2f(resolution.x-scoreTextBounds.width-50,-9));


}
void Engine::checkLevelFiles()
{
    // Charger le fichier levels.txt
    ifstream levelsManifest("levels.txt");
    if (!levelsManifest.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir levels.txt !" << std::endl;
        return;  // Si levels.txt ne peut pas etre ouvert on quitte la fonction.
    }

    ifstream testFile;
    for (string manifestLine; getline(levelsManifest, manifestLine);)
    {
        // S assurer qu on peut ouvrir le fichier correspondant au niveau
        testFile.open(manifestLine);
        if (testFile.is_open())
        {
            // Le fichier est ouvert on l ajoute a la liste des niveaux
            levels.emplace_back(manifestLine);
            testFile.close();
            maxLevels++;
        }
        else {
            std::cerr << "Erreur: Impossible d'ouvrir " <<  manifestLine << std::endl;
        }
    }
}

void Engine::loadLevel(int levelNumber)
{
    // Charger le mur depuis un fichier texte en identifiant les "X"
    string levelFile = levels[levelNumber - 1];  // Recuperer le chemin du fichier du niveau
    ifstream level(levelFile);
    string line;

    if (level.is_open())
    {
        // Lire chaque ligne du fichier de niveau
        for (int y = 0; y < 30; y++)
        {
            if (!getline(level, line)) {
                std::cerr << "Erreur: Fin de fichier inattendue en lisant le niveau." << std::endl;
                break;  // Quitter si on ne peut pas lire suffisamment de lignes
            }
            
            // Verifier chaque caracteree de la ligne
            for (int x = 0; x < 40; x++)
            {
                // Si le caractere est 'x' on place un mur
                if (x < line.length() && line[x] == 'x')
                {
                    wallSections.emplace_back(Wall(Vector2f(x * 20, y * 20), Vector2f(20, 20)));
                }
            }
        }
    }
    else {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier de niveau : " << levelFile << std::endl;
    }

    level.close();
}


void Engine::setupText(Text *textItem,const Font &font,const string &value,int size,Color color)
{
	textItem->setFont(font);
	textItem->setString(value);
	textItem->setCharacterSize(size);
	textItem->setFillColor(color);
}

void Engine::run()
{
	Clock clock;

	//Boucle de jeu
	while(window.isOpen())
	{

        Time dt= clock.restart();
        if(currentGameState==GameState::PAUSED||currentGameState==GameState::GAMEOVER)
        {
        	//Si on s est arrete on va attendre que le jouer clique une touche pour continue le jeux
        	input();
        	//Pour afficher le Game Over Screen
        	if(currentGameState==GameState::GAMEOVER)
        	{
              //On stocke les 5 meilleures scores depuis le 1er essaie dans un vecteur (seul une valeur plus grande que celle que la plus garnge deja dans le vecteur sera ajoute comme ca on va avoir 5 les meilleures )
        	if (score > scores.front())  //check si la tete est inferieur a la nouvelle valeur ajoute
            {
            	if(scores.size()>5)//on ne doit avoir que 5 scores
            	{
            		scores.resize(5);
            	}
            	scores.back() = score;
            	sort(scores.begin(), scores.end(),greater<int>());
            }
        
                
                

            
    bestScore1.setString("Player 1 : "+to_string(scores[0]));
    bestScore2.setString("Player 2 : "+to_string(scores[1]));
    bestScore3.setString("Player 3 : "+to_string(scores[2]));
    bestScore4.setString("Player 4 : "+to_string(scores[3]));
    bestScore5.setString("Player 5 : "+to_string(scores[4]));

    FloatRect bestScore1Bounds=bestScore1.getLocalBounds();
    bestScore1.setPosition(Vector2f(resolution.x/2-bestScore1Bounds.width/2,300));
    bestScore1.setOutlineColor(Color::Black);
    bestScore1.setOutlineThickness(2);

    
    FloatRect bestScore2Bounds=bestScore2.getLocalBounds();
    bestScore2.setPosition(Vector2f(resolution.x/2-bestScore2Bounds.width/2,350));
    bestScore2.setOutlineColor(Color::Black);
    bestScore2.setOutlineThickness(2);

    
    FloatRect bestScore3Bounds=bestScore3.getLocalBounds();
    bestScore3.setPosition(Vector2f(resolution.x/2-bestScore3Bounds.width/2,400));
    bestScore3.setOutlineColor(Color::Black);
    bestScore3.setOutlineThickness(2);

    
    FloatRect bestScore4Bounds=bestScore4.getLocalBounds();
    bestScore4.setPosition(Vector2f(resolution.x/2-bestScore4Bounds.width/2,450));
    bestScore4.setOutlineColor(Color::Black);
    bestScore4.setOutlineThickness(2);

    
    FloatRect bestScore5Bounds=bestScore5.getLocalBounds();
    bestScore5.setPosition(Vector2f(resolution.x/2-bestScore5Bounds.width/2,500));
    bestScore5.setOutlineColor(Color::Black);
    bestScore5.setOutlineThickness(2);



        		Draw();
                 
        	    }
                 
            sleep(milliseconds(2));
        	continue;
                 
        	}
        	
               
      timeSinceLastMove+=dt;
        input();
        update();
		Draw();

        }


        
	}
	

