#ifndef ENGINE_HPP
#define ENGINE_HPP
#include"SnakeSection.hpp"
#include"Apple.hpp"
#include"Wall.hpp"
#include"Obstacle.hpp"
#include<SFML/System/Time.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/Graphics/RectangleShape.hpp>
#include<ctime>
#include<cstdlib>
#include<vector>
//On va utiliser un vecteur pour contenir les rectangles(the snake)comme on ne sait pas quel sera la longueur final et celle ci varie
#include<deque>
//Pour pouvoir manipuler si on tape plusieurs touches a la fois pour bouger le serpant celle ci va les organier dans une file puis on pourra utiliser la tete comme la queu
#include<fstream>
#include<algorithm>
#include<iostream>
#include<functional>
using namespace sf;
using namespace std;
	class Engine
	{
	private:
		//Window
		Vector2f resolution;//La resolution de la fenetre
		RenderWindow window;//La fenetre
		const unsigned int FPS=60;
		static const Time TimePerFrame;
		vector<SnakeSection> snake;


		int snakeDirection;	
		int speed;
		int sectionsToAdd;//Combien faut il ajouter au serpent
		int currentGameState;
		int lastGameState;//On va pauser le jeu donc il nous faut une variable qui va stocker la valeur de l etat du jeu avant la pause
		unsigned long long int score;
		Time timeSinceLastMove;
		deque<int> directionQueue;

		Apple fruit;
		vector<Wall> wallSections;
		int currentLevel;
		int maxLevels;
		int applesEatenThisLevel;
		int applesEatenTotal;
		vector<int>scores;//Pour stocker les 5 top scores
		vector<String> levels;
		Obstacle obstacle1;//Le premier obstacle
		Obstacle obstacle2;//Le deuxieme obstacle
		Font mainFont;
		Text titleText;
		Text applesEatenText;
		Text currentLevelText;
		Text scoreText;
		Text gameOverText;
		Text pressEnterText;
		Text bestScore1;
		Text bestScore2;
		Text bestScore3;
		Text bestScore4;
		Text bestScore5;
	

	public:

	Engine();

	enum Direction{UP,RIGHT,DOWN,LEFT};//Pour fasciliter les directions
	enum GameState{RUNNING,PAUSED,GAMEOVER};//Pour fasiciliter les etats du jeu
	void input();//Pour gerere tous ce qui est mouvement par clavier
	void addDirection(int newDirection);//Stocker les directions que doit prendre le serpent
	void Draw();//Dessiner sur la fenetre
	void newSnake();//AJouter le serpent
	void addSnakeSection();//Pour agrandir le serpent
	void update();//POur effectuer les mise a jour
	void run();//La fonction qui va executer les autres
	void Pause();//POur gerer quand on pause le jeu
	void moveApple();//Generer des positions aleatoires pour le fruit
	void checkLevelFiles();//S assuerer du contenu d level.txt
	void loadLevel(int);//Charger le niveau
	void addObstacle();//AJouter des obstacles dans des positions aleatoires
	void startGame();//Commencer le jeu la premiere fois puis a chaque fois qu on a perdu
	static void setupText(Text *textItem,const Font &font,const string &value,int size,Color color);
    };




#endif