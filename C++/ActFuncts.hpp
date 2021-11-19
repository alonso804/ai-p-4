#ifndef ActFuncts_H
#define ActFuncts_H

#include <cmath>
#include <iostream>
#include <eigen3/Eigen/Eigen>

using namespace std;

using Matrix = Eigen::MatrixXd;
using RowVector = Eigen::RowVectorXd;

double TanhFunct(double x) {
	return tanh(x);
}

double TanhDerivative(double x) {
	double t = tanh(x);

	return 1 - t * t;
}

Matrix Tanh(Matrix x) {
	for (unsigned i = 0; i < x.rows(); i++) {
		for (unsigned j = 0; j < x.cols(); j++) {
			x(i, j) = TanhFunct(x(i, j));
		}
	}

	return x;
}

Matrix TanhD(Matrix x) {
	for (unsigned i = 0; i < x.rows(); i++) {
		for (unsigned j = 0; j < x.cols(); j++) {
			x(i, j) = TanhDerivative(x(i, j));
		}
	}

	return x;
}

double SigmoideFunct(double x) {
	const double e = exp(1);

	return 1 / (1 + pow(e, -x));
}

double SigmoideDerivate(double x) {
	const double funct = SigmoideFunct(x);

	return funct * (1 - funct);
}

Matrix Sigm(Matrix x) {
	for (unsigned i = 0; i < x.rows(); i++) {
		for (unsigned j = 0; j < x.cols(); j++) {
			x(i, j) = SigmoideFunct(x(i, j));
		}
	}

	return x;
}

Matrix SigmD(Matrix x) {
	for (unsigned i = 0; i < x.rows(); i++) {
		for (unsigned j = 0; j < x.cols(); j++) {
			x(i, j) = SigmoideDerivate(x(i, j));
		}
	}

	return x;
}

double RELUFunct(double x) {
	if (x < 0) {
		return 0;
	}

	return x;
}

double RELUDerivate(double x) {
	if (x < 0) {
		return 0;
	}

	return 1;
}

Matrix Relu(Matrix x) {
	for (unsigned i = 0; i < x.rows(); i++) {
		for (unsigned j = 0; j < x.cols(); j++) {
			x(i, j) = RELUFunct(x(i, j));
		}
	}

	return x;
}

Matrix ReluD(Matrix x) {
	for (unsigned i = 0; i < x.rows(); i++) {
		for (unsigned j = 0; j < x.cols(); j++) {
			x(i, j) = RELUDerivate(x(i, j));
		}
	}

	return x;
}

Matrix SoftMax(Matrix z) {
	const double e = exp(1);
	std::cout << "Ultima capa\n";

	for (int i = 0; i < z.rows(); i++) {
		double total = 0;

		for (int j = 0; j < z.cols(); j++) {
			total += pow(e, z(i, j));
		}

		for (int j = 0; j < z.cols(); j++) {
			z(i, j) = pow(e, z(i, j)) / total;
		}
	}

	return z;
}

#endif //ActFuncts_H
