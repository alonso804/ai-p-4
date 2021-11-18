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
		 *for (auto t : this->layers) {
		 *  cout << t << endl << endl;
		 *}
		 */
	}

	void fit(vector<RowVector*> x, vector<RowVector*> y) {
		/*
		 *for (auto& i : x) {
		 *  cout << *i << endl;
		 *}
		 */

		for (auto& i : y) {
			cout << *i << endl;
		}
		vector<pair<double, vector<RowVector*>>> out = {make_pair(0, x)};

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
