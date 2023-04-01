#include "vector2.h"
#include "gladiator.h"

/* Helper */
float	setPositionFromIndex(int index)
{
	return ((index + 0.5f) * 0.214f);
}

/* Algorithm */
int	findDirection(Gladiator* gladiator)
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

void get_square_rotater(MazeSquare current, MazeSquare *allSquare[4],Gladiator *gladiator)
{
    int facing = findDirection(gladiator);
    switch (facing)
    {
        case 1:
            allSquare[0] = current.northSquare;
            allSquare[1] = current.eastSquare;
            allSquare[2] = current.southSquare;
            allSquare[3] = current.westSquare;
            break;
        case 2:
            allSquare[0] = current.eastSquare;
            allSquare[1] = current.southSquare;
            allSquare[2] = current.westSquare;
            allSquare[3] = current.northSquare;
            break;
        case 3:
            allSquare[0] = current.southSquare;
            allSquare[1] = current.westSquare;
            allSquare[2] = current.northSquare;
            allSquare[3] = current.eastSquare;
            break;
        case 4:
            allSquare[0] = current.westSquare;
            allSquare[1] = current.northSquare;
            allSquare[2] = current.eastSquare;
            allSquare[3] = current.southSquare;
            break;
        default:
            break;
    }
}

Vector2 getNextSquare(Gladiator *gladiator)
{
	MazeSquare current = gladiator->maze->getNearestSquare();
	MazeSquare* next = NULL;
	MazeSquare* allSquare[4]; /* North, East, South, West */
	get_square_rotater(current, allSquare, gladiator);
	
	if (allSquare[3] && allSquare[3]->coin.value != 0)
		next = allSquare[3];
	else if (allSquare[0] && allSquare[0]->coin.value != 0)
		next = allSquare[0];
	else if (allSquare[1] && allSquare[1]->coin.value != 0)
		next = allSquare[1];
	else if (allSquare[2] && allSquare[2]->coin.value != 0)
		next = allSquare[2];
	else if (allSquare[3])
		next = allSquare[3];
	else if (allSquare[0])
		next = allSquare[0];
	else if (allSquare[1])
		next = allSquare[1];
	else if (allSquare[2])
		next = allSquare[2];
	else
		next = current.eastSquare;
	return ((Vector2){setPositionFromIndex(next->i), setPositionFromIndex(next->j)});
}

/* Target */
void	init_target(Vector2 &target, Gladiator *gladiator)
{
	Position pos = gladiator->robot->getData().position;

	gladiator->log("Init target: %f, %f", pos.x, pos.y);
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

void	update_target(Vector2 &target, Gladiator *gladiator)
{
	static int i = 0;

	Vector2 pos = getNextSquare(gladiator);
	gladiator->log("Target: %f, %f", pos.x(), pos.y());
	target.set_x(pos.x());
	target.set_y(pos.y());
	i++;
}