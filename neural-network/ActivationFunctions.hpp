#ifndef ActivationFunctions_H
#define ActivationFunctions_H

#include <cmath>

double Tanh(double x) {
	return tanh(x);
}

double TanhDerivative(double x) {
	double t = tanh(x);

	return 1 - t * t;
}

double Sigmoide(double x) {
	const double e = exp(1);
	return 1 / (1 + pow(e, x));
}

double SigmoideDerivate(double x) {
	const double e = exp(1);
	return e * (1 - e);
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

#endif //ActivationFunctions_H
