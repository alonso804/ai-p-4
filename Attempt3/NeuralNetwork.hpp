#ifndef NeuralNetwork_H
#define NeuralNetwork_H

#include "Layer.hpp"
#include "ErrorFunct.hpp"

class NeuralNetwork {
	Layers layers;
	string cost_funct;
	double alpha;
	unsigned epochs;
  double (*costF)(const Matrix&, const unsigned&);
  Matrix (*costD)(Matrix, const unsigned&);

public:
	NeuralNetwork() = default;

	NeuralNetwork(Layers layers, string cost_funct, unsigned epochs, double alpha) {
    assert(cost_funct == "mse");

		this->layers = layers;
		this->epochs = epochs;
		this->alpha = alpha;
		this->cost_funct = cost_funct;

		if (cost_funct == "mse") {
			this->costF = &MSE;
			this->costD = &MSE_Derivate;
		}
	}

	Matrix train(const Matrix& x, unsigned& y_idx) {
		Charges out = {x};

		for (auto& layer : this->layers) {
			//cout << layer << endl;
			//shape(out.back());
			//shape(layer.w);
			Matrix z = MatrixSum(out.back() * layer.w, layer.b);
			Matrix a = layer.actF(z);

			out.push_back(a);
		}

		list<Matrix> deltas;
		Matrix tempW;

		for (int i = this->layers.size() - 1; i >=0; i--) {
			Matrix a = out[i + 1];

			if (i == this->layers.size() - 1) {
				Matrix c = this->costD(a, y_idx);
				Matrix d = this->layers[i].actD(a);

				Matrix delta = MatrixProd(c, d);
				deltas.push_front(delta);

			} else {

				Matrix c = deltas.front() * tempW.transpose();
				Matrix d = this->layers[i].actD(a);

				Matrix delta = MatrixProd(c, d);
				deltas.push_front(delta);
			}

			tempW = this->layers[i].w;

			this->layers[i].w -= out[i].transpose() * deltas.front() * alpha;
			this->layers[i].b -= deltas.front() * alpha;
		}

		return out.back();
	}

	void fit(const Matrix& x, const RowVector& y, Mapper& mapper) {
		for (unsigned epoch = 0; epoch < this->epochs; epoch++) {
			for (int i = 0; i < x.rows(); i++) {
				Matrix out_layer = train(x.row(i), mapper[y[i]]);

				double error = this->costF(out_layer, mapper[y[i]]);
				if (i == x.rows() - 1) {
				//if (i % 50 == 0) {
					cout << error << endl;
				}
			}
		}
	}
};

#endif //NeuralNetwork_H
