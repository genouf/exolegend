#ifndef WARRIOR_H
#define WARRIOR_H

#include "gladiator.h"

class Warrior: public Gladiator
{
public:
    Warrior();

    void reset(void);

    void setSpeed(float left, float right);
    void stop(void);
    void aim(float x, float y);

private:

    float speedX;
    float speedY;


    static const float MAX_SPEED;
    static const float MAX_SPEED2;
};

#endif /* WARRIOR_H */
