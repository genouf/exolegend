#include "gladiator.h"
#include "OurGladiator.h"

bool	detectOutside(Gladiator *gladiator, struct timeval start_time)
{
    struct timeval  end_time;
	int				i = gladiator->maze->getNearestSquare().i;
	int				j = gladiator->maze->getNearestSquare().j;

	gettimeofday(&end_time, NULL);
	
    double 			time_elapsed = double(end_time.tv_sec - start_time.tv_sec) + double(end_time.tv_usec - start_time.tv_usec) / 1000000;
	int             restricted = ((int)time_elapsed / 20.0) - 1;
	gladiator->log("restricted : %d, i : %d, j : %d", restricted, i, j);
	if ((i <= restricted && restricted != 0) || (j <= restricted && restricted != 0))
		return (true);
	return (false);
}