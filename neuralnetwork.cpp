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

	//for (auto matrix : mWeights)
	//{
	//	for (int m = 0; m < matrix.n_rows; m++)
	//	{
	//		for (int n = 0; n < matrix.n_cols; n++)
	//		{
	//			std::cout << matrix(m, n) << '\n';
	//		}
	//		std::cout << '\n';
	//	}
	//	std::cout << '\n' << '\n';
	//}
	forwardPropagate(arma::mat{ 1, 3 });
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

	for (int m = 0; m < a.n_rows; m++)
	{
		for (int n = 0; n < a.n_cols; n++)
		{
			std::cout << a(m, n) << '\n';
		}
		std::cout << '\n';
	}
	std::cout << '\n' << '\n';

}
