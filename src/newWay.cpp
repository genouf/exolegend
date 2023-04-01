#include "gladiator.h"
#include "vector2.h"
#include "utils.h"

#include <sys/time.h>

bool	detectOutside(Warrior *gladiator, unsigned long start_time)
{
    unsigned long  end_time;
    MazeSquare      near = gladiator->maze->getNearestSquare();
	int				i = near.i;
	int				j = near.j;

	end_time = millis();
    float 			time_elapsed = (end_time - start_time) / 1000;
	int             restricted = (int)((int)(time_elapsed + 1) / 20);
    gladiator->log("time el + 1: %f", time_elapsed + 1);
    gladiator->log("int timeelapsed + 1: %d", (int)(time_elapsed + 1));
    gladiator->log("int tt/20: %d", (int)(time_elapsed + 1) / 20);
    gladiator->log("total: %d", (int)((int)(time_elapsed + 1) / 20));
	gladiator->log("restricted : %d, i : %d, j : %d", restricted, i, j);
	if ((i < restricted ) || (j < restricted) || (i > 13 - restricted) || (j > 13 - restricted))
		return (true);
	return (false);
}
