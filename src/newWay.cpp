#include "gladiator.h"
#include "vector2.h"
#include "utils.h"

#include <sys/time.h>

bool	detectOutside(Warrior *gladiator, struct timeval start_time)
{
    struct timeval  end_time;
	int				i = gladiator->maze->getNearestSquare().i;
	int				j = gladiator->maze->getNearestSquare().j;

	gettimeofday(&end_time, NULL);
    double 			time_elapsed = double(end_time.tv_sec - start_time.tv_sec) + double(end_time.tv_usec - start_time.tv_usec) / 1000000;
	int             restricted = (int)((time_elapsed + 1.5f) / 20.0f);
	// gladiator->log("restricted : %d, i : %d, j : %d", restricted, i, j);
	if ((i < restricted ) || (j < restricted) || (i > 13 - restricted) || (j > 13 - restricted))
		return (true);
	return (false);
}
