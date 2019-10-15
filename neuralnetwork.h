#pragma once

#include <armadillo>

class NeuralNetwork
{
public:
	NeuralNetwork();
	~NeuralNetwork();

	void forwardPropagate();

private:
	const unsigned int mInputLayerSize;
	const unsigned int mHiddenLayerSize;
	const unsigned int mOutputLayerSize;
	arma::mat mTheta0;
	arma::mat mTheta1;
};

