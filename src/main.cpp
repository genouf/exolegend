#include "gladiator.h"
#include <cmath>
#undef abs
#include "vector2.h"
#include "utils.h"
#include "OurGladiator.h"

/*  GLOBAL VAR  */
OurGladiator*  gladiator;
bool           isStarted = false;

inline float moduloPi(float a) // return angle in [-pi; pi]
{
    return (a < 0.0) ? (std::fmod(a - M_PI, 2*M_PI) + M_PI) : (std::fmod(a + M_PI, 2*M_PI) - M_PI);
}

inline bool aim(Gladiator* gladiator, const Vector2& target, bool showLogs)
{
    constexpr float ANGLE_REACHED_THRESHOLD = 0.1;
    constexpr float POS_REACHED_THRESHOLD = 0.05;

    auto posRaw = gladiator->robot->getData().position;
    Vector2 pos{posRaw.x, posRaw.y};

    Vector2 posError = target - pos;

    float targetAngle = posError.angle();
    float angleError = moduloPi(targetAngle - posRaw.a);

    bool targetReached = false;
    float leftCommand = 0.f;
    float rightCommand = 0.f;

    if (posError.norm2() < POS_REACHED_THRESHOLD) //
    {
        targetReached = true;
    } 
    else if (std::abs(angleError) > ANGLE_REACHED_THRESHOLD)
    {
        float factor = 0.2;
        if (angleError < 0)
            factor = - factor;
        rightCommand = factor;
        leftCommand = -factor;
    }
    else {
        float factor = 0.5;
        rightCommand = factor;//+angleError*0.1  => terme optionel, "pseudo correction angulaire";
        leftCommand = factor;//-angleError*0.1   => terme optionel, "pseudo correction angulaire";
    }

    gladiator->control->setWheelSpeed(WheelAxis::LEFT, leftCommand);
    gladiator->control->setWheelSpeed(WheelAxis::RIGHT, rightCommand);

    // if (showLogs || targetReached)
    // {
    //     gladiator->log("ta %f, ca %f, ea %f, tx %f cx %f ex %f ty %f cy %f ey %f", targetAngle, posRaw.a, angleError, target.x(), pos.x(), posError.x(), target.y(), pos.y(), posError.y());
    // }

    return targetReached;
}

void setup() {
    gladiator = new OurGladiator();
    gladiator->game->onReset(&reset);
}

void reset() {
    isStarted = false;
}

void loop() {
    static Vector2 target;
    static int i;

    if (gladiator->game->isStarted())
    {
        struct timeval start_time;
        // gladiator->moveTo((Vect2){(7 + 0.5f) * 0.214f, (7 + 0.5f) * 0.214f});
        // delay(2000);
        if (isStarted == false)
        {
            gettimeofday(&start_time, NULL);
            isStarted = true;
        }
        detectOutside(gladiator, start_time);
        if (i == 0) {
           init_target(target, gladiator);
           i++;
        }
        if (aim(gladiator, {target.x(), target.y()}, 0))
        {
           gladiator->log("target atteinte !");
           update_target(target, gladiator);
       }
        // if (inside)
        // if (isOutside)
        // {

        // }

    }
    delay(10); // boucle à 100Hz
}
