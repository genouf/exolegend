#include "Warrior.hpp"
#include "vector2.h"
#include "utils.h"

static inline float mod2PI(float theta)
{
    if (theta > PI)
        return (theta - 2 * PI);
    if (theta < -PI)
        return (theta + 2 * PI);
    return (theta);
}

static inline float norm2(float x, float y)
{
    return (x * x + y * y);
}

Warrior::Warrior(): Gladiator() {
    this->reset();
}

void Warrior::reset(void)
{
    this->speed = 0;
    this->theta = 0;
    this->direction = 1;
    this->stop();
}

bool Warrior::aim(float x, float y)
{
    Position current = this->robot->getData().position;
    if (direction < 0)
        current.a = mod2PI(current.a + PI);
    float delta = 0.05;

    if (norm2(x - current.x, y - current.y) < Warrior::THRESH2)
    {
        this->stop();
        return true;
    }

    float angle0 = std::atan2(y - current.y, x - current.x);
    float angle = angle0;
    angle -= current.a;
    angle = mod2PI(angle);

    if (ghostX == -1)
    {
        ghostX = current.x;
        ghostY = current.y;
        this->theta = angle0;
    }

    if ((angle > PI * 0.71 || angle < -PI * 0.71))
    {
        direction *= -1;
        return (false);
    }
    if (abs(angle) > 0.1)
    {
        delta = 0.05;
        if (abs(angle) > 0.4)
            delta = 0.2;
        this->speed = 0;
        if (angle < 0)
            delta *= -1;
        this->setSpeed(-delta * direction, delta * direction);
        return false;
    }
    if (this->speed * this->speed < Warrior::MAX_SPEED2)
    {
        this->speed += 0.1 * Warrior::MAX_SPEED * this->direction;
    }
    float s = this->speed + Warrior::AMORTIZE * sqrtf(norm2(this->ghostX - current.x, this->ghostY - current.y));
    this->updateGhost(x, y);
    delta = 0.1;
    if (angle * direction < 0)
        delta *= -1;
    this->setSpeed((s - delta), (s + delta));
    return false;
}

void Warrior::updateGhost(float x, float y)
{
    if (norm2(ghostX - x, ghostY - y) < Warrior::THRESH2)
        return ;
    ghostX += 0.001 * Warrior::DELAY * abs(speed) * cos(this->theta);
    ghostY += 0.001 * Warrior::DELAY * abs(speed) * sin(this->theta);
}

void Warrior::setSpeed(float left, float right)
{
    this->control->setWheelSpeed(WheelAxis::LEFT, left, true);
    this->control->setWheelSpeed(WheelAxis::RIGHT, right, true);
}

void Warrior::stop()
{
    this->speed = 0;
    this->theta = 0;
    this->ghostX = -1;
    this->ghostY = -1;
    this->setSpeed(0, 0);
}

int	Warrior::findDirection(void)
{
	float	radius = this->robot->getData().position.a;

	if (radius < 3.f*PI/4.f && radius > PI/4.f) //North
		return (1);
	else if (radius < PI/4.f && radius > -PI/4.f) //East
		return (2);
	else if (radius < -PI/4.f && radius > -3*PI/4.f) //South
		return (3);
	else //West
		return (4);
}

void Warrior::get_square_rotater(MazeSquare current, MazeSquare *allSquare[4])
{
    int facing = this->findDirection();
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

Vect2 Warrior::getNextSquare()
{
	//MazeSquare current = this->maze->getNearestSquare();
    Position pos = this->robot->getData().position;
	MazeSquare current = this->maze->getSquare(setIndexFromPosition(pos.x), setIndexFromPosition(pos.y));
    MazeSquare* next = NULL;
	MazeSquare* allSquare[4]; /* North, East, South, West */
	this->get_square_rotater(current, allSquare);
	
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
	return ((Vect2){setPositionFromIndex(next->i), setPositionFromIndex(next->j)});
}
