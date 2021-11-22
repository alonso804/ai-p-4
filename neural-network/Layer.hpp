#ifndef Layer_H
#define Layer_H

#include "ActFuncts.hpp"
#include "Helpers.hpp"

class NeuralNetwork;

class Layer {
	string act_f;
	unsigned n_connections;
	unsigned n_neurons;
  Matrix (*actF)(Matrix);
  Matrix (*actD)(Matrix);
	Matrix b;
	Matrix w;

public:
	Layer() = default;

	Layer(unsigned n_connections, unsigned n_neurons, string act_f) {
    assert(act_f == "tanh" || act_f == "sigm" || act_f == "relu" || act_f == "softmax");

    this->act_f = act_f;

    if (act_f == "tanh") {
      this->actF = &TanhF;
      this->actD = &TanhD;
    }

    if (act_f == "sigm") {
      this->actF = &SigmF;
      this->actD = &SigmD;
    }

    if (act_f == "relu") {
      this->actF = &ReluF;
      this->actD = &ReluD;
    }

    if (act_f == "softmax") {
      this->actF = &SoftMaxF;
      this->actD = &SoftMaxD;
    }

		this->n_connections = n_connections;
		this->n_neurons = n_neurons;

		this->b = Matrix::Random(1, n_neurons);
		this->w = Matrix::Random(n_connections, n_neurons);
	}

  static Layers create(const initializer_list<pair<unsigned, string>>& topology) {
    Layers layers;

    for (auto it = topology.begin(); it != topology.end() - 1; it++) {
      layers.push_back(Layer((*it).first, (*(it + 1)).first, (*it).second));
    }

    return layers;
  }

  friend class NeuralNetwork;
  friend ostream& operator << (ostream&, const Layer&);
};

ostream& operator << (ostream& os, const Layer& l) {
  os << "# Connection: " << l.n_connections << endl;
  os << "# Neurons: " << l.n_neurons << endl;
  os << "Activaton Function: " << l.act_f << endl;
  os << "w: ";
  shape(l.w);
  os << "b: ";
  shape(l.b);

  return os;
}

#endif //Layer_H
