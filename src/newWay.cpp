#include "gladiator.h"
#include "OurGladiator.h"
#include "vector2.h"
#include "utils.h"

bool	detectOutside(Gladiator *gladiator, struct timeval start_time)
{
    struct timeval  end_time;
	int				i = gladiator->maze->getNearestSquare().i + 1;
	int				j = gladiator->maze->getNearestSquare().j + 1;

	gettimeofday(&end_time, NULL);
    double 			time_elapsed = double(end_time.tv_sec - start_time.tv_sec) + double(end_time.tv_usec - start_time.tv_usec) / 1000000;
	int             restricted = (((int)time_elapsed + 2) / 20.0);
	// gladiator->log("restricted : %d, i : %d, j : %d", restricted, i, j);
	if ((i <= restricted ) || (j <= restricted) || (i >= 15 - restricted) || (j >= 15 - restricted))
		return (true);
	return (false);
}

void onEstLa(Vector2& target, Gladiator *gladiator)
{
	target.set_x(setPositionFromIndex(gladiator->maze->getNearestSquare().i));
	target.set_y(setPositionFromIndex(gladiator->maze->getNearestSquare().j));
}