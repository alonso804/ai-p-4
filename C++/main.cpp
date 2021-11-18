#include "CSV.hpp"
#include "NeuralNetwork.hpp"
#include <cstddef>
#include <initializer_list>
#include <unordered_set>
#include <utility>

unsigned countUnique(RowVector y) {
	unordered_set<double> uniques;

	for (int i = 0; i < y.size(); i++) {
		uniques.insert(y.coeffRef(i));
	}

	return uniques.size();
}

Layers createLayers(initializer_list<pair<unsigned, string>> topology) {
	Layers layers;

	for (auto it = topology.begin(); it != topology.end() - 1; it++) {
		layers.push_back(Layer((*it).first, (*(it + 1)).first, (*it).second));
	}

	return layers;
}

int main(int argc, char *argv[]) {
	//auto [x, y] = CSV::read("../data/train_normalize.csv");
	//auto [x, y] = CSV::read("../data/test_normalize.csv");
	auto [x, y] = CSV::read("../data/circle.csv");

	const string act_f = "tanh";
	const unsigned dimensions = x.cols();
	const unsigned n_output = countUnique(y);

	/*
	 *cout << "dimensions: " << dimensions << endl;
	 *cout << "n_outputs: " <<  n_output << endl;
	 */

	/*
	 *auto layers = createLayers({
	 *  make_pair(dimensions, act_f),
	 *  make_pair(dimensions / 2, act_f),
	 *  make_pair(dimensions / 2, act_f),
	 *  make_pair(n_output, act_f),
	 *});
	 */

	auto layers = createLayers({
		make_pair(2, act_f),
		make_pair(4, act_f),
		make_pair(8, act_f),
		make_pair(16, act_f),
		make_pair(8, act_f),
		make_pair(4, act_f),
		make_pair(1, act_f)
	});
	
	NeuralNetwork nn(layers, "mse");
	nn.fit(x, y);
	
	return 0;
}
