#include "organism.h"

#include <algorithm>

#include <QtMath>
#include <QRandomGenerator>

#include "simulation.h"
#include "constants.h"
#include "view.h"

Organism::Organism()
	: mBrain(NeuralNetwork(std::vector<int>{ 9, 4, 2 })),
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
	  mMass(0.0005),
	  mDensity(WATER_DENSITY),
	  mEnergyLevel(1e-7),
	  mEnergyCapacity(1e-6),
	  mEnergySpent(0),
	  mHasEaten(false),
	  mScore(0),
      mOutOfBoundsPenalty(0.001),
      mFoodReward(1),
      mScentReward(0.1) {}

Organism::Organism(const QPointF& pPosition)
    : Entity(pPosition),
	  mBrain(NeuralNetwork()),
	  mMaxSpeed(0.01),
      mVelocity(0.0),
      mInitialVelocity(mVelocity),
      mInitialTime(QTime::currentTime()),
      mDeltaDistance(0),
      mDirection(0.0),
      mReplicationChance(0),
      mMutationChance(0),
      mDeathChance(0),
	  mScentStrength(1.0),
      mMass(0.0005),
      mDensity(WATER_DENSITY),
      mEnergyLevel(1e-7),
      mEnergyCapacity(1e-6),
	  mEnergySpent(0),
	  mHasEaten(false),
	  mScore(0),
	  mOutOfBoundsPenalty(0.001),
	  mFoodReward(1),
	  mScentReward(0.1) 
{
	mX = pPosition.x() / SCALE_FACTOR - width() / 2.0;
	mY = pPosition.y() / SCALE_FACTOR - height() / 2.0;
}

Organism::Organism(const Simulation& pSimulation, NeuralNetwork pBrain)
	: Entity(),
	  mBrain(pBrain),
	  mMaxSpeed(.01),
	  mVelocity(0.0),
	  mInitialVelocity(mVelocity),
	  mInitialTime(QTime::currentTime()),
	  mDeltaDistance(0),
	  mDirection(QRandomGenerator::global()->bounded(2 * M_PI)),
	  mReplicationChance(0),
	  mMutationChance(0),
	  mDeathChance(0),
	  mScentStrength(1.0),
	  mMass(0.0005),
	  mDensity(WATER_DENSITY),
	  mEnergyLevel(1e-7),
	  mEnergyCapacity(1e-6),
	  mEnergySpent(0),
	  mHasEaten(false),
	  mScore(0),
	  mOutOfBoundsPenalty(0.001),
	  mFoodReward(1),
	  mScentReward(0.1)
{
	mX = QRandomGenerator::global()->bounded(pSimulation.boardView().width() - widthP()) / SCALE_FACTOR;
	mY = QRandomGenerator::global()->bounded(pSimulation.boardView().height() - heightP()) / SCALE_FACTOR;
}

Organism::Organism(const Simulation& pSimulation, const QPointF& pPosition, NeuralNetwork pBrain)
	: Entity(pPosition),
	  mBrain(pBrain),
	  mMaxSpeed(0.01),
	  mVelocity(0.0),
	  mInitialVelocity(mVelocity),
	  mInitialTime(QTime::currentTime()),
	  mDeltaDistance(0),
	  mDirection(QRandomGenerator::global()->bounded(2 * M_PI)),
	  mReplicationChance(0),
	  mMutationChance(0),
	  mDeathChance(0),
	  mScentStrength(1.0),
	  mMass(0.0005),
	  mDensity(WATER_DENSITY),
	  mEnergyLevel(1e-7),
	  mEnergyCapacity(1e-6),
	  mEnergySpent(0),
	  mHasEaten(false),
	  mScore(0),
	  mOutOfBoundsPenalty(0.001),
	  mFoodReward(1),
	  mScentReward(0.1) 
{
	mX = pPosition.x() / SCALE_FACTOR - width() / 2.0;
	mY = pPosition.y() / SCALE_FACTOR - height() / 2.0;
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
		mScore -= mOutOfBoundsPenalty;
	}
	if (y() + dy + height() > pSimulation.mBoard.height() || y() + dy < 0)
	{
		mDirection = 2 * M_PI - mDirection;
		mScore -= mOutOfBoundsPenalty;
	}

    dx = mVelocity * cos(mDirection);
    dy = mVelocity * sin(mDirection);
    mDeltaDistance = std::sqrt(pow(dx, 2) + pow(dy, 2));

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
    return QTime::currentTime().msecsTo(mInitialTime) / 1000.0;
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
			std::cout << "coords: (" << coords(pSimulation).first << ", " << coords(pSimulation).second << ")" << std::endl;
			arma::mat scents = smell(pSimulation);
			for (int i = 0; i < scents.n_rows; i++)
			{
				for (int j = 0; j < scents.n_cols; j++)
				{
					std::cout << "(" << i << ", " << j << "): " << scents.at(i, j) << std::endl;
				}
			}

			if (!mHasEaten)
			{
				mHasEaten = true;
				mScore += mFoodReward;
				pSimulation.mScore += mFoodReward;
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
	arma::mat scents(3, 3);
	int offset = -1;
	qreal sum = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			coordPair foobar = coords(pSimulation); // debug
			int m = coords(pSimulation).first + i + offset;
			int n = coords(pSimulation).second + j + offset;
			bool invalid = m >= pSimulation.board().rows()
				|| m < 0
				|| n >= pSimulation.board().columns()
				|| n < 0;
			scents.at(i, j) = invalid ? -1 : pSimulation.getScent(coordPair(m, n));
			sum += scents.at(i, j);
		}
		mScore += sum > 0 ? mScentReward * deltaTime() * sum: 0;
	}
	scents.reshape(1, scents.n_rows * scents.n_cols);
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
				scents(i, j) = scents(i, j) / maxScent;
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
