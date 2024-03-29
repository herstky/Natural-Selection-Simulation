#include "Scenario/Training/Training.h"

Training::Training(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork)
	: Scenario(pSimulation),
	  mBestNeuralNetwork(pBestNeuralNetwork),
	  mNextNeuralNetwork(mBestNeuralNetwork.first) {}

NeuralNetwork Training::generateNeuralNetwork()
{
	NeuralNetwork neuralNetwork = NeuralNetwork::mutateWeights(mNextNeuralNetwork);
	return NeuralNetwork::mutateBasisWeights(neuralNetwork);
}