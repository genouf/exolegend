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

void reset() {
    isStarted = false;
}

void setup() {
    gladiator = new OurGladiator();
    gladiator->game->onReset(&reset);
}


void loop() {
    static Vector2          target;
    static bool             inside;

    if (gladiator->game->isStarted())
    {
        struct timeval start_time;
        if (isStarted == false)
        {
            gettimeofday(&start_time, NULL);
            init_target(target, gladiator);
            inside = true;
            isStarted = true;
        }
        if (detectOutside(gladiator, start_time))
        {
            init_target(target, gladiator);
            inside = false;
        } 
        if (inside == false && !detectOutside(gladiator, start_time))
        {
            inside = true;
            onEstLa(target, gladiator);
        }
        if (aim(gladiator, {target.x(), target.y()}, 0))
        {
            // gladiator->log("target atteinte !");
            update_target(target, gladiator);
        }
    }
    delay(10); // boucle à 100Hz
}
