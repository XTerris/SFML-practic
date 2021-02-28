#include <vector>
using namespace std;
enum class Direction {
	Left,
	Right,
	Up,
	Down,
};
class Snake {
private:
	const int start_length = 3;
	pair<int, int> size;
	int score = 0;
	pair<int, int> apple;
	vector<pair<int, int>> body = { };
	void CreateApple();
public:
	Snake(pair<int, int> size);
	int Score() { return this->score; };
	void Move(Direction direction);
	vector<vector<int>> State();
	void Reset();
	bool inGame = true;
};