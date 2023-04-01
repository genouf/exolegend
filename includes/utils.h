void	update_target(Vector2 &target, Gladiator *gladiator);
void	init_target(Vector2 &target, Gladiator *gladiator);
float	setPositionFromIndex(int index);
bool	detectOutside(Gladiator *gladiator, struct timeval start_time);
void    onEstLa(Vector2& target, Gladiator *gladiator);
void 	getIndexFromPosition(int &i, int &j, Gladiator *gladiator);