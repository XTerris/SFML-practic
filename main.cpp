#include <SFML/Graphics.hpp>
#include "Snake.h"
#include <iostream>
using namespace sf;
using namespace std;
int main()
{
	const int segmentSize = 30;
	const pair<int, int> areaSize = make_pair(30, 20);
	const float speed = 7;
	Event event;
	Snake snake(areaSize);
	RenderWindow window(VideoMode(areaSize.first * segmentSize, areaSize.second * segmentSize), "Snake");
	Direction dir = Direction::Up;
	clock_t last_clock = clock();
	RectangleShape bodySegment(Vector2f(segmentSize, segmentSize));
	bodySegment.setFillColor(Color::Green);
	CircleShape apple(segmentSize / 2);
	apple.setFillColor(Color::Red);
	vector<vector<int>> state;
	while (true) {
		event = Event();
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
			else {
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
				window.clear();
				state = snake.State();
				for (int i = 0; i < areaSize.first; ++i) {
					for (int j = 0; j < areaSize.second; ++j) {
						if (state[i][j] == 1) {
							bodySegment.setPosition(Vector2f((float)(segmentSize * i), (float)(segmentSize * j)));
							window.draw(bodySegment);
						}
						else if (state[i][j] == 2) {
							apple.setPosition(Vector2f((float)(segmentSize * i), (float)(segmentSize * j)));
							window.draw(apple);
						}
					}
				}
				window.display();
			}
		}
		else break;
	}
	cout << snake.Score();
	return 0;
}