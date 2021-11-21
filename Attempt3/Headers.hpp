#ifndef Headers_H
#define Headers_H

#include <iostream>
#include <tuple>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>

#include <eigen3/Eigen/Eigen>

#include "prettyprint.hpp"

#define deb(x) cout << #x << ": " << x << endl

using namespace std;

using Matrix = Eigen::MatrixXd;
using RowVector = Eigen::RowVectorXd;


class Layer;

using Layers = vector<Layer>;
using out_t = tuple<Matrix, RowVector>;
using Mapper = map<double, unsigned>;
using Charges = vector<Matrix>;

#endif //Headers_H
