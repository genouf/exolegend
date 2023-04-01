#ifndef WARRIOR_H
#define WARRIOR_H

#include "gladiator.h"
#include "vector2.h"

class Warrior: public Gladiator
{
public:
    Warrior();
    ~Warrior() {}

    void reset(void);

    void setSpeed(float left, float right);
    void stop(void);
    bool aim(float x, float y);
    void updateGhost(float x, float y);

    /* Algorithm */
    int	findDirection(void);
    void get_square_rotater(MazeSquare current, MazeSquare *allSquare[4]);
    Vect2 getNextSquare();


private:

    float speed;
    float theta;

    float ghostX;
    float ghostY;

    float direction;

    static constexpr float DELAY = 4.0f;
    static constexpr float AMORTIZE = 0.1f;
    static constexpr float MAX_SPEED = 0.30f;
    static constexpr float MAX_SPEED2 = MAX_SPEED * MAX_SPEED;
    static constexpr float THRESH = 0.03f;
    static constexpr float THRESH2 = THRESH * THRESH;
};
#endif /* WARRIOR_H */
