#include "CSV.hpp"

int main(int argc, char *argv[]) {
	auto [x, y] = CSV::read("../data/train_normalize.csv");
	
	return 0;
}
