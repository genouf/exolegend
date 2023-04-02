#ifndef WARRIOR_H
#define WARRIOR_H

#include "gladiator.h"
#include "vector2.h"

typedef struct s_coord
{
    int x;
    int y;
} t_coord;

typedef struct s_newpos
{
   Vect2 vec;
   MazeSquare *square;
} t_newpos;


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
    s_newpos getNextSquare();
    MazeSquare* getJewelNext(MazeSquare *allSquare[4]);
    MazeSquare* getJewelBackMe(MazeSquare *allSquare[4], int *score);
    MazeSquare* getJewelFrontMe(MazeSquare *allSquare[4], int *score);
    MazeSquare* getJewelInLine(MazeSquare *allSquare[4]);
    MazeSquare* getRandomMove(MazeSquare *allSquare[4], MazeSquare *from);
    bool checkIfThereIsAJewel(MazeSquare *allSquare[4], MazeSquare *from, int depth);
    MazeSquare* getSmartMove(MazeSquare *allSquare[4], MazeSquare *from);
    MazeSquare* getJewelSquarePos(MazeSquare *allSquare[4], MazeSquare *from, int depth, int max_depth);



    MazeSquare* getNearestJewelInDirection(MazeSquare *allSquare[4]);
    Vect2 moveToCenter(MazeSquare current);
    Vect2 getBestCaseRecenter(t_coord major, t_coord minor1);
    MazeSquare getNearestSquare();
    void setNearestSquare(void);
    void enforceForward(void);

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
    static constexpr float MAX_SPEED = 0.30f;
    static constexpr float MAX_SPEED2 = MAX_SPEED * MAX_SPEED;
    static constexpr float THRESH = 0.025f;
    static constexpr float THRESH2 = THRESH * THRESH;
};
#endif /* WARRIOR_H */
