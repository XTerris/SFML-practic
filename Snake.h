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
private:
	const int start_length = 3;
	pair<int, int> size;
	void CreateApple();
public:
	Snake(pair<int, int> size);
	void Move(Direction direction);
	vector<vector<int>> State();
	void Reset();
	bool inGame = true;
	vector<Segment> body = { };
	pair<int, int> apple;
	int Score = 0;
};