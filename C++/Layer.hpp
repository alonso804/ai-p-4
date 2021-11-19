#ifndef Layer_H
#define Layer_H

#include "ActFuncts.hpp"
#include <iostream>
#include <tuple>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstddef>
#include <initializer_list>
#include <set>
#include <map>
#include <utility>

#include <eigen3/Eigen/Eigen>

using namespace std;

using Matrix = Eigen::MatrixXd;
using RowVector = Eigen::RowVectorXd;

class NeuralNetwork;

class Layer {
	string act_f;
	unsigned n_connections;
	unsigned n_neurons;
  Matrix (*funct)(Matrix);
  Matrix (*derivative)(Matrix);
	Matrix b;
	Matrix w;

public:
	Layer() = default;

	Layer(unsigned n_connections, unsigned n_neurons, string act_f) {
    assert(act_f == "tanh" || act_f == "sigm" || act_f == "relu" || act_f == "softmax");

    this->act_f = act_f;

    if (act_f == "tanh") {
      this->funct = &Tanh;
      this->derivative = &TanhD;
    }

    if (act_f == "sigm") {
      this->funct = &Sigm;
      this->derivative = &SigmD;
    }

    if (act_f == "relu") {
      this->funct = &Relu;
      this->derivative = &ReluD;
    }

    if (act_f == "softmax") {
      this->funct = &SoftMax;
      this->derivative = &ReluD;
    }

		this->n_connections = n_connections;
		this->n_neurons = n_neurons;

		this->b = Matrix::Random(1, n_neurons);
		this->w = Matrix::Random(n_connections, n_neurons);

/*
 *    for (int i = 0; i < this->w.rows(); i++) {
 *      for (int j = 0; j < this->w.cols(); j++) {
 *        this->w(i, j) = abs(this->w(i, j));
 *      }
 *    }
 *
 *    for (int i = 0; i < this->b.rows(); i++) {
 *      for (int j = 0; j < this->b.cols(); j++) {
 *        this->b(i, j) = abs(this->b(i, j));
 *      }
 *    }
 */
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

Matrix MatrixSum(Matrix w, const Matrix& b) {
  for (int i = 0; i < w.rows(); i++) {
    for (int j = 0; j < w.cols(); j++) {
      w(i, j) += b(0, j);
    }
  }

  return w;
}

#endif //Layer_H
