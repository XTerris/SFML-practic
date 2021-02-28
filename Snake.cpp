#include "Snake.h"
#include <ctime>
using namespace std;
Snake::Snake(pair<int, int> size) {
	this->size = size; // create first segments
	for (int i = this->start_length; i > 0; --i)
		this->body.push_back(Segment{ Direction::Up, make_pair(this->size.first / 2, this->size.second / 2 + i) });
	this->CreateApple();
}
void Snake::Move(Direction direction) {
	size_t head = this->body.size() - 1;
	if (direction == Direction::Up && this->body[head].pos.second == 0 ||
		direction == Direction::Down && this->body[head].pos.second == this->size.second - 1 ||
		direction == Direction::Left && this->body[head].pos.first == 0 ||
		direction == Direction::Right && this->body[head].pos.first == this->size.first - 1) {
		this->inGame = false;
		return;
	}
	for (size_t i = 1; i < this->body.size(); ++i) {
		this->body[i - 1] = this->body[i]; // moving segments without head
	}
	switch (direction) { // moving of head
	case Direction::Up:
		this->body[head].pos.second -= 1;
		break;
	case Direction::Down:
		this->body[head].pos.second += 1;
		break;
	case Direction::Right:
		this->body[head].pos.first += 1;
		break;
	case Direction::Left:
		this->body[head].pos.first -= 1;
		break;
	}
	if (this->body[head].pos.first < 0 || this->body[head].pos.first >= this->size.first ||
		this->body[head].pos.second < 0 || this->body[head].pos.second >= this->size.second)
		this->inGame = false; // if wend outside
	else if (this->body[head].pos == this->apple) { // add segments if apple was eated
		this->body.insert(this->body.begin(), this->body[0]);
		this->Score += 1;
		this->CreateApple();
	}
	head = this->body.size() - 1; // coordinates of head
	for (size_t i = 0; i < head; ++i) // if crashed
		if (this->body[i].pos == this->body[head].pos) this->inGame = false;
}
vector<vector<int>> Snake::State() {
	// fill matrix of areaSize with "0" as empty square, "1" as snake's segment and "2" as apple
	vector<vector<int>> state(this->size.first, vector<int>(this->size.second, 0));
	for (auto i : this->body)
		state[i.pos.first][i.pos.second] = 1;
	state[this->apple.first][this->apple.second] = 2;
	return state;
}
void Snake::CreateApple() {
	srand((unsigned int)time(NULL));
	while (true) {
		pair<int, int> t = make_pair(rand() % this->size.first, rand() % this->size.second);
		if (this->State()[t.first][t.second] != 1) { // if apple on snake create it again
			this->apple = t;
			return;
		}
	}
}
void Snake::Reset() {
	this->body.clear();
	for (int i = this->start_length; i > 0; --i)
		this->body.push_back(Segment{ Direction::Up, make_pair(this->size.first / 2, this->size.second / 2 + i) });
	this->CreateApple();
	this->inGame = true;
	this->Score = 0;
}