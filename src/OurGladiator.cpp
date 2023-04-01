#include "OurGladiator.h"

OurGladiator::OurGladiator(void): Gladiator(), _speed(0.2), _omega(0)
{
    this->_omega = this->_speed / (2.0 * PI * this->robot->getRobotRadius());
}

void OurGladiator::stop(void) {
    this->control->setWheelSpeed(WheelAxis::RIGHT, 0);
    this->control->setWheelSpeed(WheelAxis::LEFT, 0);
    delay(100);
}

void OurGladiator::setSpeed(float left, float right) {
    this->control->setWheelSpeed(WheelAxis::RIGHT, right);
    this->control->setWheelSpeed(WheelAxis::LEFT, left);
}

void OurGladiator::updateSpeed(float speed)
{
    this->_speed = speed;
    this->_omega = this->_speed / (2.0 * PI * this->robot->getRobotRadius());
}

void OurGladiator::rotate(float angle) {
    float target_angle = this->robot->getData().position.a + angle;
    if (target_angle > PI)
        target_angle -= 2 * PI;
    else if (target_angle < -PI)
        target_angle += 2 * PI;
    if (angle > 0)
        this->setSpeed(-this->_speed * 0.2, this->_speed * 0.2);
    else
        this->setSpeed(this->_speed * 0.2, -this->_speed * 0.2);
    while (abs(this->robot->getData().position.a - target_angle) > 0.3)
    { 
       delay(5);
    }
    if (angle > 0)
        this->setSpeed(-this->_speed * 0.1, this->_speed * 0.1);
    else
        this->setSpeed(this->_speed * 0.1, -this->_speed * 0.1);
    while (abs(this->robot->getData().position.a - target_angle) > 0.1)
        delay(5);
    this->stop();
    delay(5);
}

void    OurGladiator::stupidRotate(float t)
{
    float init_angle = this->robot->getData().position.a;
    this->setSpeed(-this->_speed, this->_speed);
    delay(t);
    this->stop();
    delay(100);
    float final_angle = this->robot->getData().position.a;
    float angle = final_angle - init_angle;
    this->log("Diff: %f - %f", t, angle < 0 ? angle + 2 * PI: angle);
}


void OurGladiator::forward(float distance) {
    // float target_angle = this->robot->getData().position.a + distance;
    // if (target_angle > PI)
    //     target_angle -= 2 * PI;
    // else if (target_angle < -PI)
    //     target_angle += 2 * PI;
    // if (angle > 0)
    //     this->setSpeed(-this->_speed * 0.2, this->_speed * 0.2);
    // else
    //     this->setSpeed(this->_speed * 0.2, -this->_speed * 0.2);
    // while (abs(this->robot->getData().position.a - target_angle) > 0.3)
    // { 
    //    delay(5);
    // }
    // if (angle > 0)
    //     this->setSpeed(-this->_speed * 0.05, this->_speed * 0.05);
    // else
    //     this->setSpeed(this->_speed * 0.05, -this->_speed * 0.05);
    // while (abs(this->robot->getData().position.a - target_angle) > 0.1)
    //     delay(5);
    // this->stop();
    // delay(5);
    (void)distance;
}

void OurGladiator::backward(float distance) {
    distance = distance * 3 / 14;
    this->setSpeed(-this->_speed, -this->_speed);
    delay(distance / this->_speed * 1000);
    this->stop();
}
static float    distance2(float x, float y)
{
    return (x * x + y * y);
}

float   distance( float x, float y)
{
    return (sqrt(distance2(x, y)));
}

bool    coinAvailable(MazeSquare current)
{
    if (current.westSquare && current.westSquare->coin.value != 0)
        return (true);
    else if (current.northSquare && current.northSquare->coin.value != 0)
        return (true);
    else if (current.eastSquare && current.eastSquare->coin.value != 0)
        return (true);
    else if (current.southSquare && current.southSquare->coin.value != 0)
        return (true);
    return (false);
}

static MazeSquare* getNextSquare(MazeSquare current)
{
    bool coin = true;

    if (coinAvailable(current))
        coin = false;

    if (current.westSquare && (current.westSquare->coin.value != 0 || coin))
        return (current.westSquare);
    else if (current.northSquare && (current.northSquare->coin.value != 0 || coin))
        return (current.northSquare);
    else if (current.eastSquare && (current.eastSquare->coin.value != 0 || coin))
        return (current.eastSquare);
    else if (current.southSquare && (current.southSquare->coin.value != 0 || coin))
        return (current.southSquare);
    return (current.southSquare);
}

Position OurGladiator::nextPosition(void)
{
    MazeSquare current = this->maze->getNearestSquare();
    MazeSquare *square = getNextSquare(current);
	float       squareSize = this->maze->getSquareSize();
	Position	center;

	center.x = (square->i + 0.5f) * squareSize;
	center.y = (square->j + 0.5f) * squareSize;
    return ((Position){center.x, center.y, 0});
}

void OurGladiator::moveTo(float x, float y)
{
    Position pos = this->robot->getData().position;
    float angle = atan2(y - pos.y, x - pos.x) - pos.a;
    float dist = 100.f;
    
    for (; dist > 0.01; dist *= 0.9)
    {
        if (distance2(x - this->robot->getData().position.x, y - this->robot->getData().position.y) < dist)
            continue ;
        pos = this->robot->getData().position;
        angle = atan2(y - pos.y, x - pos.x) - pos.a;
        if (angle > PI)
            angle -= 2 * PI;
        else if (angle < -PI)
            angle += 2 * PI;
        this->rotate(angle);
        this->setSpeed(0.3, 0.3);
        while (distance2(x - this->robot->getData().position.x, y - this->robot->getData().position.y) > 0.002)
            delay(5);
    }
    this->stop();
}

Position OurGladiator::getPosition(void)
{
    return this->robot->getData().position;
}
