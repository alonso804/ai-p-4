#ifndef ErrorFunct_H
#define ErrorFunct_H

#include "Headers.hpp"

double MSE(const Matrix& y_pred, const unsigned& y_idx) {
	double error = 0;

	for (int j = 0; j < y_pred.cols(); j++) {
		if (j == y_idx) {
			error += pow(y_pred(0, j) - 1, 2);
		} else {
			error += pow(y_pred(0, j), 2);
		}
	}

		error /= (2 * y_pred.cols());

	return error;
}

Matrix MSE_Derivate(Matrix y_pred, const unsigned& y_idx) {
	double error = 0;

	for (int j = 0; j < y_pred.cols(); j++) {
		if (j == y_idx) {
			y_pred(0, j) = y_pred(0, j) - 1;
		} else {
			y_pred(0, j) = y_pred(0, j);
		}

		y_pred(0, j) *= -1;
	}

	return y_pred;
}

/*
 *double MSE_Derivate(Matrix y_pred, const unsigned& y_idx) {
 *  double error = 0;
 *
 *  for (int j = 0; j < y_pred.cols(); j++) {
 *    if (j == y_idx) {
 *      error += y_pred(0, j) - 1;
 *    } else {
 *      error += y_pred(0, j);
 *    }
 *  }
 *
 *  error /= y_pred.cols();
 *
 *  return error;
 *}
 */

#endif //ErrorFunct_H
