#include "neuralnetwork.h"

#include <QRandomGenerator>

#include <iostream>

#include "utils.h"

qreal NeuralNetwork::mMutationChance = 10;
qreal NeuralNetwork::mSmallVarianceMagnitude = 1;
qreal NeuralNetwork::mLargeVarianceMagnitude = 20;
qreal NeuralNetwork::mLargeVarianceChance = 2;

NeuralNetwork::NeuralNetwork()
	: mLayers(std::vector<int>{ 20, 40, 2 })
{
	for (unsigned int i = 1; i < mLayers.size(); i++)
	{
		mWeights.push_back(2 * arma::randu<arma::mat>(mLayers[i - 1] + 1, mLayers[i]) - 1);
	}
	mutateBasisWeights(*this);
	mutateWeights(*this);
	init();
}

NeuralNetwork::NeuralNetwork(std::vector<int> pLayers)
	: mLayers(pLayers)
{
	for (unsigned int i = 1; i < mLayers.size(); i++)
	{
		mWeights.push_back(2 * arma::randu<arma::mat>(mLayers[i - 1] + 1, mLayers[i]) - 1);
	}
	mutateBasisWeights(*this);
	mutateWeights(*this);
	init();
}

NeuralNetwork::NeuralNetwork(std::vector<int> pLayers, std::vector<arma::mat> pWeights)
	: mLayers(pLayers), mWeights(pWeights)
{
	init();
}

arma::mat NeuralNetwork::forwardPropagate(arma::mat input)
{
	arma::mat a = input;
	for (int i = 0; i < mLayers.size() - 1; i++)
	{
		a = arma::join_rows(arma::mat{ 1 }, a);
		arma::mat z = a * mWeights[i];
		a = sigmoid(z);
	}
	return a;
}

void NeuralNetwork::init() {}

NeuralNetwork NeuralNetwork::crossoverWeights(const NeuralNetwork& pFirst, const NeuralNetwork& pSecond)
{
	NeuralNetwork nn(pFirst.mLayers, pFirst.mWeights);
	for (int i = 0; i < nn.mWeights.size(); i++)
	{
		for (int j = 1; j < nn.mWeights[i].n_rows; j++) // skip row of basis weights
		{
			for (int k = 0; k < nn.mWeights[i].n_cols; k++)
			{
				if (QRandomGenerator::global()->bounded(2))
				{
					nn.mWeights[i].at(j, k) = pSecond.mWeights[i].at(j, k);
				}
			}
		}
	}
	return nn;
}

NeuralNetwork NeuralNetwork::crossoverBasisWeights(const NeuralNetwork& pFirst, const NeuralNetwork& pSecond)
{
	NeuralNetwork nn(pFirst.mLayers, pFirst.mWeights);
	for (int i = 0; i < nn.mWeights.size(); i++)
	{
		for (int k = 0; k < nn.mWeights[i].n_cols; k++)
		{
			if (QRandomGenerator::global()->bounded(2))
			{
				nn.mWeights[i].at(0, k) = pSecond.mWeights[i].at(0, k);
			}
		}
	}
	return nn;
}

NeuralNetwork NeuralNetwork::mutateWeights(const NeuralNetwork& pNeuralNetwork)
{
	NeuralNetwork nn(pNeuralNetwork.mLayers, pNeuralNetwork.mWeights);
	for (int i = 0; i < nn.mWeights.size(); i++)
	{
		for (int j = 1; j < nn.mWeights[i].n_rows; j++) // skip row of basis weights
		{
			for (int k = 0; k < nn.mWeights[i].n_cols; k++)
			{
				if (QRandomGenerator::global()->bounded(100) < mMutationChance)
				{
					qreal delta;
					if (QRandomGenerator::global()->bounded(100.0) < mLargeVarianceChance)
						delta = (2 * QRandomGenerator::global()->bounded(1) - 1) * mLargeVarianceMagnitude;
					else
						delta = (2 * QRandomGenerator::global()->bounded(1) - 1) * mSmallVarianceMagnitude;
					nn.mWeights[i].at(j, k) += delta;
				}
			}
		}
	}
	return nn;
}

NeuralNetwork NeuralNetwork::mutateBasisWeights(const NeuralNetwork& pNeuralNetwork)
{
	NeuralNetwork nn(pNeuralNetwork.mLayers, pNeuralNetwork.mWeights);
	for (int i = 0; i < nn.mWeights.size(); i++)
	{
		for (int k = 0; k < nn.mWeights[i].n_cols; k++)
		{
			if (QRandomGenerator::global()->bounded(100) < mMutationChance)
			{
				qreal delta;
				if (QRandomGenerator::global()->bounded(100.0) < mLargeVarianceChance)
					delta = (2 * QRandomGenerator::global()->bounded(1) - 1) * mLargeVarianceMagnitude;
				else
					delta = (2 * QRandomGenerator::global()->bounded(1) - 1) * mSmallVarianceMagnitude;
				nn.mWeights[i].at(0, k) += delta;
			}
		}
	}
	return nn;
}
