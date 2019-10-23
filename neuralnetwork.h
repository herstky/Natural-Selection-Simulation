#pragma once

#include <QtCore>

#include <vector>
#include <armadillo>

class Simulation;
class Organism;

class NeuralNetwork
{
public:
	friend Simulation;
	friend Organism;

	NeuralNetwork();
	NeuralNetwork(std::vector<int> pLayers);
	NeuralNetwork(std::vector<int> pLayers, std::vector<arma::mat> pWeights);

	arma::mat forwardPropagate(arma::mat input);
	static NeuralNetwork crossoverWeights(const NeuralNetwork& pFirst, const NeuralNetwork& pSecond);
	static NeuralNetwork crossoverBasisWeights(const NeuralNetwork& pFirst, const NeuralNetwork& pSecond);
	static NeuralNetwork mutateWeights(const NeuralNetwork& pNeuralNetwork);
	static NeuralNetwork mutateBasisWeights(const NeuralNetwork& pNeuralNetwork);
	
private:
	std::vector<int> mLayers;
	std::vector<arma::mat> mWeights;
	static qreal mMutationChance;
	static qreal mSmallVarianceMagnitude;
	static qreal mLargeVarianceMagnitude;
	static qreal mLargeVarianceChance;

	void init();
};

