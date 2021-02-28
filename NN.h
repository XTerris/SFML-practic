#include <vector>
using namespace std;
struct Neuron {
	float input;
	vector<float> weights;
	float output;
};
class NN {
private:
	vector<vector<Neuron>> structure;
	float Activation(float x);
	float Derivative(float x);
public:
	NN(vector<int> structure);
	vector<float> FeedForward(vector<float> input);
	vector<float> getMSE(vector<float> input, vector<float> right_output);
	void PrintStructure();
};