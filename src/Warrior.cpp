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
