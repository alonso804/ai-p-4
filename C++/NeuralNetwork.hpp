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

	Matrix activation(Matrix x, double (*f)(double)) {
		for (unsigned i = 0; i < x.rows(); i++) {
			for (unsigned j = 0; j < x.cols(); j++) {
				x(i, j) = f(x(i, j));
			}
		}

		return x;
	}

	Matrix derivate(Matrix x, double (*d)(double)) {
		for (unsigned i = 0; i < x.rows(); i++) {
			for (unsigned j = 0; j < x.cols(); j++) {
				x(i, j) = d(x(i, j));
			}
		}

		return x;
	}

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
			Matrix a = activation(z, layer.funct);

			out.push_back(make_pair(z, a));
		}

		// Reverse

		/*
		 *cout << out.back().second << endl;
		 *cout << "Rows: " << out.back().second.rows() << endl;
		 *cout << "Cols: " << out.back().second.cols() << endl;
		 */
		cout << "Calculating cost ...\n";
		cout << "Cost: "<< this->cost(out.back().second, y) << endl;
		cout << "Finish \n";
	}
};

#endif //NeuralNetwork_H
