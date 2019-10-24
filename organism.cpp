#include "organism.h"

#include <algorithm>

#include <QtMath>
#include <QRandomGenerator>

#include "simulation.h"
#include "constants.h"
#include "view.h"
#include "food.h"

// TODO: consider diminishing returns for certain rewards

qreal Organism::mStarvationPenalty = 1; // 1
qreal Organism::mOutOfBoundsPenalty = 0; // 1
qreal Organism::mNoScentsPenalty = 0.1; // 0.1
qreal Organism::mFoodReward = 150; // 100
qreal Organism::mScentReward = 0.25; // 1
qreal Organism::mScentIncreaseReward = 100;
qreal Organism::mScentDecreasePenalty = 1000;

Organism::Organism()
	: mBrain(NeuralNetwork()),
	  mMass(0.0005),
	  mDensity(WATER_DENSITY),
	  mMaxSpeed(.01),
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
	  mScentThreshhold(0.02),
	  mEnergyLevel(1e-7),
	  mEnergyCapacity(1e-6),
	  mEnergySpent(0),
	  mHasEaten(false),
	  mScore(0),
	  mPrevScentSum(0) {}

Organism::Organism(const QPointF& pPosition)
    : Organism()
{
	mColor = Qt::red;
	mX = pPosition.x() / SCALE_FACTOR - width() / 2.0;
	mY = pPosition.y() / SCALE_FACTOR - height() / 2.0;
}

Organism::Organism(const Simulation& pSimulation, NeuralNetwork pBrain)
	: Organism()
{
	mBrain = pBrain;
	mColor = Qt::red;
	mX = QRandomGenerator::global()->bounded(pSimulation.boardView().width() - widthP()) / SCALE_FACTOR;
	mY = QRandomGenerator::global()->bounded(pSimulation.boardView().height() - heightP()) / SCALE_FACTOR;
}

Organism::Organism(const QPointF& pPosition, NeuralNetwork pBrain)
	: Organism(pPosition)
{
	mColor = Qt::red;
	mBrain = pBrain;
}

Organism::Organism(const QPointF& pPosition, NeuralNetwork pBrain, QColor pColor)
	: Organism(pPosition)
{
	mBrain = pBrain;
	mColor = pColor;
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

	if (!mHasEaten)
		mScore -= mStarvationPenalty * pSimulation.M_TICK_DURATION / 1000.0;

    expendEnergy(pSimulation);

	setX(x() + dx);
	setY(y() + dy);

	qreal x = mView->x();
	qreal y = mView->y();
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

void Organism::init(Simulation& pSimulation) 
{
	switch (pSimulation.mMode)
	{
		case Simulation::Mode::simulate:
		{
			break;
		}
		case Simulation::Mode::train:
		{
			break;
		}
		default:
		{
			break;
		}
	}
}

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

void Organism::expendEnergy(const Simulation& pSimulation)
{
    qreal drag = 1.0 / 2.0 * SPHERE_WATER_DRAG_COEFFICIENT * WATER_DENSITY * M_PI * pow((diameter() / 2), 2) * pow(mVelocity, 2);

	qreal force = std::max(mMass * acceleration(), 0.0) + drag;
    qreal work = force * mDeltaDistance;

	mInitialTime = QTime::currentTime();
	mInitialVelocity = mVelocity;

	switch (pSimulation.mMode)
	{
		case Simulation::Mode::simulate:
		{
			mEnergyLevel -= work;
			if (mEnergyLevel <= 0)
				die(pSimulation);
			break;
		}
		case Simulation::Mode::train:
		{
			mEnergySpent += work;
			break;
		}
		default:
		{
			break;
		}
	}
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
	switch (pSimulation.mMode)
	{
		case Simulation::Mode::simulate:
		{
			if (pOther.getType() == Entity::Type::prey)
				eat(pSimulation, pOther);
			break;
		}
		case Simulation::Mode::train:
		{
			//std::cout << "coords: (" << coords(pSimulation).first << ", " << coords(pSimulation).second << ")" << std::endl;
			arma::mat scents = smell(pSimulation);
			for (int i = 0; i < scents.n_rows; i++)
			{
				for (int j = 0; j < scents.n_cols; j++)
				{
					//std::cout << "(" << i << ", " << j << "): " << scents.at(i, j) << std::endl;
				}
			}

			if (!mHasEaten)
			{
				mHasEaten = true;
				mScore += mFoodReward;
				pSimulation.mScore += 1;
			}

			break;
		}
		default:
		{
			break;
		}
	}
}

arma::mat Organism::smell(Simulation& pSimulation)
{
	int divisions = mBrain.mLayers[0];
	arma::mat scents = arma::zeros(1, divisions);
	qreal sum = 0;

	for (int i = 0; i < divisions; i++)
	{
		qreal angle = i * 2.0 * M_PI / divisions;
		for (auto food : pSimulation.mFoodSet)
		{
			qreal intensity;
			if (sqrt(pow(x() - food->x(), 2) + pow(y() - food->y(), 2)) < mSmellRadius)
			{
				intensity = Food::M_SCENT_STRENGTH;
				scents.at(0, i) += intensity;
			}
			else
			{
				qreal scentPositionX = x() + mSmellRadius * cos(angle);
				qreal scentPositionY = y() - mSmellRadius * sin(angle); // invert because y decreases in the up direction
				qreal dx = scentPositionX - food->x();
				qreal dy = scentPositionY - food->y();
				bool validPosition = !(scentPositionX >= pSimulation.board().width()
					|| scentPositionX < 0
					|| scentPositionY >= pSimulation.board().height()
					|| scentPositionY < 0);
				qreal distance = std::sqrt(pow(dx, 2) + pow(dy, 2));
				if (distance == 0.0)
					intensity = Food::M_SCENT_STRENGTH;
				else
					intensity = std::min(Food::M_SCENT_DIFFUSIVITY * Food::M_SCENT_STRENGTH / distance, Food::M_SCENT_STRENGTH);
				if (validPosition && intensity >= mScentThreshhold)
					scents.at(0, i) += intensity;
				else
					scents.at(0, i) = 0;
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

	// normalize scent matrix
	qreal maxScent = 0;
	for (int i = 0; i < scents.n_rows; i++)
	{
		for (int j = 0; j < scents.n_cols; j++)
		{
			maxScent = std::max(maxScent, scents.at(i, j));
		}
	}
	if (maxScent > 0)
	{
		for (int i = 0; i < scents.n_rows; i++)
		{
			for (int j = 0; j < scents.n_cols; j++)
			{
				scents.at(i, j) = scents.at(i, j) / maxScent;
			}
		}
	}

	arma::mat decision = mBrain.forwardPropagate(scents);
	mVelocity = mMaxSpeed * decision(0, 0);
	mDirection = 2 * M_PI * decision(0, 1);
}

void Organism::eat(const Simulation& pSimulation, Entity& pOther)
{
	mEnergyLevel += pOther.getMass() * pOther.getEnergyContent();
	pOther.die(pSimulation);
}
