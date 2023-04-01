#ifndef OURGLADIATOR_H
#define OURGLADIATOR_H

#include "gladiator.h"

class OurGladiator: public Gladiator
{
public:
    OurGladiator();
    ~OurGladiator();

    /*  MOVEMENT    */
    void rotate(float angle);
    void stupidRotate(float angle);
    void forward(float distance);
    void backward(float distance);
    void stop(void);
    /*  SET */
    void setSpeed(float left, float right);
    void updateSpeed(float speed);
    /*  GET */
    Position getPosition(void);
    Position nextPosition(void);
    int getWest(MazeSquare current);

    /*  NEW */
    void newFoward(float distance);

    void moveTo(float x, float y);

protected:
    float _speed;
    float _omega;
};

int	        findDirection(OurGladiator* gladiator);
bool	    checkWall(OurGladiator* gladiator, int direction);
Position	findCenter(MazeSquare* square);
MazeSquare* findNextSquare(OurGladiator* gladiator, int direction);

#endif /* OURGLADIATOR_H */
