#ifndef NeuralNetwork_H
#define NeuralNetwork_H

#include <iostream>
#include <vector>

#include <eigen3/Eigen/Eigen>

using namespace std;

using Matrix = Eigen::MatrixXf;
using RowVector = Eigen::RowVectorXf;

class NeuralNetwork {
  vector<unsigned> topology;
	vector<RowVector*> neuronLayers;
  vector<RowVector*> cacheLayers;
  vector<RowVector*> deltas;
  vector<Matrix*> weights;

public:
  NeuralNetwork(const vector<unsigned>& topology) {
    this->topology = topology;
  }

	virtual ~NeuralNetwork();
};

#endif //NeuralNetwork_H
