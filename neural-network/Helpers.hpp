#ifndef Helpers_H
#define Helpers_H

#include "Headers.hpp"

Mapper countUnique(RowVector y) {
	set<double> uniques;

	for (int i = 0; i < y.size(); i++) {
		uniques.insert(y.coeffRef(i));
	}

	unsigned i = 0;

	Mapper mapper;

	for (const auto& u : uniques) {
		mapper[u] = i++;
	}

	return mapper;
}

void shape(const Matrix& x) {
  cout << "(" << x.rows() << ", " << x.cols() << ")" << endl;
}

void shape(const RowVector& x) {
  cout << "(" << x.size() << ", " << ")" << endl;
}

Matrix abs(Matrix x) {
	for (int i = 0; i < x.rows(); i++) {
		for (int j = 0; j < x.cols(); j++) {
			x(i, j) = abs(x(i, j));
		}
	}

	return x;
}

Matrix MatrixSum(Matrix w, const Matrix& b) {
  for (int i = 0; i < w.rows(); i++) {
    for (int j = 0; j < w.cols(); j++) {
      w(i, j) += b(0, j);
    }
  }

  return w;
}

Matrix MatrixProd(Matrix matrix1, const Matrix& matrix2) {
  for (int i = 0; i < matrix1.rows(); i++) {
    for (int j = 0; j < matrix1.cols(); j++) {
      matrix1(i, j) *= matrix2(i, j);
    }
  }

  return matrix1;
}

Matrix MatrixProd(const double& d, Matrix x) {
  for (int i = 0; i < x.rows(); i++) {
    for (int j = 0; j < x.cols(); j++) {
      x(i, j) *= d;
    }
  }

  return x;
}

#endif //Helpers_H
