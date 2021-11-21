#ifndef ActFuncts_H
#define ActFuncts_H

#include "Headers.hpp"

Matrix TanhF(Matrix z) {
	for (unsigned i = 0; i < z.rows(); i++) {
		for (unsigned j = 0; j < z.cols(); j++) {
			z(i, j) = tanh(z(i, j));
		}
	}

	return z;
}

Matrix TanhD(Matrix a) {
	for (unsigned i = 0; i < a.rows(); i++) {
		for (unsigned j = 0; j < a.cols(); j++) {
			a(i, j) = 1 - a(i, j) * a(i, j);
		}
	}

	return a;
}

Matrix SigmF(Matrix z) {
	const double e = exp(1);

	for (unsigned i = 0; i < z.rows(); i++) {
		for (unsigned j = 0; j < z.cols(); j++) {
			z(i, j) = 1 / (1 + pow(e, -z(i, j)));
		}
	}

	return z;
}

Matrix SigmD(Matrix a) {
	for (unsigned i = 0; i < a.rows(); i++) {
		for (unsigned j = 0; j < a.cols(); j++) {
			a(i, j) = a(i, j) * (1 - a(i, j));
		}
	}

	return a;
}

Matrix ReluF(Matrix z) {
	for (unsigned i = 0; i < z.rows(); i++) {
		for (unsigned j = 0; j < z.cols(); j++) {
			z(i, j) = z(i, j) < 0 ? 0 : z(i, j);
		}
	}

	return z;
}

Matrix ReluD(Matrix a) {
	for (unsigned i = 0; i < a.rows(); i++) {
		for (unsigned j = 0; j < a.cols(); j++) {
			a(i, j) = a(i, j) < 0 ? 0 : 1;
		}
	}

	return a;
}

Matrix SoftMaxF(Matrix z) {
	const double e = exp(1);

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

Matrix SoftMaxD(Matrix a) {
	for (int i = 0; i < a.rows(); i++) {
		for (int j = 0; j < a.cols(); j++) {
			a(i, j) = a(i, j) * (1 - a(i, j));
		}

	}

	return a;
}

#endif //ActFuncts_H
