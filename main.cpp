#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "NN.h"
#include <vector>
#include <iostream>
using namespace sf;
using namespace std;
void Draw(RenderWindow& window, Snake& snake, const float segmentSize, float moveProgress) {
	const int scoreMargin = 2;
	window.clear();
	RectangleShape bodySegment(Vector2f(segmentSize, segmentSize));
	bodySegment.setFillColor(Color::Green);
	for (size_t i = 1; i < snake.body.size() - 1; ++i) {
		bodySegment.setPosition(Vector2f(segmentSize * snake.body[i].pos.first, segmentSize * (snake.body[i].pos.second + scoreMargin)));
		window.draw(bodySegment);
	}
	Segment head = snake.body[snake.body.size() - 1];
	if (head.dir == Direction::Down || head.dir == Direction::Up)
		bodySegment.setSize(Vector2f(segmentSize, segmentSize * moveProgress));
	else
		bodySegment.setSize(Vector2f(segmentSize * moveProgress, segmentSize));
	if (head.dir == Direction::Up)
		bodySegment.setPosition(Vector2f(segmentSize * head.pos.first, segmentSize * (head.pos.second + scoreMargin - moveProgress + 1)));
	else if (head.dir == Direction::Down || head.dir == Direction::Right)
		bodySegment.setPosition(Vector2f(segmentSize * head.pos.first, segmentSize * (head.pos.second + scoreMargin)));
	else if (head.dir == Direction::Left)
		bodySegment.setPosition(Vector2f(segmentSize * (head.pos.first - moveProgress + 1), segmentSize * (head.pos.second + scoreMargin)));
	window.draw(bodySegment);
	Segment tail = snake.body[0];
	if (tail.dir == Direction::Down || tail.dir == Direction::Up)
		bodySegment.setSize(Vector2f(segmentSize, segmentSize * (1 - moveProgress)));
	else
		bodySegment.setSize(Vector2f(segmentSize * (1 - moveProgress), segmentSize));
	if (tail.dir == Direction::Up || tail.dir == Direction::Left)
		bodySegment.setPosition(Vector2f(segmentSize * tail.pos.first, segmentSize * (tail.pos.second + scoreMargin)));
	else if (tail.dir == Direction::Down)
		bodySegment.setPosition(Vector2f(segmentSize * tail.pos.first, segmentSize * (tail.pos.second + scoreMargin + moveProgress)));
	else if (tail.dir == Direction::Right)
		bodySegment.setPosition(Vector2f(segmentSize * (tail.pos.first + moveProgress), segmentSize * (tail.pos.second + scoreMargin)));
	window.draw(bodySegment);

	CircleShape apple(segmentSize / 2);
	apple.setFillColor(Color::Red);
	apple.setPosition(Vector2f(segmentSize * snake.apple.first, segmentSize * (snake.apple.second + scoreMargin)));
	window.draw(apple);
	RectangleShape interface(Vector2f(segmentSize * snake.size.first, scoreMargin * segmentSize));
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
	NN n({ 2, 3, 1 });
	vector<float> input = { 0, 1 };
	vector<float> output = { 1 };
	for (auto i : n.FeedForward(input))
		cout << i << " ";
	n.Train(input, output);
	return 0;
	const pair<int, int> areaSize = make_pair(30, 20);
	const int segmentSize = 30;
	const int scoreMargin = 2;
	float speed = 7;
	bool pause = false;
	bool active = true;
	Snake snake(areaSize);
	ContextSettings settings;
	settings.antialiasingLevel = 4;
	RenderWindow window(VideoMode(areaSize.first * segmentSize, (areaSize.second + scoreMargin) * segmentSize), "Snake", Style::Default, settings);
	Direction dir = Direction::Up;
	Clock timer;
	Clock moveTimer;
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
			else if (Keyboard::isKeyPressed(Keyboard::Pause))
				pause = !pause;
			if (Keyboard::isKeyPressed(Keyboard::Add))
				speed += 1;
			if (Keyboard::isKeyPressed(Keyboard::Subtract))
				speed = max((float)1, speed - 1);
		}
		if (snake.inGame && !pause) {
			if (moveTimer.getElapsedTime().asMilliseconds() >= 1000 / speed / segmentSize) {
				Draw(window, snake, segmentSize, timer.getElapsedTime().asMilliseconds() / (float)1000 * speed);
				if (timer.getElapsedTime().asMilliseconds() >= 1000 / speed) {
					snake.Move(dir);
					timer.restart();
				}
				moveTimer.restart();
			}
		}
	}
	return 0;
}