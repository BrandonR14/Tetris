#include "Game.h"
#include <vector>
#include <random>


Game::Game()
{
	width = cellsize * columns * resize;
	height = cellsize * rows * resize;
	rcellsize = cellsize * resize;
	fps = 144;
	title = "Tetris";
	

	initWindow();
	initminos();
}

Game::~Game()
{
	delete window;
}

void Game::initWindow()
{

	window = new sf::RenderWindow(sf::VideoMode(width ,height), title);
	window->setFramerateLimit(fps);
	running = true;
}

void Game::initBlocks()
{
	int xcounter = 0;
	int ycounter = 0;
	for (int i = 0; i < 219; i++)
	{
		block[i].setSize(sf::Vector2f(resize * cellsize - 1, resize * cellsize - 1));
		block[i].setFillColor(sf::Color::White);
		block[i].setPosition(sf::Vector2f(resize * cellsize * xcounter, resize * cellsize * ycounter));
		window->draw(block[i]);
		xcounter++;
		if (xcounter == 11)
		{
			xcounter = 0;
			ycounter++;
		}
		if (filled == true)
		{
			for (int j = 0; j < shape1.size(); j++)
			{
				if (i == shape1[j])
				{
					block[i].setFillColor(sf::Color::Yellow);
					window->draw(block[i]);
				}
			}
			for (int j = 0; j < shape2.size(); j++)
			{
				if (i == shape2[j])
				{
					block[i].setFillColor(sf::Color::Cyan);
					window->draw(block[i]);
				}
			}
			for (int j = 0; j < shape3.size(); j++)
			{
				if (i == shape3[j])
				{
					block[i].setFillColor(sf::Color::Magenta);
					window->draw(block[i]);
				}
			}
			for (int j = 0; j < shape4.size(); j++)
			{
				if (i == shape4[j])
				{
					block[i].setFillColor(sf::Color::Red);
					window->draw(block[i]);
				}
			}
			for (int j = 0; j < shape5.size(); j++)
			{
				if (i == shape5[j])
				{
					block[i].setFillColor(sf::Color::Green);
					window->draw(block[i]);
				}
			}
			for (int j = 0; j < shape6.size(); j++)
			{
				if (i == shape6[j])
				{
					block[i].setFillColor(sf::Color::Blue);
					window->draw(block[i]);
				}
			}				
			for (int j = 0; j < shape7.size(); j++)
			{
				if (i == shape7[j])
				{
					block[i].setFillColor(sf::Color::Black);
					window->draw(block[i]);
				}
			}
			
			
			if (xcounter == 0)
			{
				rowcheck = 0;
			}
			if (block[i].getFillColor() != sf::Color::White)
			{
				sf::Vector2f blockpos = block[i].getPosition();
				rowcheck++;
				sf::FloatRect blockBounds = block[i].getGlobalBounds();
				sf::FloatRect minoBounds0 = minos[0].getGlobalBounds();
				sf::FloatRect minoBounds1 = minos[1].getGlobalBounds();
				sf::FloatRect minoBounds2 = minos[2].getGlobalBounds();
				sf::FloatRect minoBounds3 = minos[3].getGlobalBounds();
				if (blockBounds.top == minoBounds0.top + (64) && blockBounds.left == minoBounds0.left)
				{
					ground = true;
					reset();
				}
				else if (blockBounds.top == minoBounds1.top + (64) && blockBounds.left == minoBounds1.left)
				{
					ground = true;
					reset();
				}
				else if (blockBounds.top == minoBounds2.top + (64) && blockBounds.left == minoBounds2.left)
				{
					ground = true;
					reset();
				}
				else if (blockBounds.top == minoBounds3.top + (64) && blockBounds.left == minoBounds3.left)
				{
					ground = true;
					reset();
				}
				if (ground == true)
				{
					if (rowcheck == 10)
					{
						for (int y = 0; y < 11; y++)
						{
							rownum.push_back(i - y);
						}
						for (int j = 0; j < rownum.size(); j++)
						{
							linenum++;
							if (i == rownum[j])
							{
								block[i].setFillColor(sf::Color::White);
								window->draw(block[i]);
							}
						}
						if (linenum == rownum.size())
						{
							del_count = 0;
							for (int j = rownum[0]; j > 10; j--)
							{
								rownum.clear();
								//block[j].setFillColor(block[j - 11].getFillColor());
								blockdel(j);
								//window->draw(block[j]);
								del_count++;
							}
							linenum = 0;
						}
						rowcheck = 0;
					}
				}
				if (blockpos.y == 0)
				{
					for (int l = 0; l < 219; l++)
					{
						block[l].setFillColor(sf::Color::White);
					}
					shape1.clear();
					shape2.clear();
					shape3.clear();
					shape4.clear();
					shape5.clear();
					shape6.clear();
					shape7.clear();
				}
			}
		}
	}
}
void Game::position()
{
	position0 = minos[0].getPosition();
	position1 = minos[1].getPosition();
	position2 = minos[2].getPosition();
	position3 = minos[3].getPosition();
}
void Game::blockdel(int blockcoord)
{
	int pos;
	int num;
	if (std::count(shape1.begin(), shape1.end(), blockcoord))
	{
		for (int l = 219; l > 209; l--)
		{
			if (l == blockcoord)
			{
				auto del_pos = find(shape1.begin(), shape1.end(), l);
				int index = del_pos - shape1.begin();
				shape1.erase(shape1.begin() + index);

			}
		}
		if (del_count < 11)
		{
			auto del_pos = find(shape1.begin(), shape1.end(), blockcoord);
			int index = del_pos - shape1.begin();
			shape1.erase(shape1.begin() + index);
		}
		for (int x = 0; x < shape1.size(); x++)
		{
			if (shape1[x] == blockcoord)
			{
				pos = x;
				num = shape1[x];
				shape1.erase(shape1.begin() + pos);
				shape1.push_back(num + 11);
			}
		}
	}
	else if (std::count(shape2.begin(), shape2.end(), blockcoord))
	{
		for (int l = 219; l > 209; l--)
		{
			if (l == blockcoord)
			{
				auto del_pos = find(shape2.begin(), shape2.end(), l);
				int index = del_pos - shape2.begin();
				shape2.erase(shape2.begin() + index);

			}
		}
		if (del_count < 11)
		{
			auto del_pos = find(shape2.begin(), shape2.end(), blockcoord);
			int index = del_pos - shape2.begin();
			shape2.erase(shape2.begin() + index);
		}
		for (int x = 0; x < shape2.size(); x++)
		{
			if (shape2[x] == blockcoord)
			{
				pos = x;
				num = shape2[x];
				shape2.erase(shape2.begin() + pos);
				shape2.push_back(num + 11);
			}
		}
	}
	else if (std::count(shape3.begin(), shape3.end(), blockcoord))
	{
		for (int l = 219; l > 209; l--)
		{
			if (l == blockcoord)
			{
				auto del_pos = find(shape3.begin(), shape3.end(), l);
				int index = del_pos - shape3.begin();
				shape3.erase(shape3.begin() + index);

			}
		}
		if (del_count < 11)
		{
			auto del_pos = find(shape3.begin(), shape3.end(), blockcoord);
			int index = del_pos - shape3.begin();
			shape3.erase(shape3.begin() + index);
		}
		for (int x = 0; x < shape3.size(); x++)
		{
			if (shape3[x] == blockcoord)
			{
				pos = x;
				num = shape3[x];
				shape3.erase(shape3.begin() + pos);
				shape3.push_back(num + 11);
			}
		}
	}
	else if (std::count(shape4.begin(), shape4.end(), blockcoord))
	{
		for (int l = 219; l > 209; l--)
		{
			if (l == blockcoord)
			{
				auto del_pos = find(shape4.begin(), shape4.end(), l);
				int index = del_pos - shape4.begin();
				shape4.erase(shape4.begin() + index);

			}
		}
		if (del_count < 11)
		{
			auto del_pos = find(shape4.begin(), shape4.end(), blockcoord);
			int index = del_pos - shape4.begin();
			shape4.erase(shape4.begin() + index);
		}
		for (int x = 0; x < shape4.size(); x++)
		{
			if (shape4[x] == blockcoord)
			{
				pos = x;
				num = shape4[x];
				shape4.erase(shape4.begin() + pos);
				shape4.push_back(num + 11);
			}
		}
	}
	else if (std::count(shape5.begin(), shape5.end(), blockcoord))
	{
		for (int l = 219; l > 209; l--)
		{
			if (l == blockcoord)
			{
				auto del_pos = find(shape5.begin(), shape5.end(), l);
				int index = del_pos - shape5.begin();
				shape5.erase(shape5.begin() + index);

			}
		}
		if (del_count < 11)
		{
			auto del_pos = find(shape5.begin(), shape5.end(), blockcoord);
			int index = del_pos - shape5.begin();
			shape5.erase(shape5.begin() + index);
		}
		for (int x = 0; x < shape5.size(); x++)
		{
			if (shape5[x] == blockcoord)
			{
				pos = x;
				num = shape5[x];
				shape5.erase(shape5.begin() + pos);
				shape5.push_back(num + 11);
			}
		}
	}
	else if (std::count(shape6.begin(), shape6.end(), blockcoord))
	{
		for (int l = 219; l > 209; l--)
		{
			if (l == blockcoord)
			{
				auto del_pos = find(shape6.begin(), shape6.end(), l);
				int index = del_pos - shape6.begin();
				shape6.erase(shape6.begin() + index);

			}
		}
		if (del_count < 11)
		{
			auto del_pos = find(shape1.begin(), shape6.end(), blockcoord);
			int index = del_pos - shape6.begin();
			shape6.erase(shape6.begin() + index);
		}
		for (int x = 0; x < shape6.size(); x++)
		{
			if (shape6[x] == blockcoord)
			{
				pos = x;
				num = shape6[x];
				shape6.erase(shape6.begin() + pos);
				shape6.push_back(num + 11);
			}
		}
	}
	else if (std::count(shape7.begin(), shape7.end(), blockcoord))
	{
		for (int l = 219; l > 209; l--)
		{
			if (l == blockcoord)
			{
				auto del_pos = find(shape7.begin(), shape7.end(), l);
				int index = del_pos - shape7.begin();
				shape7.erase(shape7.begin() + index);

			}
		}
		if (del_count < 11)
		{
			auto del_pos = find(shape7.begin(), shape7.end(), blockcoord);
			int index = del_pos - shape7.begin();
			shape7.erase(shape7.begin() + index);
		}
		for (int x = 0; x < shape7.size(); x++)
		{
			if (shape7[x] == blockcoord)
			{
				pos = x;
				num = shape7[x];
				shape7.erase(shape7.begin() + pos);
				shape7.push_back(num + 11);
			}
		}
	}
}

void Game::updateBlock()
{
	if (ground == true )
	{
		for (int i = 0; i < 219; i++)
		{
			if(block[i].getPosition() == minos[0].getPosition() || block[i].getPosition() == minos[1].getPosition() || block[i].getPosition() == minos[2].getPosition() || block[i].getPosition() == minos[3].getPosition())
			{
				if (shape == 1)
				{
					shape1.push_back(i);
				}
				else if (shape == 2)
				{
					shape2.push_back(i);
				}
				else if (shape == 3)
				{
					shape3.push_back(i);
				}
				else if (shape == 4)
				{
					shape4.push_back(i);
				}
				else if (shape == 5)
				{
					shape5.push_back(i);
				}
				else if (shape == 6)
				{
					shape6.push_back(i);
				}
				else if (shape == 7)
				{
					shape7.push_back(i);
				}
			}
			
		}
		filled = true;
	}
}

void Game::initminos()
{
	count++;
	random_device rand;
	mt19937 gen(rand());
	uniform_int_distribution<>dis(1, 7);
	shape = dis(gen);
	rotatenum = 0;
	for (int i = 0; i < 4; i++)
	{
		minos[i].setSize(sf::Vector2f(resize * cellsize - 1, resize * cellsize - 1));
		if (shape == 1)
		{
			minos[i].setFillColor(sf::Color::Yellow);
		}
		if (shape == 2)
		{
			minos[i].setFillColor(sf::Color::Cyan);
		}
		if (shape == 3)
		{
			minos[i].setFillColor(sf::Color::Magenta);
		}
		if (shape == 4)
		{
			minos[i].setFillColor(sf::Color::Red);
		}
		if (shape == 5)
		{
			minos[i].setFillColor(sf::Color::Green);
		}
		if (shape == 6)
		{
			minos[i].setFillColor(sf::Color::Blue);
		}
		if (shape == 7)
		{
			minos[i].setFillColor(sf::Color::Black);
		}
		
	}
	
	if (shape == 1)
	{
		minos[0].setPosition(sf::Vector2f(width / 2 - 64, 0));
		minos[1].setPosition(sf::Vector2f(width / 2, 0));
		minos[2].setPosition(sf::Vector2f(width / 2 - 64, 64));
		minos[3].setPosition(sf::Vector2f(width / 2, 64));
	}
	else if (shape == 2)
	{
		minos[0].setPosition(sf::Vector2f(width / 2 - (64*2), 0));
		minos[1].setPosition(sf::Vector2f(width / 2 - 64, 0));
		minos[2].setPosition(sf::Vector2f(width / 2, 0));
		minos[3].setPosition(sf::Vector2f(width / 2 + 64, 0));
	}
	else if (shape == 3)
	{
		minos[0].setPosition(sf::Vector2f(width / 2 - 64, 0));
		minos[1].setPosition(sf::Vector2f(width / 2 - (64*2), 64));
		minos[2].setPosition(sf::Vector2f(width / 2 - 64, 64));
		minos[3].setPosition(sf::Vector2f(width / 2, 64));
	}
	else if (shape == 4)
	{
		minos[0].setPosition(sf::Vector2f(width / 2 - 64, 0));
		minos[1].setPosition(sf::Vector2f(width / 2, 0));
		minos[2].setPosition(sf::Vector2f(width / 2 - 64, 64));
		minos[3].setPosition(sf::Vector2f(width / 2 - (64*2), 64));
	}
	else if (shape == 5)
	{
		minos[0].setPosition(sf::Vector2f(width / 2 - 64, 0));
		minos[1].setPosition(sf::Vector2f(width / 2, 0));
		minos[2].setPosition(sf::Vector2f(width / 2, 64));
		minos[3].setPosition(sf::Vector2f(width / 2 + 64, 64));
	}
	else if (shape == 6) 
	{
		minos[0].setPosition(sf::Vector2f(width / 2 - (64*2), 0));
		minos[1].setPosition(sf::Vector2f(width / 2-(64*2), 64));
		minos[2].setPosition(sf::Vector2f(width / 2 - 64, 64));
		minos[3].setPosition(sf::Vector2f(width / 2, 64));
	}
	else if (shape == 7)
	{
		minos[0].setPosition(sf::Vector2f(width / 2, 0));
		minos[1].setPosition(sf::Vector2f(width / 2, 64));
		minos[2].setPosition(sf::Vector2f(width / 2 - 64, 64));
		minos[3].setPosition(sf::Vector2f(width / 2 - (2*64), 64));
	}
}

void Game::updateMinos()
{
		if (timer.getElapsedTime().asSeconds() >= 0.5)
		{
			position();
			position0.y += rcellsize;
			position1.y += rcellsize;
			position2.y += rcellsize;
			position3.y += rcellsize;
			minos[0].setPosition(position0.x, position0.y);
			minos[1].setPosition(position1.x, position1.y);
			minos[2].setPosition(position2.x, position2.y);
			minos[3].setPosition(position3.x, position3.y);
			timer.restart();
		}
}

void Game::updateCollision()
{
	sf::FloatRect minoBounds0 = minos[0].getGlobalBounds();
	sf::FloatRect minoBounds1 = minos[1].getGlobalBounds();
	sf::FloatRect minoBounds2 = minos[2].getGlobalBounds();
	sf::FloatRect minoBounds3 = minos[3].getGlobalBounds();
	if (minoBounds0.left <= - rcellsize)
	{
		collision = true;
	}
	else if (minoBounds0.top + minoBounds0.height >= height - rcellsize)
	{
		ground = true;
	}
	else if (minoBounds0.left + minoBounds0.width >= width)
	{
		collision = true;
	}

	if (minoBounds1.left <= - rcellsize)
	{
		collision = true;
	}
	else if (minoBounds1.top + minoBounds1.height >= height - rcellsize)
	{
		ground = true;
	}
	else if (minoBounds1.left + minoBounds1.width >= width)
	{
		collision = true;
	}

	if (minoBounds2.left <= - rcellsize)
	{
		collision = true;
	}
	else if (minoBounds2.top + minoBounds2.height >= height - rcellsize)
	{
		ground = true;
	}
	else if (minoBounds2.left + minoBounds2.width >= width)
	{
		collision = true;
	}

	if (minoBounds3.left <= - rcellsize)
	{
		collision = true;
	}
	else if (minoBounds3.top + minoBounds3.height >= height - rcellsize)
	{
		ground = true;
		
	}
	else if (minoBounds3.left + minoBounds3.width >= width)
	{
		collision = true;
	}

	if (collision == true)
	{
		minos[0].setPosition(sf::Vector2f(position0.x, position0.y));
		minos[1].setPosition(sf::Vector2f(position1.x, position1.y));
		minos[2].setPosition(sf::Vector2f(position2.x, position2.y));
		minos[3].setPosition(sf::Vector2f(position3.x, position3.y));
		collision = false;
	}
}

void Game::rotation()
{ 
	position();
	if (rotatenum == 4)
	{
		rotatenum = 0;
	}
	if (shape == 2)
	{
		if (rotatenum == 0)
		{
			minos[0].setPosition(position0.x + (2 * rcellsize), position0.y - rcellsize);
			minos[1].setPosition(position1.x + rcellsize, position1.y);
			minos[2].setPosition(position2.x, position2.y + rcellsize);
			minos[3].setPosition(position3.x - rcellsize, position3.y + (2*rcellsize));
		}
		else if (rotatenum == 1)
		{
			minos[0].setPosition(position0.x + rcellsize, position0.y + (2*rcellsize));
			minos[1].setPosition(position1.x, position1.y + rcellsize);
			minos[2].setPosition(position2.x - rcellsize, position2.y);
			minos[3].setPosition(position3.x - (2*rcellsize), position3.y - rcellsize);
		}
		else if (rotatenum == 2)
		{
			minos[0].setPosition(position0.x - (2 * rcellsize), position0.y + rcellsize);
			minos[1].setPosition(position1.x - rcellsize, position1.y);
			minos[2].setPosition(position2.x, position2.y - rcellsize);
			minos[3].setPosition(position3.x + rcellsize, position3.y - (2 * rcellsize));
		}
		else if (rotatenum == 3)
		{
			minos[0].setPosition(position0.x - rcellsize, position0.y - (2*rcellsize));
			minos[1].setPosition(position1.x, position1.y - rcellsize);
			minos[2].setPosition(position2.x + rcellsize, position2.y );
			minos[3].setPosition(position3.x + (2*rcellsize), position3.y + rcellsize);
		}
		rotatenum++;

	}
	else if (shape == 3)
	{
		if (rotatenum == 0)
		{
			minos[0].setPosition(position0.x + rcellsize, position0.y + rcellsize);
			minos[1].setPosition(position1.x + rcellsize, position1.y - rcellsize);
			minos[3].setPosition(position3.x - rcellsize, position3.y + rcellsize);
		}
		else if (rotatenum == 1)
		{
			minos[0].setPosition(position0.x - rcellsize, position0.y + rcellsize);
			minos[1].setPosition(position1.x + rcellsize, position1.y + rcellsize);
			minos[3].setPosition(position3.x - rcellsize, position3.y - rcellsize);
		}
		else if (rotatenum == 2)
		{
			minos[0].setPosition(position0.x - rcellsize, position0.y - rcellsize);
			minos[1].setPosition(position1.x - rcellsize, position1.y + rcellsize);
			minos[3].setPosition(position3.x + rcellsize, position3.y - rcellsize);
		}
		else if (rotatenum == 3)
		{
			minos[0].setPosition(position0.x + rcellsize, position0.y - rcellsize);
			minos[1].setPosition(position1.x - rcellsize, position1.y - rcellsize);
			minos[3].setPosition(position3.x + rcellsize, position3.y + rcellsize);
		}
		rotatenum++;
	}
	else if (shape == 4)
	{
		if (rotatenum == 0)
		{
			minos[0].setPosition(position0.x + rcellsize, position0.y + rcellsize);
			minos[1].setPosition(position1.x, position1.y + (2*rcellsize));
			minos[3].setPosition(position3.x + rcellsize, position3.y - rcellsize);
		}
		else if (rotatenum == 1)
		{
			minos[0].setPosition(position0.x - rcellsize, position0.y + rcellsize);
			minos[1].setPosition(position1.x - (2*rcellsize), position1.y);
			minos[3].setPosition(position3.x + rcellsize, position3.y + rcellsize);
		}
		else if (rotatenum == 2)
		{
			minos[0].setPosition(position0.x - rcellsize, position0.y - rcellsize);
			minos[1].setPosition(position1.x, position1.y - (2*rcellsize));
			minos[3].setPosition(position3.x - rcellsize, position3.y + rcellsize);
		}
		else if (rotatenum == 3)
		{
			minos[0].setPosition(position0.x + rcellsize, position0.y - rcellsize);
			minos[1].setPosition(position1.x + (2*rcellsize), position1.y);
			minos[3].setPosition(position3.x - rcellsize, position3.y - rcellsize);
		}
		rotatenum++;
	}
	else if (shape == 5)
	{
		if (rotatenum == 0)
		{
			minos[0].setPosition(position0.x + (2*rcellsize), position0.y);
			minos[1].setPosition(position1.x + rcellsize, position1.y + rcellsize);
			minos[3].setPosition(position3.x - rcellsize, position3.y + rcellsize);
		}
		else if (rotatenum == 1)
		{
			minos[0].setPosition(position0.x, position0.y + (2*rcellsize));
			minos[1].setPosition(position1.x - rcellsize, position1.y + rcellsize);
			minos[3].setPosition(position3.x - rcellsize, position3.y - rcellsize);
		}
		else if (rotatenum == 2)
		{
			minos[0].setPosition(position0.x - (2*rcellsize), position0.y);
			minos[1].setPosition(position1.x - rcellsize, position1.y - rcellsize);
			minos[3].setPosition(position3.x + rcellsize, position3.y - rcellsize);
		}
		else if (rotatenum == 3)
		{
			minos[0].setPosition(position0.x, position0.y - (2*rcellsize));
			minos[1].setPosition(position1.x + rcellsize, position1.y - rcellsize);
			minos[3].setPosition(position3.x + rcellsize, position3.y + rcellsize);
		}
		rotatenum++;
	}
	else if (shape == 6)
	{
		if (rotatenum == 0)
		{
			minos[0].setPosition(position0.x + (2*rcellsize), position0.y);
			minos[1].setPosition(position1.x + rcellsize, position1.y - rcellsize);
			minos[3].setPosition(position3.x - rcellsize, position3.y + rcellsize);
		}
		else if (rotatenum == 1)
		{
			minos[0].setPosition(position0.x, position0.y + (2*rcellsize));
			minos[1].setPosition(position1.x + rcellsize, position1.y + rcellsize);
			minos[3].setPosition(position3.x - rcellsize, position3.y - rcellsize);
		}
		else if (rotatenum == 2)
		{
			minos[0].setPosition(position0.x - (2*rcellsize), position0.y);
			minos[1].setPosition(position1.x - rcellsize, position1.y + rcellsize);
			minos[3].setPosition(position3.x + rcellsize, position3.y - rcellsize);
		}
		else if (rotatenum == 3)
		{
			minos[0].setPosition(position0.x, position0.y - (2*rcellsize));
			minos[1].setPosition(position1.x - rcellsize, position1.y - rcellsize);
			minos[3].setPosition(position3.x + rcellsize, position3.y + rcellsize);
		}
		rotatenum++;
	}
	else if (shape == 7)
	{
		if (rotatenum == 0)
		{
			minos[0].setPosition(position0.x, position0.y + (2 * rcellsize));
			minos[1].setPosition(position1.x - rcellsize, position1.y + rcellsize);
			minos[3].setPosition(position3.x + rcellsize, position3.y - rcellsize);
		}
		else if (rotatenum == 1)
		{
			minos[0].setPosition(position0.x - (2 * rcellsize), position0.y);
			minos[1].setPosition(position1.x - rcellsize, position1.y - rcellsize);
			minos[3].setPosition(position3.x + rcellsize, position3.y + rcellsize);
		}
		else if (rotatenum == 2)
		{
			minos[0].setPosition(position0.x, position0.y - (2 * rcellsize));
			minos[1].setPosition(position1.x + rcellsize, position1.y - rcellsize);
			minos[3].setPosition(position3.x - rcellsize, position3.y + rcellsize);
		}
		else if (rotatenum == 3)
		{
			minos[0].setPosition(position0.x + (2 * rcellsize), position0.y);
			minos[1].setPosition(position1.x + rcellsize, position1.y + rcellsize);
			minos[3].setPosition(position3.x - rcellsize, position3.y - rcellsize);
		}
		rotatenum++;
	}
}

void Game::reset()
{
	if (ground == true)
	{
		position();
		minos[0].setPosition(position0.x,position0.y);
		minos[1].setPosition(position1.x, position1.y);
		minos[2].setPosition(position2.x, position2.y);
		minos[3].setPosition(position3.x, position3.y);
		minos[0].setFillColor(sf::Color::Transparent);
		minos[1].setFillColor(sf::Color::Transparent);
		minos[2].setFillColor(sf::Color::Transparent);
		minos[3].setFillColor(sf::Color::Transparent);
		
		if (timer.getElapsedTime().asSeconds() >= 1)
		{
			ground = false;
			initminos();
			timer.restart();
		}
	}
}

void Game::pollEvents()
{
	while (window->pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
		{
			window->close();
			running = false;
		}
		if (ground == false)
		{
			if (ev.type == sf::Event::KeyPressed)
			{
				if (ev.key.code == sf::Keyboard::A)
				{
					position();
					minos[0].setPosition(position0.x - rcellsize, position0.y);
					minos[1].setPosition(position1.x - rcellsize, position1.y);
					minos[2].setPosition(position2.x - rcellsize, position2.y);
					minos[3].setPosition(position3.x - rcellsize, position3.y);
				}
				else if (ev.key.code == sf::Keyboard::D)
				{
					position();
					minos[0].setPosition(position0.x + rcellsize, position0.y);
					minos[1].setPosition(position1.x + rcellsize, position1.y);
					minos[2].setPosition(position2.x + rcellsize, position2.y);
					minos[3].setPosition(position3.x + rcellsize, position3.y);
				}
				else if (ev.key.code == sf::Keyboard::W)
				{
					rotation();
				}
				else if (ev.key.code == sf::Keyboard::Space)
				{
					int minoy = 0;
					float blockdist = 0;
					float realblockdist;
					for (int i = 0; i < 219; i++)
					{
						sf::Vector2f blockpos = block[i].getPosition();
						if (block[i].getFillColor() != sf::Color::White || blockpos.y == height - rcellsize)
						{
							for (int j = 0; j < 4; j++)
							{
								sf::Vector2f minopos = minos[j].getPosition();
								if (minopos.x == blockpos.x)
								{
									if (minoy == 0)
									{
										minoy = minopos.y;
									}
									else if (minopos.y > minoy)
									{
										minoy = minopos.y;
									}
									if (blockdist == 0)
									{
										blockdist = blockpos.y - (minoy + rcellsize);
										realblockdist = blockdist;
									}
									else
									{
										blockdist = blockpos.y - (minoy + rcellsize);
									}
									if (blockdist < realblockdist)
									{
										realblockdist = blockdist;
									}
								}

							}
						}
					}
					if (count == 1)
					{
						realblockdist += 64;
					}
					minos[0].setPosition(position0.x, position0.y + realblockdist);
					minos[1].setPosition(position1.x, position1.y + realblockdist);
					minos[2].setPosition(position2.x, position2.y + realblockdist);
					minos[3].setPosition(position3.x, position3.y + realblockdist);
				}
			}
		}
	}
}

void Game::update()
{
	pollEvents();
	updateCollision();
	if (ground == false)
	{
		updateMinos();
	}
	updateBlock();
	reset();
}

void Game::render()
{
	window->clear();
	initBlocks();
	window->draw(minos[0]);
	window->draw(minos[1]);
	window->draw(minos[2]);
	window->draw(minos[3]);
	window->display();
}
