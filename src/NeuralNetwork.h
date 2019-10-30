#pragma once

#include <vector>
#include <chrono>
#include <random>

#include <QtCore>

#include <armadillo>

class Simulation;
class Organism;

class NeuralNetwork
{
public:
	friend class Simulation;
	friend class Organism;
	friend class QuickWeak;

	NeuralNetwork();
	NeuralNetwork(std::vector<int> pLayers);
	NeuralNetwork(std::vector<arma::mat> pWeights);

	arma::mat forwardPropagate(arma::mat input);
	static qreal randn();
	static NeuralNetwork crossoverWeights(const NeuralNetwork& pFirst, const NeuralNetwork& pSecond);
	static NeuralNetwork crossoverBasisWeights(const NeuralNetwork& pFirst, const NeuralNetwork& pSecond);
	static NeuralNetwork mutateWeights(const NeuralNetwork& pNeuralNetwork);
	static NeuralNetwork mutateBasisWeights(const NeuralNetwork& pNeuralNetwork);
	
	std::vector<arma::mat> weights();

	static qreal mMutationChance;
	static qreal mSmallVarianceMagnitude;
	static qreal mLargeVarianceMagnitude;
	static qreal mLargeVarianceChance;

private:
	std::vector<arma::mat> mWeights;
	static std::default_random_engine mGenerator;
	static std::normal_distribution<qreal> mDistribution;

};

