#ifndef NeuralNetwork_H
#define NeuralNetwork_H

#include "Neuron.hpp"

using Layer = vector<Neuron>;

class NeuralNetwork {
  vector<unsigned> topology;
  vector<Layer> layers;
  unsigned numLayers;

  void propagateForward(const RowVector& input) {
    assert(input.size() == layers[0].size());
    
    for (unsigned i = 0; i < input.size(); i++) {
      this->layers[0][i].output = input[i];
    }
  }

public:
  NeuralNetwork(const vector<unsigned>& topology) {
    this->topology = topology;
    this->numLayers = topology.size();

    for (unsigned layerIdx = 0; layerIdx < numLayers; layerIdx++) {
      layers.push_back(Layer());
      unsigned numOutputs = layerIdx == numLayers - 1 ? 0 : topology[layerIdx + 1];

      for (unsigned neuronIdx = 0; neuronIdx < topology[layerIdx]; neuronIdx++) {
        //printf("Layer %d - Neuron %d created!\n", layerIdx, neuronIdx);
        layers.back().push_back(Neuron(numOutputs));
      }
    }
  }

  void fit(const vector<RowVector*>& inputs, vector<RowVector*> outputs) {
    for (unsigned i = 0; i < outputs.size(); i++) {
      this->propagateForward(*inputs[i]);
      //cout << (*inputs[i]).size() << endl;
      //this->propagateBackward(*inputs[i]);
    }
  }

  virtual ~NeuralNetwork() {}
};

#endif //NeuralNetwork_H
