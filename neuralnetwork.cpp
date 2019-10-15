#include "neuralnetwork.h"

#include <iostream>

#include "utils.h"

NeuralNetwork::NeuralNetwork()
	: mLayers(std::vector<unsigned int>({ 9, 4, 2 }))
{
	for (int i = 1; i < mLayers.size(); i++)
	{
		mWeights.push_back(2 * arma::randu<arma::mat>(mLayers[i-1], mLayers[i]) - 1);
	}

	for (auto matrix : mWeights)
	{
		for (int m = 0; m < matrix.n_rows; m++)
		{
			for (int n = 0; n < matrix.n_cols; n++)
			{
				std::cout << matrix(m, n) << '\n';
			}
			std::cout << '\n';
		}
		std::cout << '\n' << '\n';
	}
}

NeuralNetwork::~NeuralNetwork() {}

void NeuralNetwork::forwardPropagate()
{

}
