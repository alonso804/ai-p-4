#include "CSV.hpp"
#include "NeuralNetwork.hpp"

#include "prettyprint.hpp"

map<double, unsigned> countUnique(RowVector y) {
	set<double> uniques;

	for (int i = 0; i < y.size(); i++) {
		uniques.insert(y.coeffRef(i));
	}

	unsigned i = 0;

	map<double, unsigned> mapper;

	for (const auto& u : uniques) {
		mapper[u] = i++;
	}

	return mapper;
}

Layers createLayers(initializer_list<pair<unsigned, string>> topology) {
	Layers layers;

	for (auto it = topology.begin(); it != topology.end() - 1; it++) {
		layers.push_back(Layer((*it).first, (*(it + 1)).first, (*it).second));
	}

	return layers;
}

int main(int argc, char *argv[]) {
  const string act_f = "sigm";
  //const string act_f = "tanh";
  //const string act_f = "relu";
	auto [x, y] = CSV::read("../data/test_normalize.csv");
	//auto [x, y] = CSV::read("../data/train_normalize.csv");

	const unsigned dimensions = x.cols();
	const map<double, unsigned> output_mapper = countUnique(y);

	auto layers = createLayers({
		make_pair(dimensions, act_f),
		make_pair(dimensions / 2, "softmax"),
		make_pair(output_mapper.size(), ""),
	});

/*
 *  auto [x, y] = CSV::read("../data/circle.csv");
 *  const map<double, unsigned> output_mapper = countUnique(y);
 *
 *  auto layers = createLayers({
 *    make_pair(2, act_f),
 *    make_pair(4, act_f),
 *    make_pair(8, act_f),
 *    make_pair(16, act_f),
 *    make_pair(8, act_f),
 *    make_pair(4, act_f),
 *    make_pair(1, act_f)
 *  });
 */
	
	NeuralNetwork nn(layers, "mse");
	nn.fit(x, y, output_mapper);
	
	return 0;
}
