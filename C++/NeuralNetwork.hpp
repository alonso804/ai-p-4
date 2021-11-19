#ifndef NeuralNetwork_H
#define NeuralNetwork_H

#include "Layer.hpp"
#include "ErrorFunct.hpp"

using Layers = vector<Layer>;

class NeuralNetwork {
	Layers layers;
	string cost_funct;
	double learning_rate;
  double (*cost)(Matrix, RowVector);

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

	void fit(Matrix x, RowVector y) {
		vector<pair<Matrix, Matrix>> out = {make_pair(Matrix(0, 0), x)};

		// Forward
		for (auto& layer : this->layers) {
			Matrix z = MatrixSum(out.back().second * layer.w, layer.b);
			Matrix a = layer.funct(z);
			cout << layer << endl << endl;

			out.push_back(make_pair(z, a));
		}

		// Reverse

		//cout << out.back().first << endl;
		cout << "Rows: " << out.back().first.rows() << endl;
		cout << "Cols: " << out.back().first.cols() << endl;
		cout << "Z: " << out.back().first.row(0) << endl;
		cout << "A: " << out.back().second.row(0) << endl;
		cout << "Sum: " << out.back().second.row(0).sum() << endl;
		cout << endl;
		//cout << "Calculating cost ...\n";
		//cout << "Cost: "<< this->cost(out.back().second, y) << endl;
		//cout << "Finish \n";
	}
};

#endif //NeuralNetwork_H
