#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
class Game
{
private:

	int width, height, fps, rcellsize;
	const char* title;
	int cellsize = 8;
	int columns = 10;
	int rows = 20;
	int resize = 8;
	int shape;
	int rotatenum = 0;
	int rowcheck = 0;
	int linenum = 0;
	int count;
	int del_count;
	vector<int> rownum;
	vector<int> shape1;
	vector<int> shape2;
	vector<int> shape3;
	vector<int> shape4;
	vector<int> shape5;
	vector<int> shape6;
	vector<int> shape7;

	bool collision = false;
	bool ground = false;
	bool filled = false;

	sf::RenderWindow* window;
	sf::Event ev;
	sf::RectangleShape block[219];
	sf::RectangleShape minos[4];
	sf::Clock timer;

	sf::Vector2f position0;
	sf::Vector2f position1;
	sf::Vector2f position2;
	sf::Vector2f position3;



	void initWindow();
	void initBlocks();
	void initminos();
	void position();
	void blockdel(int blockcoord);

public:
	Game();
	~Game();
	bool running = false;
	void reset();
	void updateCollision();
	void rotation();
	void updateBlock();
	void updateMinos();
	void pollEvents();
	void update();
	void render();

};

