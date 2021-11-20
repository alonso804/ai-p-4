#ifndef NeuralNetwork_H
#define NeuralNetwork_H

#include "Layer.hpp"
#include "ErrorFunct.hpp"

using Layers = vector<Layer>;

class NeuralNetwork {
	Layers layers;
	string cost_funct;
	double learning_rate;
	unsigned epochs;
  RowVector (*cost)(const Matrix&, const RowVector&, map<double, unsigned>);
  RowVector (*costD)(Matrix, RowVector, map<double, unsigned>);

	void shape(const Matrix& x) {
		cout << "(" << x.rows() << ", " << x.cols() << ")" << endl;
	}

public:
	NeuralNetwork() = default;

	NeuralNetwork(Layers layers, string cost_funct, unsigned epochs, double learning_rate) {
    assert(cost_funct == "mse");

		this->layers = layers;
		this->epochs = epochs;
		this->learning_rate = learning_rate;
		this->cost_funct = cost_funct;

		if (cost_funct == "mse") {
			this->cost = &MSE;
			this->costD = &MSE_Derivate;
		}
	}

	Matrix train(Matrix x, RowVector y, map<double, unsigned> mapper) {
		vector<pair<Matrix, Matrix>> out = {make_pair(Matrix(0, 0), x)};

		// Forward
		for (auto& layer : this->layers) {
			Matrix z = MatrixSum(out.back().second * layer.w, layer.b);
			Matrix a = layer.funct(z);

			out.push_back(make_pair(z, a));
		}

		/*
		 *RowVector errors = this->cost(out.back().second, y, mapper);
		 *cout << "Error mean: " << errors.mean() << endl;
		 */

		// Reverse
		list<Matrix> deltas;
		Matrix tempW;

		for (int i = this->layers.size() - 1; i >=0; i--) {
			Matrix z = out[i + 1].first;
			Matrix a = out[i + 1].second;

			if (i == this->layers.size() - 1) {
				RowVector c = this->costD(a, y, mapper);
				Matrix d = this->layers[i].derivative(a);

				Matrix res = MatrixProd(c.transpose(), d);
				deltas.push_front(res);
			} else {
				Matrix c = deltas.front() * tempW.transpose();
				Matrix d = this->layers[i].derivative(a);
				
				Matrix res = MatrixProd(c, d);
				deltas.push_front(res);
			}

			tempW = this->layers[i].w;

			// Gradient descent
			unsigned bRows = this->layers[i].b.rows();
			unsigned bCols = this->layers[i].b.cols();
			this->layers[i].b -= mean(deltas.front(), bRows, bCols) * learning_rate;

			this->layers[i].w -= (out[i].second.transpose() * deltas.front()) * learning_rate;
		}

		return out.back().second;
	}

	void fit(Matrix x, RowVector y, map<double, unsigned> mapper) {
		for (unsigned i = 0; i < this->epochs; i++) {
			if (i % 15 == 0) {
				cout << this->cost(this->train(x, y, mapper), y, mapper).mean() << endl;
			}
		}
	}
};

#endif //NeuralNetwork_H
