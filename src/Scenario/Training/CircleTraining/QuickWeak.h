#pragma once

#include "Scenario/Training/CircleTraining/CircleTraining.h"

#include <utility>
#include <memory>
#include <vector>
#include <unordered_map>

#include <armadillo>

#include <QtGlobal>

#include "NeuralNetwork.h"
#include "Model/Entity/Organism/WeakCreature.h"

class Simulation;

// This training scenario uses weak creatures and a short generation duration while focusing the
// rewards on reaching the food. The goal of this scenario is to pressure the creatures to reach
// the food as fast as possible.
class QuickWeak : public CircleTraining
{
public:
	QuickWeak(Simulation* pSimulation, std::pair<NeuralNetwork, qreal> pBestNeuralNetwork);
	
	virtual std::shared_ptr<Organism> addCreature(QPointF pPos, NeuralNetwork pNeuralNetwork, QColor pGroupColor) override;
	virtual void endRound() override;
};
