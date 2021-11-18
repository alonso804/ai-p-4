#ifndef Layer_H
#define Layer_H

#include "ActFuncts.hpp"
#include <iostream>
#include <tuple>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include <eigen3/Eigen/Eigen>

using namespace std;

using Matrix = Eigen::MatrixXd;
using RowVector = Eigen::RowVectorXd;

class NeuralNetwork;

class Layer {
	string act_f;
	unsigned n_connections;
	unsigned n_neurons;
  double (*funct)(double);
  double (*derivative)(double);
	Matrix b;
	Matrix w;

public:
	Layer() = default;

	Layer(unsigned n_connections, unsigned n_neurons, string act_f) {
    assert(act_f == "tanh" || act_f == "sigmoide" || act_f == "relu");

    this->act_f = act_f;

    if (act_f == "tanh") {
      this->funct = &Tanh;
      this->derivative = &TanhDerivative;
    }

    if (act_f == "sigmoide") {
      this->funct = &Sigmoide;
      this->derivative = &SigmoideDerivate;
    }

    if (act_f == "relu") {
      this->funct = &RELU;
      this->derivative = &RELUDerivate;
    }

		this->n_connections = n_connections;
		this->n_neurons = n_neurons;

		this->b = Matrix::Random(1, n_neurons);
		this->w = Matrix::Random(n_connections, n_neurons);
	}

  friend class NeuralNetwork;
  friend ostream& operator << (ostream&, const Layer&);
};

ostream& operator << (ostream& os, const Layer& l) {
  os << "# Connection: " << l.n_connections << endl;
  os << "# Neurons: " << l.n_neurons << endl;
  os << "Activaton Function: " << l.act_f;

  return os;
}

#endif //Layer_H
