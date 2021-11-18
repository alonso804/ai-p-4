#ifndef ActFuncts_H
#define ActFuncts_H

#include <cmath>
#include <eigen3/Eigen/Eigen>

using Matrix = Eigen::MatrixXd;
using RowVector = Eigen::RowVectorXd;

double Tanh(double x) {
	return tanh(x);
}

double TanhDerivative(double x) {
	double t = tanh(x);

	return 1 - t * t;
}

double Sigmoide(double x) {
	const double e = exp(1);

	return 1 / (1 + pow(e, -x));
}

double SigmoideDerivate(double x) {
	const double funct = Sigmoide(x);

	return funct * (1 - funct);
}

double RELU(double x) {
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

#endif //ActFuncts_H
