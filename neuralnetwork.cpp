#include "neuralnetwork.h"

#include <QRandomGenerator>

#include <random>

#include "utils.h"

std::default_random_engine NeuralNetwork::mGenerator(std::chrono::system_clock::now().time_since_epoch().count());
std::normal_distribution<qreal> NeuralNetwork::mDistribution;
qreal NeuralNetwork::mMutationChance = 15;
qreal NeuralNetwork::mSmallVarianceMagnitude = 1;
qreal NeuralNetwork::mLargeVarianceMagnitude = 100;
qreal NeuralNetwork::mLargeVarianceChance = 0;
			
NeuralNetwork::NeuralNetwork()
{
	arma::arma_rng::set_seed_random();
	std::vector<int> layers{ 8, 40, 2 };
	for (unsigned int i = 1; i < layers.size(); i++)
	{
		mWeights.push_back(arma::randn<arma::mat>(layers[i - 1] + 1, layers[i]));
	}
}

NeuralNetwork::NeuralNetwork(std::vector<int> pLayers)
{
	arma::arma_rng::set_seed_random();
	for (unsigned int i = 1; i < pLayers.size(); i++)
	{
		mWeights.push_back(arma::randn<arma::mat>(pLayers[i - 1] + 1, pLayers[i]));
	}
}

NeuralNetwork::NeuralNetwork(std::vector<arma::mat> pWeights)
	: mWeights(pWeights) {}

arma::mat NeuralNetwork::forwardPropagate(arma::mat input)
{
	arma::mat a = input;
	for (int i = 0; i < mWeights.size() - 1; i++)
	{
		a = arma::join_rows(arma::mat{ 1 }, a);
		arma::mat z = a * mWeights[i];
		a = sigmoid(z);
	}
	return a;
}

qreal NeuralNetwork::randn()
{
	return mDistribution(mGenerator);
}

NeuralNetwork NeuralNetwork::crossoverWeights(const NeuralNetwork& pFirst, const NeuralNetwork& pSecond)
{
	NeuralNetwork nn(pFirst.mWeights);
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
	NeuralNetwork nn(pFirst.mWeights);
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
	NeuralNetwork nn(pNeuralNetwork.mWeights);
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
						delta = randn() * mLargeVarianceMagnitude;
					else
						delta = randn() * mSmallVarianceMagnitude;
					nn.mWeights[i].at(j, k) += delta;
				}
			}
		}
	}
	return nn;
}

NeuralNetwork NeuralNetwork::mutateBasisWeights(const NeuralNetwork& pNeuralNetwork)
{
	NeuralNetwork nn(pNeuralNetwork.mWeights);
	for (int i = 0; i < nn.mWeights.size(); i++)
	{
		for (int k = 0; k < nn.mWeights[i].n_cols; k++)
		{
			if (QRandomGenerator::global()->bounded(100) < mMutationChance)
			{
				qreal delta;
				if (QRandomGenerator::global()->bounded(100.0) < mLargeVarianceChance)
					delta = randn() * mLargeVarianceMagnitude;
				else
					delta = randn() * mSmallVarianceMagnitude;
				nn.mWeights[i].at(0, k) += delta;
			}
		}
	}
	return nn;
}
