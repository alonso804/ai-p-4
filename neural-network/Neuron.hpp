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
class Neuron;

using Layer = vector<Neuron>;

class Neuron {
  unsigned numOutputs;
  RowVector weights;
  double output;
  unsigned idx;

public:
  Neuron(const unsigned& numOutputs, const unsigned& idx) {
    this->numOutputs = numOutputs;
    this->weights = RowVector::Random(numOutputs);

    for (unsigned i = 0; i < weights.size(); i++) {
      weights[i] = abs(weights[i]);
    }

    this->output = 0;
    this->idx = idx;
    //cout << weights << endl;
  }

  void forward(Layer* prevLayer, double (*funct)(double)) {
    double sum = 0;

    /*
     *cout << prevLayer->size() << endl;
     *cout << (*prevLayer)[0].weights.size() << endl;
     *cout << this->idx << endl << endl;
     */

    for (unsigned i = 0; i < prevLayer->size(); i++) {
      sum += (*prevLayer)[i].output * (*prevLayer)[i].weights[this->idx];
    }

    this->output = funct(sum);
    cout << sum << endl;
    cout << this->output << endl;
  }

  friend class NeuralNetwork;
};


#endif //Neuron_H
