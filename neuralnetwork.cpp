#include "neuralnetwork.h"

#include <iostream>

#include "utils.h"

NeuralNetwork::NeuralNetwork()
	: mInputLayerSize(8),
	  mHiddenLayerSize(10),
	  mOutputLayerSize(2),
	  mTheta0(2 * arma::randu<arma::mat>(mInputLayerSize, mHiddenLayerSize) - 1),
	  mTheta1(2 * arma::randu<arma::mat>(mHiddenLayerSize, mOutputLayerSize) - 1) 
{
	for (int m = 0; m < mTheta0.n_rows; m++)
	{
		for (int n = 0; n < mTheta1.n_cols; n++)
		{
			std::cout << mTheta0(m, n) << '\n';
		}
	}
}

NeuralNetwork::~NeuralNetwork() {}

void NeuralNetwork::forwardPropagate()
{

}
