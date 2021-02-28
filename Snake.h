#include <vector>
using namespace std;
enum class Direction {
	Left,
	Right,
	Up,
	Down,
};
struct Segment {
	Direction dir;
	pair<int, int> pos;
};
class Snake {
public:
	Snake(pair<int, int> size);
	const int start_length = 3;
	void Move(Direction direction);
	vector<vector<int>> State();
	void Reset();
	void CreateApple();
	pair<int, int> size;
	bool inGame = true;
	vector<Segment> body = { };
	pair<int, int> apple;
	int Score = 0;
};