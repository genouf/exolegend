#include "Warrior.hpp"

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
    this->speedX = 0;
    this->speedY = 0;
}

void Warrior::aim(float x, float y)
{
    Position current = this->robot->getData().position;
    float angle = mod2PI(std::atan2(x - current.x, y - current.y));
    if (std::abs(angle) > 0.1)
    {
        this->log("t inquiete, je tournerai...");
        return ;
    }

}

void Warrior::setSpeed(float left, float right)
{
    this->controll->setWheelSpeed(WheelAxis::LEFT, left);
    this->controll->setWheelSpeed(WheelAxis::RIGHT, right);
}

void Warrior::stop()
{
    this->setSpeed(0, 0);
}

Warrior::MAX_SPEED = 1.0f;
Warrior::MAX_SPEED2 = Warriro::MAX_SPEED * Warrior::MAX_SPEED;
