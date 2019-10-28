#include "Organism.h"

#include <algorithm>
#include <limits>
#include <filesystem>

#include <QtMath>
#include <QRandomGenerator>

#include <armadillo>

#include "Simulation.h"
#include "Scenario.h"
#include "constants.h"
#include "View.h"
#include "Food.h"

qreal Organism::mStarvationPenalty = 15; // 5
qreal Organism::mOutOfBoundsPenalty = 0; // 0
qreal Organism::mNoScentsPenalty = 0; // 0
qreal Organism::mEnergyExpenditurePenalty = 0;
qreal Organism::mFoodReward = 400; // 200
qreal Organism::mScentReward = 0; // 1
qreal Organism::mScentIncreaseReward = 10; // 10
qreal Organism::mScentDecreasePenalty = 20; // 20

Organism::Organism()
	: mBrain(NeuralNetwork()),
	  mMass(0.0005),
	  mDensity(WATER_DENSITY),
	  mMaxSpeed(.005),
	  mVelocity(0.0),
	  mInitialVelocity(mVelocity),
	  mInitialTime(QTime::currentTime()),
	  mDeltaDistance(0),
	  mDirection(0.0),
	  mReplicationChance(0),
	  mMutationChance(0),
	  mDeathChance(0),
	  mScentStrength(1.0),
	  mSmellRadius(diameter() / 2.0),
	  mScentThreshhold(0.002),
	  mEnergyLevel(5e-7),
	  mEnergyCapacity(5e-7),
	  mEnergySpent(0),
	  mHasEaten(false),
	  mScore(0),
	  mPrevScentSum(0) {}

Organism::Organism(const QPointF& pPosition)
    : Organism()
{
	mColor = QColor(QRandomGenerator::global()->bounded(255), 
		QRandomGenerator::global()->bounded(255), 
		QRandomGenerator::global()->bounded(255));
	mX = pPosition.x() / SCALE_FACTOR - width() / 2.0;
	mY = pPosition.y() / SCALE_FACTOR - height() / 2.0;
}

Organism::Organism(const Simulation& pSimulation, NeuralNetwork pBrain)
	: Organism()
{
	mBrain = pBrain;
	mColor = QColor(QRandomGenerator::global()->bounded(255),
		QRandomGenerator::global()->bounded(255),
		QRandomGenerator::global()->bounded(255));
	mX = QRandomGenerator::global()->bounded(pSimulation.boardView().width() - widthP()) / SCALE_FACTOR;
	mY = QRandomGenerator::global()->bounded(pSimulation.boardView().height() - heightP()) / SCALE_FACTOR;
}

Organism::Organism(const QPointF& pPosition, NeuralNetwork pBrain)
	: Organism(pPosition)
{
	mColor = QColor(QRandomGenerator::global()->bounded(255),
		QRandomGenerator::global()->bounded(255),
		QRandomGenerator::global()->bounded(255));
	mBrain = pBrain;
}

Organism::Organism(const QPointF& pPosition, NeuralNetwork pBrain, QColor pColor)
	: Organism(pPosition)
{
	mBrain = pBrain;
	mColor = pColor;
}

Organism::~Organism() {}

Organism::Organism(const Organism& pOther)
	: Organism() {}
	
Organism& Organism::operator=(const Organism& pOther)
{
	return *this;
}

void Organism::die(const Simulation& pSimulation)
{
	Model::die(pSimulation);
}

void Organism::move(const Simulation& pSimulation)
{
	if (mStatus == Model::Status::dead)
		return;

    qreal dx = mVelocity * cos(mDirection);
    qreal dy = mVelocity * sin(mDirection);

	if (x() + dx + width() > pSimulation.mBoard.width() || x() + dx < 0)
	{
		mDirection = M_PI - mDirection;
		mScore -= mOutOfBoundsPenalty * pSimulation.M_TICK_DURATION / 1000.0;
	}
	if (y() + dy + height() > pSimulation.mBoard.height() || y() + dy < 0)
	{
		mDirection = 2 * M_PI - mDirection;
		mScore -= mOutOfBoundsPenalty * pSimulation.M_TICK_DURATION / 1000.0;
	}

    dx = mVelocity * cos(mDirection);
    dy = mVelocity * sin(mDirection);
    mDeltaDistance = std::sqrt(pow(dx, 2) + pow(dy, 2));

    pSimulation.mScenario->expendEnergy(*this);

	setX(x() + dx);
	setY(y() + dy);
}

void Organism::simulate(Simulation& pSimulation)
{
	if (mStatus == Model::Status::dead)
		return;

	think(pSimulation);
}

void Organism::replicate(const Simulation& pSimulation) {}

const qreal Organism::volume() const
{
    return mMass / mDensity;
}

const qreal Organism::diameter() const
{
   return 2.0 * std::cbrt(3.0 * volume() / (4.0 * M_PI));
}

qreal Organism::deltaVelocity()
{
    return mVelocity - mInitialVelocity;
}

qreal Organism::deltaTime()
{
    return -1 * QTime::currentTime().msecsTo(mInitialTime) / 1000.0;
}

qreal Organism::acceleration()
{
    return deltaVelocity() / deltaTime();
}

void Organism::init(Simulation& pSimulation) {}

const qreal Organism::height() const
{
	return diameter();
}

void Organism::setHeight(qreal pHeight) {}

const qreal Organism::width() const
{
	return diameter();
}

void Organism::setWidth(qreal pWidth) {}

qreal& Organism::score()
{
	return mScore;
}

qreal& Organism::energyLevel()
{
	return mEnergyLevel;
}

qreal Organism::energyCapacity()
{
	return mEnergyCapacity;
}

qreal Organism::foodReward()
{
	return mFoodReward;
}


void Organism::expendEnergy(const Simulation& pSimulation)
{
    qreal drag = 1.0 / 2.0 * SPHERE_WATER_DRAG_COEFFICIENT * WATER_DENSITY * M_PI * pow((diameter() / 2), 2) * pow(mVelocity, 2);

	qreal force = std::max(mMass * acceleration(), 0.0) + drag;
    qreal work = force * mDeltaDistance;

	qreal basalMetabolicRate = 0.0001 * mMass * deltaTime();
	qreal energyExpenditure = work + basalMetabolicRate;

	mEnergySpent += energyExpenditure;
	mEnergyLevel -= energyExpenditure;
	mScore -= mEnergyExpenditurePenalty * energyExpenditure * pSimulation.M_TICK_DURATION / 1000.0;
	if (mEnergyLevel <= 0)
		pSimulation.mScenario->die(*this);
	mInitialTime = QTime::currentTime();
	mInitialVelocity = mVelocity;
}

QRectF Organism::hitbox()
{
	qreal scaledRadius = SCALE_FACTOR * diameter() / 2.0;
	QPointF topLeft = QPointF(centerP().x() + scaledRadius * cos(3.0 * M_PI / 4.0), 
		centerP().y() - scaledRadius * sin(3.0 * M_PI / 4.0));
	QPointF bottomRight = QPointF(centerP().x() + scaledRadius * cos(7.0 * M_PI / 4.0), 
		centerP().y() - scaledRadius * sin(7.0 * M_PI / 4.0));
	return QRectF(topLeft, bottomRight);
}

void Organism::collide(Simulation& pSimulation, Entity& pOther)
{
	if (pOther.getType() == Entity::Type::prey)
	{
		pSimulation.mScenario->eat(*this, pOther);
	}
}

arma::mat Organism::smell(Simulation& pSimulation)
{
	int divisions = mBrain.mWeights[0].n_rows - 1;
	arma::mat scents = arma::zeros(1, divisions);
	qreal sum = 0;

	for (int i = 0; i < divisions; i++)
	{
		qreal angle = i * 2.0 * M_PI / divisions;
		for (auto food : pSimulation.mFoodSet)
		{
			qreal intensity;
			if (sqrt(pow(center().x() - food->center().x(), 2) + pow(center().y() - food->center().y(), 2)) < mSmellRadius)
			{
				intensity = Food::M_SCENT_STRENGTH;
				scents.at(0, i) += intensity;
			}
			else
			{
				qreal scentPositionX = center().x() + mSmellRadius * cos(angle);
				qreal scentPositionY = center().y() - mSmellRadius * sin(angle); // invert because y decreases in the up direction
				qreal dx = scentPositionX - food->center().x();
				qreal dy = scentPositionY - food->center().y();
				bool validPosition = !(scentPositionX >= pSimulation.board().widthP()
					|| scentPositionX < 0
					|| scentPositionY >= pSimulation.board().heightP()
					|| scentPositionY < 0);
				qreal distance = std::sqrt(pow(dx, 2) + pow(dy, 2));
				if (distance == 0.0)
					intensity = Food::M_SCENT_STRENGTH;
				else
					intensity = std::min(Food::M_SCENT_DIFFUSIVITY * Food::M_SCENT_STRENGTH / distance, Food::M_SCENT_STRENGTH);

				if (!validPosition)
				{
					scents.at(0, i) = -1;
					mScore -= mOutOfBoundsPenalty * pSimulation.M_TICK_DURATION / 1000.0;
				}
				else if (intensity >= mScentThreshhold)
				{
					scents.at(0, i) += intensity;
				}
			}

			sum += scents.at(0, i);
		}
	}
	qreal scentDelta = sum - mPrevScentSum;
	if (scentDelta > 0)
		mScore += mScentIncreaseReward * scentDelta * pSimulation.M_TICK_DURATION / 1000.0;
	else
		mScore += mScentDecreasePenalty * scentDelta * pSimulation.M_TICK_DURATION / 1000.0;
	mPrevScentSum = sum;

	mScore += mScentReward * sum * pSimulation.M_TICK_DURATION / 1000.0;
	return scents;
}

void Organism::think(Simulation& pSimulation)
{
	arma::mat scents = smell(pSimulation);

	// normalize and mean-center scent matrix
	qreal maxScent = -std::numeric_limits<qreal>::infinity();
	qreal minScent = std::numeric_limits<qreal>::infinity();
	for (int i = 0; i < scents.n_rows; i++)
	{
		for (int j = 0; j < scents.n_cols; j++)
		{
			maxScent = std::max(maxScent, scents.at(i, j));
			minScent = std::min(minScent, scents.at(i, j));
		}
	}
	for (int i = 0; i < scents.n_rows; i++)
	{
		for (int j = 0; j < scents.n_cols; j++)
		{
			if (maxScent - minScent == 0)
				scents.at(i, j) = 0;
			else
				scents.at(i, j) = (scents.at(i, j) - minScent) / (maxScent - minScent);
		}
	}

	arma::mat decision = mBrain.forwardPropagate(scents);
	mVelocity = mMaxSpeed * decision(0, 0);
	mDirection = 2 * M_PI * decision(0, 1);
}

void Organism::eat(Simulation& pSimulation, Entity& pOther)
{
	mScore += mFoodReward;
	pSimulation.scorePoint();
	
	mEnergyLevel += pOther.getMass() * pOther.getEnergyContent();
	mEnergyLevel = std::min(mEnergyLevel, mEnergyCapacity);
	pOther.die(pSimulation);
}

NeuralNetwork Organism::loadBrain()
{
	return NeuralNetwork();
}

NeuralNetwork Organism::loadBrain(std::string pPath)
{
	std::vector<arma::mat> weights;
	for (const auto& file : std::filesystem::directory_iterator(pPath))
	{
		arma::mat matrix;
		matrix.load(file.path().generic_string());
		weights.push_back(matrix);
	}
	return weights;
}