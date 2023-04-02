#include "Warrior.hpp"
#include "vector2.h"
#include "utils.h"
#include <cstdlib>

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


void Warrior::setNearestSquare(void)
{
    Position pos = this->robot->getData().position;
	MazeSquare current = this->maze->getSquare(setIndexFromPosition(pos.x), setIndexFromPosition(pos.y));
   
//    return (this->maze->getNearestSquare())
    nearest = current;
}


MazeSquare Warrior::getNearestSquare(void)
{
    return (this->nearest);
}

// void Warrior::initMap(void)
// {
//     for (int i = 0; i < 14; i++)
//     {
//         for (int j = 0; j < 14; j++)
//         {
//             map[i][j] = this->maze->getSquare(i, j);
//             this->log("map[%d][%d] = %d", i, j, map[i][j].coin.value);
//         }
//     }
// }

bool Warrior::checkRobots(void)
{
    RobotList list = this->game->getPlayingRobotsId();

    for (int i = 0; i < 4; i++)
    {
        if (list.ids[i] == this->data0.id || list.ids[i] == 0)
            continue;
        RobotData data = this->game->getOtherRobotData(list.ids[i]);
        if (data.teamId != this->data0.teamId)
        {
            Position self = this->robot->getData().position;
            Position enemy = data.position;
            float dist = norm2(self.x - enemy.x, self.y - enemy.y);
            // this->log("myId : %d", this->data0.id);
            // this->log("enemyID : %d", list.ids[i]);
            // this->log("dist: %f", dist);
            if (dist < 0.25)
            {
                this->enemyId = list.ids[i];
                return (true);
            }
        }
    }
    return (false);
}

void    Warrior::continueChasing(RobotData enemy_data)
{
    Position self = this->robot->getData().position;
    Position enemy = enemy_data.position;
    int      enemy_life = enemy_data.lifes;
    float dist = norm2(self.x - enemy.x, self.y - enemy.y);
    if (enemy_life == 0 || dist > 0.40)
        this->state = State::SEARCH;
}

Warrior::Warrior(): Gladiator() {
    this->reset();
    // this->data0 = this->robot->getData();
}

void Warrior::reset(void)
{
    this->stop();
    this->direction = 1;
    this->state = State::INIT;
}

bool Warrior::aim(float x, float y)
{
    Position current = this->robot->getData().position;
    if (direction < 0)
        current.a = mod2PI(current.a + PI);
    float delta = 0.05;

    if (norm2(x - current.x, y - current.y) < Warrior::THRESH2)
    {
        // this->stop();
        this->ghostX = -1;
        this->ghostY = -1;
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

    if (this->state != State::KILL && abs(angle) > PI * 0.51)
    {
        this->direction *= -1;
        // this->log("new direction: %.0f angle: %f", this->direction, angle);
        this->speed *= -0.9;
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
        this->setSpeed(-delta, delta);
        return false;
    }
    if (this->speed * this->speed < Warrior::MAX_SPEED2)
    {
        this->speed += 0.1 * Warrior::MAX_SPEED * this->direction;
    }
    float s = this->speed + Warrior::AMORTIZE * sqrtf(norm2(this->ghostX - current.x, this->ghostY - current.y));
    this->updateGhost(x, y);
    delta = 0.1;
    if (angle < 0)
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

int	Warrior::findDirection(void)
{
	float	radius = this->robot->getData().position.a;

	if (radius < 3.f*PI/4.f && radius > PI/4.f) //North
		return (Direction::NORTH);
	else if (radius < PI/4.f && radius > -PI/4.f) //East
		return (Direction::EAST);
	else if (radius < -PI/4.f && radius > -3*PI/4.f) //South
		return (Direction::SOUTH);
	else //West
		return (Direction::WEST);
}

void Warrior::get_square_rotater(MazeSquare current, MazeSquare *allSquare[4])
{
    int facing = this->findDirection();
    switch (facing)
    {
        case Direction::NORTH:
            allSquare[Direction::NORTH] = current.northSquare;
            allSquare[Direction::EAST] = current.eastSquare;
            allSquare[Direction::SOUTH] = current.southSquare;
            allSquare[Direction::WEST] = current.westSquare;
            break;
        case Direction::EAST:
            allSquare[Direction::NORTH] = current.eastSquare;
            allSquare[Direction::EAST] = current.southSquare;
            allSquare[Direction::SOUTH] = current.westSquare;
            allSquare[Direction::WEST] = current.northSquare;
            break;
        case Direction::SOUTH:
            allSquare[Direction::NORTH] = current.southSquare;
            allSquare[Direction::EAST] = current.westSquare;
            allSquare[Direction::SOUTH] = current.northSquare;
            allSquare[Direction::WEST] = current.eastSquare;
            break;
        case Direction::WEST:
            allSquare[Direction::NORTH] = current.westSquare;
            allSquare[Direction::EAST] = current.northSquare;
            allSquare[Direction::SOUTH] = current.eastSquare;
            allSquare[Direction::WEST] = current.southSquare;
            break;
        default:
            break;
    }
}


MazeSquare* Warrior::getJewelNext(MazeSquare *allSquare[4])
{
    if (allSquare[Direction::NORTH] != NULL && allSquare[Direction::NORTH]->coin.value != 0)
        return (allSquare[Direction::NORTH]);
    if (allSquare[Direction::SOUTH] != NULL && allSquare[Direction::SOUTH]->coin.value != 0)
        return (allSquare[Direction::SOUTH]);
    int max = 0;
    MazeSquare* next = NULL;
    
    for (int i = 1; i < 4; i+=2)
    {
        if (allSquare[i] != NULL && allSquare[i]->coin.value > max)
        {
            max = allSquare[i]->coin.value;
            next = allSquare[i];
        }
    }
    return (next);
}

MazeSquare* Warrior::getJewelBackMe(MazeSquare *allSquare[4], int *score)
{
    MazeSquare* next = NULL;
    MazeSquare* allSquareTMP[4] = {allSquare[0], allSquare[1], allSquare[2], allSquare[3]};
    while (allSquare[2] != NULL)
    {
        *score+=1;
        if (allSquare[2]->coin.value != 0)
        {
            next = allSquareTMP[2];  /* SetFirstActionToJoinJewel */
            break ;
        }
        this->get_square_rotater(*allSquare[2], allSquare);
    }
    /* Reset allSquare*/
    allSquare[0] = allSquareTMP[0];
    allSquare[1] = allSquareTMP[1];
    allSquare[2] = allSquareTMP[2];
    allSquare[3] = allSquareTMP[3];
    return (next);
}

MazeSquare* Warrior::getJewelFrontMe(MazeSquare *allSquare[4], int *score)
{
    MazeSquare* next = NULL;
    MazeSquare* allSquareTMP[4] = {allSquare[0], allSquare[1], allSquare[2], allSquare[3]};
    while (allSquare[0] != NULL)
    {
        *score+=1;
        if (allSquare[0]->coin.value != 0)
        {
            next = allSquareTMP[0];  /* SetFirstActionToJoinJewel */
            break ;
        }
        this->get_square_rotater(*allSquare[0], allSquare);
    }
    /* Reset allSquare*/
    allSquare[0] = allSquareTMP[0];
    allSquare[1] = allSquareTMP[1];
    allSquare[2] = allSquareTMP[2];
    allSquare[3] = allSquareTMP[3];
    return (next);
}

MazeSquare *Warrior::getJewelInLine(MazeSquare *allSquare[4])
{
    int score1 = 0;
    int score2 = 0;
    MazeSquare* front = this->getJewelFrontMe(allSquare, &score1);
    MazeSquare* back = this->getJewelBackMe(allSquare, &score2);
    if (score1 > 4)
        score1 = -1;
    if (score2 > 4)
        score2 = -1;
    if ((front == NULL || score1 == -1) && (back == NULL || score2 == -1))
        return (NULL);
    if (front == NULL)
        return (back);
    if (back == NULL)
        return (front);
    if (score1 < score2)
        return (front);
    return (back);
}

MazeSquare* Warrior::getNearestJewelInDirection(MazeSquare *allSquare[4])
{
    int max = 0;
    MazeSquare* next = NULL;
    MazeSquare* allSquareTMP[4] = {allSquare[0], allSquare[1], allSquare[2], allSquare[3]};
    for (int i = 1; i < 4; i+=2)
    {
        int count = 0;
        while (allSquare[i] != NULL)
        {
            if (allSquare[i]->coin.value != 0)
            {
                if (count < max)
                {
                    max = count;
                    next = allSquareTMP[i];  /* SetFirstActionToJoinJewel */
                }
                break ;
            }
            count++;
            this->get_square_rotater(*allSquare[i], allSquare);
        }
        /* Reset allSquare*/
        allSquare[0] = allSquareTMP[0];
        allSquare[1] = allSquareTMP[1];
        allSquare[2] = allSquareTMP[2];
        allSquare[3] = allSquareTMP[3];
    }
    return (next);
}

Vect2 Warrior::getBestCaseRecenter(t_coord major, t_coord minor1)
{
    int majorValue = this->maze->getSquare(major.x, major.y).coin.value;
    int minor1Value = this->maze->getSquare(minor1.x, minor1.y).coin.value;

    if (minor1Value > majorValue)
        return ((Vect2){setPositionFromIndex((float)minor1.x), setPositionFromIndex((float)minor1.y)});
    return ((Vect2){setPositionFromIndex((float)major.x), setPositionFromIndex((float)major.y)});
}

Vect2 Warrior::moveToCenter(MazeSquare current)
{
    if (current.i < 7 && current.j < 7)
        return (this->getBestCaseRecenter({current.i, current.j + 1}, {current.i + 1, current.j}));
    if (current.i < 7 && current.j > 7)
        return (this->getBestCaseRecenter({current.i, current.j - 1}, {current.i + 1, current.j}));
    if (current.i > 7 && current.j < 7)
        return (this->getBestCaseRecenter({current.i, current.j + 1}, {current.i - 1, current.j}));
    if (current.i > 7 && current.j > 7)
        return (this->getBestCaseRecenter({current.i, current.j - 1}, {current.i - 1, current.j}));
    return ((Vect2){setPositionFromIndex(6.5), setPositionFromIndex(6.5)});
}

bool Warrior::checkIfThereIsAJewel(MazeSquare *allSquare[4], MazeSquare *from, int depth)
{
    if (depth > 3)
        return (0);

    for (int i = 0; i < 4; i++)
    {
        if (allSquare[i] == from || allSquare[i] == NULL)
            continue ;
        else if (allSquare[i] != NULL && allSquare[i]->coin.value != 0)
        {
            return (1);
        }
    }
    
    MazeSquare *tmp[4];
    int         val;
    for (int i = 0; i < 4; i++)
    {
        if (allSquare[i])
        {
            this->get_square_rotater(*allSquare[i], tmp);
            val = this->checkIfThereIsAJewel(tmp, allSquare[i], depth + 1);
            if (val)
                return (val);
        }
    }
    return (0);
}

MazeSquare  *Warrior::getRandomMove(MazeSquare *allSquare[4], MazeSquare *from)
{
    if (!this->checkIfThereIsAJewel(allSquare, from, 0))
        return (NULL);

    if (!allSquare[0] && !allSquare[1] && !allSquare[2] && !allSquare[3])
        return (NULL);

    while (1)
    {
        int n = random(0, 4);
        if (allSquare[n] && allSquare[n] != from)
            return (allSquare[n]);
    }
    return (NULL);
}

MazeSquare *Warrior::getJewelSquarePos(MazeSquare *allSquare[4], MazeSquare *from, int depth, int max_depth)
{
    if (depth > max_depth)
        return (0);

    for (int i = 0; i < 4; i++)
    {
        if (allSquare[i] == from || allSquare[i] == NULL)
            continue ;
        else if (allSquare[i] != NULL && allSquare[i]->coin.value != 0)
        {
            return (allSquare[i]);
        }
    }
    
    MazeSquare *tmp[4];
    MazeSquare *val;
    for (int i = 0; i < 4; i++)
    {
        if (allSquare[i])
        {
            this->get_square_rotater(*allSquare[i], tmp);
            val = this->getJewelSquarePos(tmp, allSquare[i], depth + 1, max_depth);
            if (val)
                return (allSquare[i]);
        }
    }
    return (0);
}

MazeSquare*	Warrior::FindNextMoveToCenter(MazeSquare *allSquare[4], MazeSquare *current, MazeSquare *from, int depth, int max_depth)
{
    if (current->i == 7 && current->j == 7)
        return (current);
    if (abs(from->i - 7) + abs(from->j - 7) < abs(current->i - 7) + abs(current->j - 7))
        depth += 1;
    else
        depth -= 1;

    if (depth > max_depth)
        return (0);

    MazeSquare *tmp[4];
    MazeSquare *val;
    for (int i = 0; i < 4; i++)
    {
        if (allSquare[i] == from || allSquare[i] == NULL)
            continue ;
        if (allSquare[i])
        {
            this->get_square_rotater(*allSquare[i], tmp);
            val = this->FindNextMoveToCenter(tmp, allSquare[i], current, depth, max_depth);
            if (val)
                return (allSquare[i]);
        }
    }
}

MazeSquare *Warrior::getSmartMove(MazeSquare *allSquare[4], MazeSquare *from)
{
    MazeSquare *next = NULL;

    // next = this->getJewelSquarePos(allSquare, from, 0, 1);
    // if (next)
    //     return (next);
    next = this->getJewelSquarePos(allSquare, from, 0, 2);
    if (next)
        return (next);
    next = this->getJewelSquarePos(allSquare, from, 0, 3);
    if (next)
        return (next);
    return (NULL);
}

s_newpos Warrior::getNextSquare()
{
    MazeSquare current = this->nearest;
    // Position pos = this->robot->getData().position;
	// MazeSquare current = this->maze->getSquare(setIndexFromPosition(pos.x), setIndexFromPosition(pos.y));
	MazeSquare* allSquare[4];
	this->get_square_rotater(current, allSquare);

    MazeSquare* next = NULL;

    next = this->getJewelInLine(allSquare);
    if (next)
        return ((s_newpos){(Vect2){setPositionFromIndex(next->i), setPositionFromIndex(next->j)}, next});
    next = this->getJewelNext(allSquare);
    if (next)
	    return ((s_newpos){(Vect2){setPositionFromIndex(next->i), setPositionFromIndex(next->j)}, next});
	next = this->getNearestJewelInDirection(allSquare);
    if (next)
        return ((s_newpos){(Vect2){setPositionFromIndex(next->i), setPositionFromIndex(next->j)}, next});
    next = this->getSmartMove(allSquare, 0);
    if (next)
        return ((s_newpos){(Vect2){setPositionFromIndex(next->i), setPositionFromIndex(next->j)}, next});
    return ((s_newpos){this->moveToCenter(current), 0});
}

void Warrior::enforceForward(void)
{
    if (this->direction == -1)
        this->speed *= -0.9;
    this->direction = 1;
}