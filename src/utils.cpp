#include "vector2.h"
#include "Warrior.hpp"

/* Helper */
float	setPositionFromIndex(int index)
{
	return ((index + 0.5f) * 0.214f);
}

int	setIndexFromPosition(float position)
{
	return (position / 0.214f);
}

/* Target */
void	init_target(Vect2 &target, Warrior *gladiator)
{
	Position pos = gladiator->robot->getData().position;

	if (pos.x > 9*0.214f || pos.y > 9*0.214f)
	{
		target.set_x(setPositionFromIndex(7));
		target.set_y((setPositionFromIndex(6)));
	}
	else
	{
		target.set_x(setPositionFromIndex(6));
		target.set_y((setPositionFromIndex(7)));
	}
}

void	targetMiddle(Vect2 &target, Warrior *gladiator)
{
	target.set_x(setPositionFromIndex(6.5));
	target.set_y((setPositionFromIndex(6.5)));
}

void	update_target(Vect2 &target, Warrior *gladiator)
{
	static int i = 0;

	Vect2 pos = gladiator->getNextSquare();
	target.set_x(pos.x());
	target.set_y(pos.y());
	i++;
}

void targetCenterNearest(Vect2& target, Warrior *gladiator)
{
	target.set_x(setPositionFromIndex(gladiator->maze->getNearestSquare().i));
	target.set_y(setPositionFromIndex(gladiator->maze->getNearestSquare().j));
}

void 	setTarget(Vect2& target, float x, float y)
{
	target.set_x(setPositionFromIndex(x));
	target.set_y((setPositionFromIndex(y)));
}
