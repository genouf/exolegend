#ifndef OURGLADIATOR_H
#define OURGLADIATOR_H

#include "gladiator.h"

class OurGladiator: public Gladiator
{
public:
    OurGladiator();
    ~OurGladiator();

    void rotate(float angle);
    void forward(float distance);
    void backward(float distance);
    void stop(void);
    void setSpeed(float left, float right);
    void updateSpeed(float speed);

protected:
    float _speed;
    float _omega;
};

#endif /* OURGLADIATOR_H */
