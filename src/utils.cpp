#include "vector2.h"
#include "Warrior.hpp"
#include "utils.h"

#include <sys/time.h>

bool	detectOutside(Warrior *gladiator, unsigned long start_time)
{
    unsigned long  end_time;
    MazeSquare      near = gladiator->getNearestSquare();
	int				i = near.i;
	int				j = near.j;

	end_time = millis();
    float 			time_elapsed = (end_time - start_time) / 1000;
	int             restricted = (int)((int)(time_elapsed + 1) / 20);
    // gladiator->log("time el + 1: %f", time_elapsed + 1);
    // gladiator->log("int timeelapsed + 1: %d", (int)(time_elapsed + 1));
    // gladiator->log("int tt/20: %d", (int)(time_elapsed + 1) / 20);
    // gladiator->log("total: %d", (int)((int)(time_elapsed + 1) / 20));
	// gladiator->log("restricted : %d, i : %d, j : %d", restricted, i, j);
	if ((i < restricted ) || (j < restricted) || (i > 13 - restricted) || (j > 13 - restricted))
		return (true);
	return (false);
}

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
	Position pos = gladiator->robot->getData().position;
	MazeSquare current =  gladiator->maze->getSquare(setIndexFromPosition(pos.x), setIndexFromPosition(pos.y));
	Vect2 vec = gladiator->moveToCenter(current);
	target.set_x(vec.x());
	target.set_y(vec.y());
}

void	update_target(Vect2 &target, Warrior *gladiator)
{
	static int i = 0;

	s_newpos pos = gladiator->getNextSquare();
	
	target.set_x(pos.vec.x());
	target.set_y(pos.vec.y());
	i++;
}

void	targetNextMiddleMap(Vect2 &target, Warrior *gladiator)
{
	MazeSquare current = gladiator->getNearestSquare();
	MazeSquare* allSquare[4];
	gladiator->get_square_rotater(current, allSquare);

    MazeSquare* next = NULL;

	next = gladiator->FindNextMoveToCenter(allSquare, &current, NULL, 0, 3);
	if (next == NULL)
	{
		if (gladiator->getNearestSquare().i >= 0 && gladiator->getNearestSquare().i <= 5)
		{
			target.set_x(setPositionFromIndex(current.i + 1));
			target.set_y(setPositionFromIndex(current.j));
		}
		else if (gladiator->getNearestSquare().i >= 8 && gladiator->getNearestSquare().i <= 13)
		{
			target.set_x(setPositionFromIndex(current.i - 1));
			target.set_y(setPositionFromIndex(current.j));
		}
		else if (gladiator->getNearestSquare().j >= 0 && gladiator->getNearestSquare().j <= 5)
		{
			target.set_x(setPositionFromIndex(current.i));
			target.set_y(setPositionFromIndex(current.j + 1));
		}
		else if (gladiator->getNearestSquare().j >= 8 && gladiator->getNearestSquare().j <= 13)
		{
			target.set_x(setPositionFromIndex(current.i));
			target.set_y(setPositionFromIndex(current.j - 1));
		}	
	}
	else
	{
		target.set_x(setPositionFromIndex(next->i));
		target.set_y(setPositionFromIndex(next->j));
	}
}

void targetCenterNearest(Vect2& target, Warrior *gladiator)
{
	target.set_x(setPositionFromIndex(gladiator->getNearestSquare().i));
	target.set_y(setPositionFromIndex(gladiator->getNearestSquare().j));
}

void 	setTarget(Vect2& target, float x, float y)
{
	target.set_x(setPositionFromIndex(x));
	target.set_y((setPositionFromIndex(y)));
}

void 	setTargetPosition(Vect2& target, float x, float y)
{
	target.set_x(x);
	target.set_y(y);
}
