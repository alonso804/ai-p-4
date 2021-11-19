#ifndef NeuralNetwork_H
#define NeuralNetwork_H

#include "Layer.hpp"
#include "ErrorFunct.hpp"

using Layers = vector<Layer>;

class NeuralNetwork {
	Layers layers;
	string cost_funct;
	double learning_rate;
  RowVector (*cost)(Matrix, RowVector, map<double, unsigned>);

public:
	NeuralNetwork() = default;

	NeuralNetwork(Layers layers, string cost_funct, double learning_rate = 0.5) {
    assert(cost_funct == "mse");

		this->layers = layers;
		this->learning_rate = learning_rate;
		this->cost_funct = cost_funct;

		if (cost_funct == "mse") {
			this->cost = &MSE;
		}
	}

	void fit(Matrix x, RowVector y, map<double, unsigned> mapper) {
		vector<pair<Matrix, Matrix>> out = {make_pair(Matrix(0, 0), x)};

		// Forward
		for (auto& layer : this->layers) {
			Matrix z = MatrixSum(out.back().second * layer.w, layer.b);
			Matrix a = layer.funct(z);
			cout << layer << endl;

			out.push_back(make_pair(z, a));
		}

		RowVector errors = this->cost(out.back().second, y, mapper);
		cout << errors.sum() / errors.size() << endl;

		// Reverse

	}
};

#endif //NeuralNetwork_H
