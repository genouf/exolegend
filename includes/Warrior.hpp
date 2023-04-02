#ifndef WARRIOR_H
#define WARRIOR_H

#include "gladiator.h"
#include "vector2.h"

typedef struct s_coord
{
    int x;
    int y;
} t_coord;


class Warrior: public Gladiator
{
public:
    enum class State {
        INIT,
        SEARCH,
        KILL,
        RUN,
        GOINSIDE,
    };

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
    MazeSquare* getJewelNext(MazeSquare *allSquare[4]);
    MazeSquare* getJewelFrontMe(MazeSquare *allSquare[4]);
    MazeSquare* getNearestJewelInDirection(MazeSquare *allSquare[4]);
    Vect2 moveToCenter(MazeSquare current);
    Vect2 getBestCaseRecenter(t_coord major, t_coord minor1, t_coord minor2);
    MazeSquare getNearestSquare();
    void setNearestSquare(void);

    /*  Init    */
    void            initMap(void);
    bool            checkRobots(void);
    void            continueChasing(RobotData enemy_data);
    int             enemyId;
    RobotData       data0;
    State           state;


private:

    float speed;
    float theta;

    float ghostX;
    float ghostY;

    float direction;

    MazeSquare nearest;

    /*  Kill */
    // MazeSquare   map[14][14];

    static constexpr float DELAY = 4.0f;
    static constexpr float AMORTIZE = 0.1f;
    static constexpr float MAX_SPEED = 0.40f;
    static constexpr float MAX_SPEED2 = MAX_SPEED * MAX_SPEED;
    static constexpr float THRESH = 0.03f;
    static constexpr float THRESH2 = THRESH * THRESH;
};
#endif /* WARRIOR_H */
