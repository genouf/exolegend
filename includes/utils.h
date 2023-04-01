#pragma once

#include "Warrior.hpp"
#include "vector2.h"

void	update_target(Vect2 &target, Warrior *gladiator);
float	setPositionFromIndex(int index);
int		setIndexFromPosition(float position);
bool	detectOutside(Warrior *gladiator, unsigned long start_time);
void	init_target(Vect2 &target, Warrior *gladiator);
void    update_target(Vect2 &target, Warrior *gladiator);
void	targetMiddle(Vect2 &target, Warrior *gladiator);
void 	targetCenterNearest(Vect2& target, Warrior *gladiator);
