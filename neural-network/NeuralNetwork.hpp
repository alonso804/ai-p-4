#ifndef NeuralNetwork_H
#define NeuralNetwork_H

#include "Neuron.hpp"
#include "ActivationFunctions.hpp"

class NeuralNetwork {
  vector<Layer> layers;
  unsigned numLayers;
  double (*funct)(double);
  double (*derivative)(double);

  void propagateForward(const RowVector& input) {
    assert(input.size() == layers[0].size() - 1);
    
    for (unsigned i = 0; i < input.size(); i++) {
      this->layers[0][i].output = input[i];
    }

    this->layers[0][layers[0].size() - 1].output = 1;

    for (unsigned layerIdx = 1; layerIdx < this->numLayers; layerIdx++) {
      Layer* prevLayer = &this->layers[layerIdx - 1];
      for (unsigned neuronIdx = 0; neuronIdx < this->layers[layerIdx].size() - 1; neuronIdx++) {
        this->layers[layerIdx][neuronIdx].forward(prevLayer, funct);
      }
    }
  }

  void propagateBackward() {

  }

public:
  NeuralNetwork(const vector<unsigned>& topology, const string& functName) {
    assert(functName == "tanh" || functName == "sigmoide" || functName == "relu");

    if (functName == "tanh") {
      this->funct = &Tanh;
      this->derivative = &TanhDerivative;
    }

    if (functName == "sigmoide") {
      this->funct = &Sigmoide;
      this->derivative = &SigmoideDerivate;
    }

    if (functName == "relu") {
      this->funct = &RELU;
      this->derivative = &RELUDerivate;
    }

    this->numLayers = topology.size();

    for (unsigned layerIdx = 0; layerIdx < numLayers; layerIdx++) {
      layers.push_back(Layer());
      unsigned numOutputs = layerIdx == numLayers - 1 ? 0 : topology[layerIdx + 1];

      for (unsigned neuronIdx = 0; neuronIdx <= topology[layerIdx]; neuronIdx++) {
        layers.back().push_back(Neuron(numOutputs, neuronIdx));
      }
    }
  }

  void fit(const vector<RowVector*>& inputs, vector<RowVector*> outputs) {
    for (unsigned i = 0; i < outputs.size(); i++) {
      this->propagateForward(*inputs[i]);
      for (auto i : this->layers[this->layers.size() - 1]) {
        cout << i.output << endl;
      }
      cout << endl;
    }

    //cout << this->layers[this->layers.size() - 1].size() << endl;
  }

  virtual ~NeuralNetwork() {}
};

#endif //NeuralNetwork_H
