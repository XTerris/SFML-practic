#include <vector>
#include "NN.h"
#include <ctime>
#include <iostream>
using namespace std;
float NN::Activation(float x) {
	return x < 0 ? x * 0.01 : x; // Leaky ReLU
}
float NN::Derivative(float x) {
	return x < 0 ? 0.01 : 1; // LeakyReLU's derivative
}
NN::NN(vector<int> structure) {
	srand(time(NULL));
	for (auto l : structure) { // filling structure with neurons
		this->structure.push_back(vector<Neuron>(l, Neuron()));
		int size = this->structure.size(); // count of filled layers
		if (size == 1) continue; // if firts layer continue
		for (auto &n : this->structure[size - 1]) { // else for each neuron
			n.weights = vector<float>(this->structure[size - 2].size());
			for (auto &i : n.weights) i = (float)rand() / RAND_MAX; // set random weights
		}
	}
}
vector<float> NN::FeedForward(vector<float> input) {
	if (input.size() != this->structure[0].size()) // throw exception if input is of invalid size
		throw invalid_argument("Invalid size of input");
	for (int l = 0; l < this->structure.size(); ++l) { // each layer
		if (l == 0) { // first layer
			for (int i = 0; i < input.size(); ++i) // each neuron
				this->structure[0][i].input = input[i]; // set inputs
		}
		else { // from second to last layers
			for (int n = 0; n < this->structure[l].size(); ++n) { // each neuron
				for (int i = 0; i < this->structure[l - 1].size(); ++n) { // each neuron of last layer

				}
			}
		}
		// calc outputs for each neuron
	}
}
void NN::PrintStructure() {
	for (auto l : this->structure) {
		cout << l.size() << " ";
	}
}