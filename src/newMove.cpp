#include "OurGladiator.h"

inline float mod2PI(float angle)
{
    if (angle > PI)
        return (angle - 2 * PI);
    if (angle < -PI)
        return (angle + 2 * PI);
    return (angle);
}

inline float dist2(Vect2 position1, Vect2 position2)
{
    Vect2 delta = position2 - position1;

    return (delta.x * delta.x - delta.y * delta.y);
}

inline float norm2(Vect2 v)
{
    return (v.x * v.x + v.y * v.y);
}

void OurGladiator::moveTo(Vect2 position)
{
    Position current = this->robot->getData().position;
    Vect2 theoritical = {current.x, current.y};
    float angle = mod2PI(std::atan2(position.x - current.x, position.y - current.y));
    float motorLeft, motorRight;
    float K = 0.1;
    const float dt = 0.004f;    // 4ms
    bool reached = false;

    while (norm2(theoritical - (Vect2){current.x, current.y}) > 0.003)
    {
        if (!reached && norm2(this->currentSpeed) < this->_speed)
        {
            this->currentSpeed.x += cos(angle) * this->_speed * 0.1;
            this->currentSpeed.y += sin(angle) * this->_speed * 0.1;
        }
        theoritical = theoritical + (Vect2){dt * this->currentSpeed.x, dt * this->currentSpeed.y};
        current = this->robot->getData().position;
        motorLeft = sqrtf(norm2(this->currentSpeed)) + K * sqrtf(norm2(theoritical - (Vect2){current.x, current.y}));
        motorRight = motorLeft;
        if (norm2(position - theoritical) < 0.003)
            reached = true;
        this->setSpeed(motorLeft, motorRight);
        delay(dt * 1000.0f);
    }
}
