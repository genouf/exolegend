#ifndef OURGLADIATOR_H
#define OURGLADIATOR_H

#include <iostream>
#include <sys/time.h>

#include "gladiator.h"

struct Vect2
{
    float x;
    float y;

    Vect2 operator+(const Vect2& other)
    {
        return ((Vect2){x + other.x, y + other.y});
    }  

    Vect2 operator-(const Vect2& other)
    {
        return ((Vect2){x - other.x, y - other.y});
    }
};

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
    MazeSquare* getNextSquare(MazeSquare current);
    void get_square_rotater(MazeSquare current, MazeSquare *allSquare[4]);
    Position runToCenter();
    MazeSquare *getForwardCase();
    MazeSquare *getBackwardCase();
    bool   isOutsideMap();

    /*  NEW */
    void newFoward(float distance);

    void moveTo(float x, float y);
    void moveTo(Vect2 position);

protected:
    Vect2 currentSpeed;
    float _speed;
    float _omega;
};

int	        findDirection(OurGladiator* gladiator);
bool	    checkWall(OurGladiator* gladiator, int direction);
Position	findCenter(MazeSquare* square);
MazeSquare* findNextSquare(OurGladiator* gladiator, int direction);

void	detectOutside(Gladiator *gladiator, struct timeval start_time);

#endif /* OURGLADIATOR_H */
