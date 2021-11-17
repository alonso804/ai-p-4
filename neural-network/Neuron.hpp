#ifndef Neuron_H
#define Neuron_H

#include <iostream>
#include <vector>
#include <cassert>

#include <eigen3/Eigen/Eigen>

using namespace std;

using Matrix = Eigen::MatrixXf;
using RowVector = Eigen::RowVectorXf;

class NeuralNetwork;

class Neuron {
  unsigned numOutputs;
  RowVector weights;
  double output;

public:
  Neuron(const unsigned& numOutputs) {
    this->numOutputs = numOutputs;
    this->weights = RowVector::Random(numOutputs);

    for (unsigned i = 0; i < weights.size(); i++) {
      weights[i] = abs(weights[i]);
    }

    //cout << weights << endl;
  }

  friend class NeuralNetwork;
};


#endif //Neuron_H
