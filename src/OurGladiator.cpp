#include "OurGladiator.h"

void OurGladiator::stop(void) {
    this->control->setWheelSpeed(WheelAxis::RIGHT, 0);
    this->control->setWheelSpeed(WheelAxis::LEFT, 0);
}

void OurGladiator::setSpeed(float left, float right) {
    this->control->setWheelSpeed(WheelAxis::RIGHT, right);
    this->control->setWheelSpeed(WheelAxis::LEFT, left);
}

void OurGladiator::updateSpeed(float speed)
{
    this->_speed = speed;
    this->_omega = this->robot->getRobotRadius() / this->_speed / (2 * PI);
}

OurGladiator::OurGladiator(void): Gladiator(), _speed(0.6), _omega(0)
{
    this->_omega = this->robot->getRobotRadius() / this->_speed / (2 * PI);
}

void OurGladiator::rotate(float angle) {
    if (angle > 0)
        this->setSpeed(this->_speed, -this->_speed);
    else 
        this->setSpeed(-this->_speed, this->_speed);
    this->log("Angle: %f, Omega: %f, Time: %f", angle, this->_omega, angle / this->_omega * 1000);
    delay(angle / this->_omega * 1000);
    this->stop();
}

void OurGladiator::forward(float distance) {
    this->setSpeed(this->_speed, this->_speed);
    delay(distance / this->_speed * 1000);
    this->stop();
}

void OurGladiator::backward(float distance) {
    this->setSpeed(-this->_speed, -this->_speed);
    delay(distance / this->_speed * 1000);
    this->stop();
}