#ifndef ErrorFunct_H
#define ErrorFunct_H

#include <iostream>

#include <eigen3/Eigen/Eigen>

using namespace std;

using Matrix = Eigen::MatrixXd;
using RowVector = Eigen::RowVectorXd;

double MSE(Matrix y_pred, RowVector y_real) {
	double result = 0;

	for (std::size_t i = 0; i < y_pred.size(); i++) {
		cout << y_pred(i) << endl;
		result += pow(y_pred(i, 0) - y_real[i], 2);
	}

	result /= y_pred.size();

	return result;
}

/*
 *double MSE_Derivate(RowVector y_pred, RowVector y_real) {
 *  return y_pred - y_pred;
 *}
 */

#endif //ErrorFunct_H
