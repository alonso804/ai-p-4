#include "CSV.hpp"
#include "NeuralNetwork.hpp"
#include "Helpers.hpp"

int main(int argc, char *argv[]) {
  //const string act_f = "sigm";
	//const string act_f = "tanh";
	const string act_f = "relu";
	//auto [x, y] = CSV::read("../data/train_normalize.csv");
	auto [x, y] = CSV::read("../data/test_normalize.csv");

	const unsigned dimensions = x.cols();
	map<double, unsigned> output_mapper = countUnique(y);

	Layers layers = Layer::create({
		make_pair(dimensions, act_f),
		make_pair(50, act_f),
		make_pair(50, "softmax"),
		make_pair(output_mapper.size(), ""),
	});

/*
 *  auto [x, y] = CSV::read("../data/circle.csv");
 *  Mapper output_mapper = countUnique(y);
 *
 *  Layers layers = Layer::create({
 *    make_pair(2, act_f),
 *    make_pair(4, act_f),
 *    make_pair(8, act_f),
 *    make_pair(1, "")
 *  });
 */

	NeuralNetwork nn(layers, "mse", 10, 0.0001);
	nn.fit(x, y, output_mapper);
	
	return 0;
}
