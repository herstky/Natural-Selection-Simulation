#pragma once

#include <vector>
#include <armadillo>

class NeuralNetwork
{
public:
	NeuralNetwork();
	~NeuralNetwork();

	void forwardPropagate(arma::mat input);
	
private:
	std::vector<unsigned int> mLayers;
	std::vector<arma::mat> mWeights;
};

