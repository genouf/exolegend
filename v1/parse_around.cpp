#include "OurGladiator.h"

// 1N, 2E, 3S, 4W
int	findDirection(OurGladiator* gladiator)
{
	float	radius = gladiator->robot->getData().position.a;

	if (radius < 3.f*PI/4.f && radius > PI/4.f) //North
		return (1);
	else if (radius < PI/4.f && radius > -PI/4.f) //East
		return (2);
	else if (radius < -PI/4.f && radius > -3*PI/4.f) //South
		return (3);
	else //West
		return (4);
}

// bool	checkWall(OurGladiator* gladiator, int direction)
// {
// 	MazeSquare nearestSquare = gladiator->maze->getNearestSquare();

// 	switch (direction)
// 	{
// 		case (1):
// 			if (nearestSquare.northSquare)
// 				return (true);
// 		case (2):
// 			if (nearestSquare.eastSquare)
// 				return (true);
// 		case(3):
// 			if (nearestSquare.southSquare)
// 				return (true);
// 		case(4):
// 			if (nearestSquare.westSquare)
// 				return (true);
// 		default:
// 			return (false);
// 	}
// }

// Position	findCenter(MazeSquare* square, OurGladiator* gladiator)
// {
// 	Position	center;
// 	float       squareSize = gladiator->maze->getSquareSize();

// 	center.x = (square->i + 0.5f) * squareSize;
// 	center.y = (square->j + 0.5f) * squareSize;
// 	center.a = 0.f;
// 	return (center);
// }

// MazeSquare* findNextSquare(OurGladiator* gladiator, int direction)
// {
// 	MazeSquare currentSquare = gladiator->maze->getNearestSquare();
// 	MazeSquare* nextSquare;

// 	while (checkWall(gladiator, direction) != true)
// 		direction++;
// 	switch (direction)
// 	{
// 		case (1):
// 			nextSquare = currentSquare.northSquare;
// 		case (2):
// 			nextSquare = currentSquare.eastSquare;
// 		case(3):
// 			nextSquare = currentSquare.southSquare;
// 		case(4):
// 			nextSquare = currentSquare.westSquare;
// 		default:
// 			return (&currentSquare);
// 	}
// 	return (nextSquare);
// }