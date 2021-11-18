#include "CSV.hpp"
#include "NeuralNetwork.hpp"
#include <cstddef>
#include <initializer_list>
#include <unordered_set>
#include <utility>

unsigned countUnique(vector<RowVector*> y) {
	unordered_set<double> uniques;

	for (int i = 0; i < y.size(); i++) {
		uniques.insert(y[i]->coeffRef(0));
	}

	return uniques.size();
}

Topology createTopology(initializer_list<pair<unsigned, string>> topo) {
	Topology topology;

	for (auto it = topo.begin(); it != topo.end() - 1; it++) {
		topology.push_back(Layer((*it).first, (*(it + 1)).first, (*it).second));
	}

	return topology;
}

int main(int argc, char *argv[]) {
	//auto [x, y] = CSV::read("../data/train_normalize.csv");
	auto [x, y] = CSV::read("../data/test_normalize.csv");

	const string act_f = "tanh";
	const unsigned dimensions = (*x[0]).size();
	const unsigned n_output = countUnique(y);

	auto topology = createTopology({
		make_pair(dimensions, act_f),
		make_pair(dimensions / 2, act_f),
		make_pair(dimensions / 2, act_f),
		make_pair(n_output, act_f),
	});
	
	NeuralNetwork nn(x, y, topology, "mse");
	
	return 0;
}
