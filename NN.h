#include <vector>
using namespace std;
struct Neuron {
	float input;
	vector<float> weights;
	float output;
	float error;
};
class NN {
private:
	vector<vector<Neuron>> structure;
	float Activation(float x);
	float Derivative(float x);
	float Error(float x, float y);
public:
	NN(vector<int> structure);
	vector<float> FeedForward(vector<float> input);
	void Train(vector<float> input, vector<float> right_output);
	float getMSE(vector<float> input, vector<float> right_output);
	void PrintStructure();
};