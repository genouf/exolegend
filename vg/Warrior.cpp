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
    this->direction = 1;
    this->stop();
}

bool Warrior::aim(float x, float y)
{
    Position current = this->robot->getData().position;
    float delta = 0.05;

    if (ghostX == -1)
    {
        ghostX = current.x;
        ghostY = current.y;
    }

    if (norm2(x - current.x, y - current.y) < Warrior::THRESH2)
    {
        this->stop();
        return true;
    }

    float angle0 = std::atan2(y - current.y, x - current.x);
    float angle = angle0;

    angle -= current.a;
    angle = mod2PI(angle);
    this->log("angle: %f", angle);
    if (abs(angle) > 0.1)
    {
        delta = 0.05;
        if (abs(angle) > 0.4)
            delta = 0.2;
        this->speedX = 0;
        this->speedY = 0;
        if (angle < 0)
            delta *= -1;
        this->setSpeed(-delta, delta);
        return false;
    }
    if (norm2(this->speedX, this->speedY) < Warrior::MAX_SPEED2)
    {
        this->speedX += 0.1 * std::cos(angle0) * Warrior::MAX_SPEED;
        this->speedY += 0.1 * std::sin(angle0) * Warrior::MAX_SPEED;
    }
    float sx = this->speedX + Warrior::AMORTIZE * (this->ghostX - current.x);
    float sy = this->speedY + Warrior::AMORTIZE * (this->ghostY - current.y);
    this->updateGhost(x, y);
    delta = 0.1;
    if (angle < 0)
        delta *= -1;
    this->setSpeed(sqrtf(sx * sx + sy * sy) - delta, sqrtf(sx * sx + sy * sy) + delta);
    return false;
}

void Warrior::updateGhost(float x, float y)
{
    if (norm2(ghostX - x, ghostY - y) < Warrior::THRESH2)
        return ;
    ghostX += 0.001 * Warrior::DELAY * speedX;
    ghostY += 0.001 * Warrior::DELAY * speedY;
}

void Warrior::setSpeed(float left, float right)
{
    this->control->setWheelSpeed(WheelAxis::LEFT, left);
    this->control->setWheelSpeed(WheelAxis::RIGHT, right);
}

void Warrior::stop()
{
    this->speedX = 0;
    this->speedY = 0;
    this->ghostX = -1;
    this->ghostY = -1;
    this->setSpeed(0, 0);
}
