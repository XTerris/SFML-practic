#include "Snake.h"
#include <ctime>
using namespace std;
Snake::Snake(pair<int, int> size) {
	this->size = size;
	for (int i = this->start_length; i > 0; --i)
		this->body.push_back(make_pair(this->size.first / 2, this->size.second / 2 + i));
	this->CreateApple();
}
void Snake::Move(Direction direction) {
	for (size_t i = 1; i < this->body.size(); ++i) {
		this->body[i - 1] = this->body[i];
	}
	int head = this->body.size() - 1;
	switch (direction) {
		case Direction::Up:
			if (this->body[head].second == 0) inGame = false;
			else this->body[head].second -= 1;
			break;
		case Direction::Down:
			if (this->body[head].second == this->size.second - 1) inGame = false;
			else this->body[head].second += 1;
			break;
		case Direction::Right:
			if (this->body[head].first == this->size.first - 1) inGame = false;
			else this->body[head].first += 1;
			break;
		case Direction::Left:
			if (this->body[head].first == 0) inGame = false;
			else this->body[head].first -= 1;
			break;
	}
	if (this->body[head].first < 0 || this->body[head].first >= this->size.first || this->body[head].second < 0 || this->body[head].second >= this->size.second)
		this->inGame = false;
	else if (this->body[head] == this->apple) {
		this->body.insert(this->body.begin(), this->body[0]);
		this->score += 1;
		this->CreateApple();
	}
	for (size_t i = 0; i < this->body.size(); ++i)
		if (i != head && this->body[i] == this->body[head]) this->inGame = false;
}
vector<vector<int>> Snake::State() {
	vector<vector<int>> state(this->size.first, vector<int>(this->size.second, 0));
	for (auto i : this->body)
		state[i.first][i.second] = 1;
	state[this->apple.first][this->apple.second] = 2;
	return state;
}
void Snake::CreateApple() {
	srand((unsigned int)time(0));
	while (true) {
		pair<int, int> t = make_pair(rand() % this->size.first, rand() % this->size.second);
		if (this->State()[t.first][t.second] != 1) {
			this->apple = t;
			return;
		}
	}
}