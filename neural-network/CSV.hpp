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

using Matrix = Eigen::MatrixXf;
using RowVector = Eigen::RowVectorXf;

using out_t = tuple<vector<RowVector*>, vector<RowVector*>>;

class CSV {
public:
	static out_t read(const string& filename) {
		fstream file;
		file.open(filename, ios::in);

		vector<RowVector*> data;
		vector<RowVector*> output;

		string line;
		string word;

		if (file.is_open()) {
			getline(file, line, '\n');

			stringstream ss(line);
			vector<double> cols;

			unsigned dimensions = -1;
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

		return {data, output};
	}
};


#endif //CSV_H
