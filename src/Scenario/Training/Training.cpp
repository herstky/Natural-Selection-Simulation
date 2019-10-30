#include "Scenario/Training/Training.h"

Training::Training(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork)
	: Scenario(pSimulation),
	  mBestNeuralNetwork(pBestNeuralNetwork),
	  mNextNeuralNetwork(mBestNeuralNetwork.first) {}

NeuralNetwork Training::generateNeuralNetwork()
{
	return NeuralNetwork::mutateWeights(mNextNeuralNetwork);
}