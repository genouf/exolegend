#include "OurGladiator.h"

void OurGladiator::newFoward(float distance)
{
	float speed = 1;
	float position = this->robot->getData().position.x;
	float position0 = position;
	int	  timer = 0;
	float k = 0.1;
	float motorInput;
	const float dt = 4 / 1000;

	while (abs(distance - (robot->getData().position.x - position0)) > 0.01)
	{
		this->log("position: %f", robot->getData().position.x);
		this->log("condition : %f", distance - (robot->getData().position.x - position0));
		motorInput = speed + k * (position - robot->getData().position.x);
		this->log("input: %f", motorInput); 
		this->setSpeed(motorInput, motorInput);
		if (position - position0 >= distance)
			speed = 0;
		position += dt * speed;
		delay(4);
		timer++;
	}
	this->stop();
}