#ifndef NeuralNetwork_H
#define NeuralNetwork_H

#include "Layer.hpp"
#include "ErrorFunct.hpp"

using Topology = vector<Layer>;

class NeuralNetwork {
	Topology topology;
	string cost_funct;
	double learning_rate;
  double (*cost)(RowVector, RowVector);

public:
	NeuralNetwork() = default;

	NeuralNetwork(Topology topology, string cost_funct, double learning_rate = 0.5) {
    assert(cost_funct == "mse");

		this->topology = topology;
		this->learning_rate = learning_rate;
		this->cost_funct = cost_funct;

		if (cost_funct == "mse") {
			this->cost = &MSE;
		}

		/*
		 *for (auto t : topology) {
		 *  cout << t << endl << endl;
		 *}
		 */
	}

	void fit(vector<RowVector*> x, vector<RowVector*> y) {
		vector<pair<double, double>> out = {make_pair(0, x)};
	}
};

#endif //NeuralNetwork_H
