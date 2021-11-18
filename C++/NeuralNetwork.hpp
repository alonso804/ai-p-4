#ifndef NeuralNetwork_H
#define NeuralNetwork_H

#include "Layer.hpp"
#include "ErrorFunct.hpp"

using Layers = vector<Layer>;

class NeuralNetwork {
	Layers layers;
	string cost_funct;
	double learning_rate;
  double (*cost)(RowVector, RowVector);

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

		/*
		 *cout << layers[0] << endl << endl;
		 *cout << layers[0].b << endl << endl;
		 *cout << layers[0].w << endl;
		 */
	}

	void fit(Matrix x, RowVector y) {
		//cout << x << endl;
		cout << y << endl;
		//vector<pair<double, vector<RowVector*>>> out = {make_pair(0, x)};

		/*
		 *for (auto& layer : layers) {
		 *  cout << layer.w << endl;
		 *}
		 */
		/*
		 *for (size_t  i = 0; i < this->layers.size(); i++) {
		 *  //auto z = out.back().second * 
		 *}
		 *for (auto i : out[0].second) {
		 *  cout << *(i) << endl;
		 *  cout << *(i) << endl;
		 *}
		 */
	}
};

#endif //NeuralNetwork_H
