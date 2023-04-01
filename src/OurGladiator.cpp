#include "OurGladiator.h"

OurGladiator::OurGladiator(void): Gladiator(), currentSpeed((Vect2){0, 0}), _speed(0.2), _omega(0)
{
    this->_omega = this->_speed / (2.0 * PI * this->robot->getRobotRadius());
}

void OurGladiator::stop(void) {
    this->control->setWheelSpeed(WheelAxis::RIGHT, 0);
    this->control->setWheelSpeed(WheelAxis::LEFT, 0);
    delay(100);
}

void OurGladiator::setSpeed(float left, float right) {
    this->control->setWheelSpeed(WheelAxis::RIGHT, right);
    this->control->setWheelSpeed(WheelAxis::LEFT, left);
}

// void OurGladiator::updateSpeed(float speed)
// {
//     this->_speed = speed;
//     this->_omega = this->_speed / (2.0 * PI * this->robot->getRobotRadius());
// }

// void OurGladiator::rotate(float angle) {
//     float target_angle = this->robot->getData().position.a + angle;
//     if (target_angle > PI)
//         target_angle -= 2 * PI;
//     else if (target_angle < -PI)
//         target_angle += 2 * PI;
//     if (angle > 0)
//         this->setSpeed(-this->_speed * 0.2, this->_speed * 0.2);
//     else
//         this->setSpeed(this->_speed * 0.2, -this->_speed * 0.2);
//     while (abs(this->robot->getData().position.a - target_angle) > 0.3)
//     {
//         if (this->isOutsideMap())
//             return (this->stop());
//         delay(5);
//     }
//     if (angle > 0)
//         this->setSpeed(-this->_speed * 0.05, this->_speed * 0.05);
//     else
//         this->setSpeed(this->_speed * 0.05, -this->_speed * 0.05);
//     while (abs(this->robot->getData().position.a - target_angle) > 0.05)
//     {
//         if (this->isOutsideMap())
//             return (this->stop());
//         delay(5);
//     }
//     this->stop();
//     delay(5);
// }

// void    OurGladiator::stupidRotate(float t)
// {
//     float init_angle = this->robot->getData().position.a;
//     this->setSpeed(-this->_speed, this->_speed);
//     delay(t);
//     this->stop();
//     delay(100);
//     float final_angle = this->robot->getData().position.a;
//     float angle = final_angle - init_angle;
//     this->log("Diff: %f - %f", t, angle < 0 ? angle + 2 * PI: angle);
// }


// void OurGladiator::forward(float distance) {
//     // float target_angle = this->robot->getData().position.a + distance;
//     // if (target_angle > PI)
//     //     target_angle -= 2 * PI;
//     // else if (target_angle < -PI)
//     //     target_angle += 2 * PI;
//     // if (angle > 0)
//     //     this->setSpeed(-this->_speed * 0.2, this->_speed * 0.2);
//     // else
//     //     this->setSpeed(this->_speed * 0.2, -this->_speed * 0.2);
//     // while (abs(this->robot->getData().position.a - target_angle) > 0.3)
//     // { 
//     //    delay(5);
//     // }
//     // if (angle > 0)
//     //     this->setSpeed(-this->_speed * 0.05, this->_speed * 0.05);
//     // else
//     //     this->setSpeed(this->_speed * 0.05, -this->_speed * 0.05);
//     // while (abs(this->robot->getData().position.a - target_angle) > 0.1)
//     //     delay(5);
//     // this->stop();
//     // delay(5);
//     (void)distance;
// }

// void OurGladiator::backward(float distance) {
//     distance = distance * 3 / 14;
//     this->setSpeed(-this->_speed, -this->_speed);
//     delay(distance / this->_speed * 1000);
//     this->stop();
// }
// static float    distance2(float x, float y)
// {
//     return (x * x + y * y);
// }

// float   distance( float x, float y)
// {
//     return (sqrt(distance2(x, y)));
// }

// bool    coinAvailable(MazeSquare current)
// {
//     if (current.westSquare && current.westSquare->coin.value != 0)
//         return (true);
//     else if (current.northSquare && current.northSquare->coin.value != 0)
//         return (true);
//     else if (current.eastSquare && current.eastSquare->coin.value != 0)
//         return (true);
//     else if (current.southSquare && current.southSquare->coin.value != 0)
//         return (true);
//     return (false);
// }

// /* With the robot facing, put in the list all case in function of the robot facing:
//     0: North
//     1: East
//     2: South
//     3: West
// */
// void OurGladiator::get_square_rotater(MazeSquare current, MazeSquare *allSquare[4])
// {
//     int facing = findDirection(this);
//     switch (facing)
//     {
//         case 1:
//             allSquare[0] = current.northSquare;
//             allSquare[1] = current.eastSquare;
//             allSquare[2] = current.southSquare;
//             allSquare[3] = current.westSquare;
//             break;
//         case 2:
//             allSquare[0] = current.eastSquare;
//             allSquare[1] = current.southSquare;
//             allSquare[2] = current.westSquare;
//             allSquare[3] = current.northSquare;
//             break;
//         case 3:
//             allSquare[0] = current.southSquare;
//             allSquare[1] = current.westSquare;
//             allSquare[2] = current.northSquare;
//             allSquare[3] = current.eastSquare;
//             break;
//         case 4:
//             allSquare[0] = current.westSquare;
//             allSquare[1] = current.northSquare;
//             allSquare[2] = current.eastSquare;
//             allSquare[3] = current.southSquare;
//             break;
//         default:
//             break;
//     }
// }

// Position OurGladiator::runToCenter()
// {
//     this->log("Outside map");
//     Position position = this->robot->getData().position;
    
//     float diff_x = 1.5 - position.x;
//     float diff_y = 1.5 - position.y;

//     if (abs(diff_x) < abs(diff_y))
//     {
//         if (diff_x > 0)
//             return((Position){position.x + 0.214f, position.y, 0});
//         else
//             return((Position){position.x - 0.214f, position.y, 0});
//     }
//     else
//     {
//         if (diff_y > 0)
//             return((Position){position.x, position.y + 0.214f, 0});
//         else
//             return((Position){position.x, position.y - 0.214f, 0});
//     }

// }

// MazeSquare *OurGladiator::getForwardCase()
// {
//     MazeSquare current = this->maze->getNearestSquare();
//     MazeSquare *allSquare[4]; /* North, east, south, west */
//     this->get_square_rotater(current, allSquare);
//     return (allSquare[0]);
// }

// MazeSquare *OurGladiator::getBackwardCase()
// {
//     MazeSquare current = this->maze->getNearestSquare();
//     MazeSquare *allSquare[4]; /* North, east, south, west */
//     this->get_square_rotater(current, allSquare);
//     return (allSquare[2]);
// }

// MazeSquare* OurGladiator::getNextSquare(MazeSquare current)
// {
    
//     MazeSquare *allSquare[4]; /* North, east, south, west */
    
//     this->get_square_rotater(current, allSquare);
//     if (allSquare[0] && allSquare[0]->coin.value != 0)
//         return (allSquare[0]);
//     else if (allSquare[2] && allSquare[2]->coin.value != 0)
//         return (allSquare[2]);
//     else if (allSquare[3])
//         return (allSquare[3]);
//     else if (allSquare[1])
//         return (allSquare[1]);
//     else if (allSquare[0])
//         return (allSquare[0]);
//     else if (allSquare[2])
//         return (allSquare[2]);
//     return (allSquare[2]); // get center direction et move to center
// }

// bool   OurGladiator::isOutsideMap()
// {
//     MazeSquare near = this->maze->getNearestSquare();
//     // Position pos = this->robot->getData().position;
//     this->log("Position %d %d, Nearest: %d %d", near.i, near.j);
//     return (false);
// }

// Position OurGladiator::nextPosition(void)
// {
// 	Position	center;
// 	float       squareSize = this->maze->getSquareSize();
//     if (this->isOutsideMap())
//         return (this->runToCenter());
    
//     MazeSquare current = this->maze->getNearestSquare();
//     MazeSquare *square = this->getNextSquare(current);
//     center.y = (square->j + 0.5f) * squareSize;
//     center.x = (square->i + 0.5f) * squareSize;
//     return ((Position){center.x, center.y, 0});
// }

// void OurGladiator::moveTo(float x, float y)
// {
//     Position pos = this->robot->getData().position;
//     float angle = atan2(y - pos.y, x - pos.x) - pos.a;
//     float dist = 100.f;
//     int   mode = 0;
    
//     for (; dist > 0.01; dist *= 0.9)
//     {
//         if (distance2(x - this->robot->getData().position.x, y - this->robot->getData().position.y) < dist)
//             continue ;
//         pos = this->robot->getData().position;
//         angle = atan2(y - pos.y, x - pos.x) - pos.a;
//         if (angle > PI)
//             angle -= 2 * PI;
//         else if (angle < -PI)
//             angle += 2 * PI;
//         if (angle > 2 *PI / 3 || angle < -2 * PI / 3)
//         {
//             angle = angle > 0 ? angle - PI : angle + PI;
//             mode = 1;
//         }
//         else
//             mode = 0;
//         if (this->isOutsideMap())
//             return ;
//         this->rotate(angle);

//         if (mode == 0 && this->getForwardCase()) /* If case does not exist dont move*/
//         {
//             this->setSpeed(0.3, 0.3);
//             while (distance2(x - this->robot->getData().position.x, y - this->robot->getData().position.y) > 0.005)
//                 delay(5);
//         }

//         if (mode == 1 && this->getBackwardCase()) /* If case does not exist dont move*/
//         {
//             this->setSpeed(-0.3, -0.3);
//             while (distance2(x - this->robot->getData().position.x, y - this->robot->getData().position.y) > 0.005)
//                 delay(5);
//         }
//     }
//     this->stop();
// }

// Position OurGladiator::getPosition(void)
// {
//     return this->robot->getData().position;
// }
