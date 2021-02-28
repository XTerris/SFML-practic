#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "NN.h"
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;
void Draw(RenderWindow& window, Snake& snake, const float segmentSize) {
	vector<vector<int>> state = snake.State();
	const int scoreMargin = 2;
	window.clear();
	for (size_t i = 0; i < state.size(); ++i) {
		for (size_t j = 0; j < state[0].size(); ++j) {
			if (state[i][j] == 1) {
				RectangleShape bodySegment(Vector2f(segmentSize, segmentSize));
				bodySegment.setFillColor(Color::Green);
				bodySegment.setOutlineThickness(1);
				bodySegment.setOutlineColor(Color::Black);
				bodySegment.setPosition(Vector2f(segmentSize * i, segmentSize * (j + scoreMargin)));
				window.draw(bodySegment);
			}
			else if (state[i][j] == 2) {
				CircleShape apple(segmentSize / 2);
				apple.setFillColor(Color::Red);
				apple.setPosition(Vector2f(segmentSize * i, segmentSize * (j + scoreMargin)));
				window.draw(apple);
			}
		}
	}
	RectangleShape interface(Vector2f(segmentSize * state.size(), scoreMargin * segmentSize));
	interface.setFillColor(Color(28, 28, 28));
	window.draw(interface);
	Font font;
	font.loadFromFile("Font.ttf");
	Text score("", font, (unsigned int)segmentSize * scoreMargin - 10);
	score.setString("Score: " + to_string(snake.Score));
	score.setFillColor(Color::White);
	score.setPosition(Vector2f(10, 0));
	window.draw(score);
	window.display();
}
int main()
{
	const pair<int, int> areaSize = make_pair(30, 20);
	const int segmentSize = 30;
	const int scoreMargin = 2;
	const int speed = 7;
	bool pause = false;
	bool active = true;
	Snake snake(areaSize);
	ContextSettings settings;
	settings.antialiasingLevel = 4;
	RenderWindow window(VideoMode(areaSize.first * segmentSize, (areaSize.second + scoreMargin) * segmentSize), "Snake", Style::Default, settings);
	Direction dir = Direction::Up;
	Clock timer;
	while (active) {
		Event event = Event();
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) {
				window.close();
				active = false;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Space) && !snake.inGame) {
				snake.Reset();
				dir = Direction::Up;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left))
				dir = dir == Direction::Right ? dir : Direction::Left;
			else if (Keyboard::isKeyPressed(Keyboard::Right))
				dir = dir == Direction::Left ? dir : Direction::Right;
			else if (Keyboard::isKeyPressed(Keyboard::Up))
				dir = dir == Direction::Down ? dir : Direction::Up;
			else if (Keyboard::isKeyPressed(Keyboard::Down))
				dir = dir == Direction::Up ? dir : Direction::Down;
			else if (Keyboard::isKeyPressed(Keyboard::Pause)) pause = !pause;
		}
		if (snake.inGame && !pause) {
			if (timer.getElapsedTime().asMilliseconds() > 1000 / (float)speed) {
				snake.Move(dir);
				Draw(window, snake, segmentSize);
				timer.restart();
			}
		}
	}
	return 0;
}