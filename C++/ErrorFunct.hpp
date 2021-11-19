#ifndef ErrorFunct_H
#define ErrorFunct_H

#include <iostream>

#include <eigen3/Eigen/Eigen>

using namespace std;

using Matrix = Eigen::MatrixXd;
using RowVector = Eigen::RowVectorXd;

RowVector MSE(Matrix y_pred, RowVector y_real, map<double, unsigned> mapper) {
	RowVector errors(y_pred.rows());

	for (int i = 0; i < y_pred.rows(); i++) {
		unsigned y_pos = mapper[y_real[i]];
		double mse = 0;

		for (int j = 0; j < y_pred.cols(); j++) {
			if (j == y_pos) {
				mse += pow(y_pred(i, j) - 1, 2);
			} else {
				mse += pow(y_pred(i, j), 2);
			}
		}

		mse /= y_pred.cols();

		errors[i] = mse;
	}

	return errors;
}

double MSE_Derivate(Matrix y_pred, RowVector y_real) {
	return 0;
	//return y_pred - y_pred;
}

#endif //ErrorFunct_H
