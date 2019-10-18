#pragma once

#include <vector>
#include <armadillo>

class NeuralNetwork
{
public:
	NeuralNetwork();
	NeuralNetwork(std::vector<int> pLayers);

	arma::mat forwardPropagate(arma::mat input);
	
private:
	std::vector<int> mLayers;
	std::vector<arma::mat> mWeights;

	void init();
};

