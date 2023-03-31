#include "gladiator.h"

#define PI 3.142

// 1N, 2E, 3S, 4W
int	findDirection(Gladiator* gladiator)
{
	float	radius = gladiator->robot->getData().position.a;

	if (radius < 3.f*PI/4.f && radius > PI/4.f)
		return (1);
	else if (radius < PI/4.f && radius > -PI/4.f)
		return (2);
	else if (radius < -PI/4.f && radius > -3*PI/4.f)
		return (3);
	else
		return (4);
}

bool	checkWall(Gladiator* gladiator, int direction)
{
	MazeSquare nearestSquare = gladiator->maze->getNearestSquare();

	switch (direction)
	{
		case (1):
			if (nearestSquare.northSquare)
				return (true);
		case (2):
			if (nearestSquare.eastSquare)
				return (true);
		case(3):
			if (nearestSquare.southSquare)
				return (true);
		case(4):
			if (nearestSquare.westSquare)
				return (true);
		default:
			return (false);
	}
}