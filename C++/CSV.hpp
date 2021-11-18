#ifndef CSV_H
#define CSV_H

#include <iostream>
#include <tuple>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include <eigen3/Eigen/Eigen>

using namespace std;

using Matrix = Eigen::MatrixXd;
using RowVector = Eigen::RowVectorXd;

using out_t = tuple<Matrix, RowVector>;

class CSV {
public:
	static out_t read(const string& filename) {
		fstream file;
		file.open(filename, ios::in);

		vector<RowVector*> data;
		vector<RowVector*> output;

		string line;
		string word;

		unsigned dimensions = -1;
		if (file.is_open()) {
			getline(file, line, '\n');

			stringstream ss(line);
			vector<double> cols;

			while (getline(ss, word, ',')) {
				dimensions += 1;
			}

			while (getline(file, line, '\n')) {
				data.push_back(new RowVector(1, dimensions));
				output.push_back(new RowVector(1, 1));

				stringstream ss(line);
				unsigned i = 0;

				while (getline(ss, word, ',')) {
					if (i == 0) {
						output.back()->coeffRef(i) = double(stof(&word[0]));
					} else {
						data.back()->coeffRef(i - 1) = double(stof(&word[0]));
					}

					i++;
				}
			}
		} else {
			cerr << "Can't open " << filename << endl;
		}

		file.close();
		Matrix x(data.size(), dimensions);
		RowVector y(data.size());

		for (int i = 0; i < data.size(); i++) {
			for (int j = 0; j < dimensions; j++) {
				x(i, j) = data[i]->coeffRef(j);
			}
		}

		for (int i = 0; i < output.size(); i++) {
			y.coeffRef(i) = output[i]->coeffRef(0);
		}

		return {x, y};
	}
};


#endif //CSV_H
