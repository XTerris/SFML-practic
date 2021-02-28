#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "NN.h"
#include <vector>
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
	score.setString("Score: " + to_string(snake.Score()));
	score.setFillColor(Color::White);
	score.setPosition(Vector2f(10, 0));
	window.draw(score);
	window.display();
}
int main()
{
	const pair<int, int> areaSize = make_pair(30, 20);
	const float speed = 7;
	const int segmentSize = 30;
	const int scoreMargin = 2;
	Snake snake(areaSize);
	RenderWindow window(VideoMode(areaSize.first * segmentSize, (areaSize.second + scoreMargin) * segmentSize), "Snake");
	Direction dir = Direction::Up;
	clock_t last_clock = clock();
	while (true) {
		Event event = Event();
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			else { // turns with arrow keys
				switch (event.key.code) {
				case 71:
					dir = dir == Direction::Right ? dir : Direction::Left;
					break;
				case 72:
					dir = dir == Direction::Left ? dir : Direction::Right;
					break;
				case 73:
					dir = dir == Direction::Down ? dir : Direction::Up;
					break;
				case 74:
					dir = dir == Direction::Up ? dir : Direction::Down;;
					break;
				}
			}
		}
		if (snake.inGame) {
			if ((float)(clock() - last_clock) / CLOCKS_PER_SEC > 1.0 / speed) {
				snake.Move(dir);
				last_clock = clock();
				Draw(window, snake, segmentSize);
			}
		}
		else {
			window.close();
			break;
		};
	}
	return 0;
}