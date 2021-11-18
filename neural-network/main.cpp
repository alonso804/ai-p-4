#include "CSV.hpp"
#include "NeuralNetwork.hpp"

int main(int argc, char *argv[]) {
	//auto [x, y] = CSV::read("../data/train_normalize.csv");
	auto [x, y] = CSV::read("../data/test_normalize.csv");
	vector<unsigned> topology;
	unsigned dimensions = (*x[0]).size();
	topology.push_back(dimensions);
	topology.push_back(dimensions / 2);
	topology.push_back(dimensions / 4);
	topology.push_back(24);

	NeuralNetwork nn(topology, "tanh");
	nn.fit(x, y);

	return 0;
}
