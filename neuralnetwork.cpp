#include "neuralnetwork.h"

#include <iostream>

#include "utils.h"

NeuralNetwork::NeuralNetwork()
	: mLayers(std::vector<unsigned int>({ 4, 4, 2 }))
{
	for (unsigned int i = 1; i < mLayers.size(); i++)
	{
		mWeights.push_back(2 * arma::randu<arma::mat>(mLayers[i-1] + 1, mLayers[i]) - 1);
	}
}

NeuralNetwork::~NeuralNetwork() {}

void NeuralNetwork::forwardPropagate(arma::mat input)
{
	arma::mat a = input;
	for (int i = 0; i < mLayers.size() - 1; i++)
	{
		a = arma::join_rows(arma::mat{ 1 }, a);
		arma::mat z = a * mWeights[i];
		a = sigmoid(z);
	}
}
