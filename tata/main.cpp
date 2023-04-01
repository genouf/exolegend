#include "gladiator.h"
#include <cmath>
#undef abs
#include "vector2.h"
#include "utils.h"
#include "Warrior.hpp"

Warrior* gladiator;
int init = 0;

void reset() {
    gladiator->reset();
    init = 0;
}

inline float moduloPi(float a) // return angle in [-pi; pi]
{
    return (a < 0.0) ? (std::fmod(a - M_PI, 2*M_PI) + M_PI) : (std::fmod(a + M_PI, 2*M_PI) - M_PI);
}

inline bool aim(Gladiator* gladiator, const Vect2& target, bool showLogs)
{
    constexpr float ANGLE_REACHED_THRESHOLD = 0.1;
    constexpr float POS_REACHED_THRESHOLD = 0.05;

    auto posRaw = gladiator->robot->getData().position;
    Vect2 pos{posRaw.x, posRaw.y};

    Vect2 posError = target - pos;

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
    //instanciation de l'objet gladiator
    gladiator = new Warrior();
    //enregistrement de la fonction de reset qui s'éxecute à chaque fois avant qu'une partie commence
    gladiator->game->onReset(&reset);
}

void loop() {
    static Vect2 target;

    if (gladiator->game->isStarted())
    {
        // gladiator->moveTo((Vect2){(7 + 0.5f) * 0.214f, (7 + 0.5f) * 0.214f});
        // delay(2000);
        if (init == 0) {
           init_target(target, gladiator);
           init++;
        }
        if (gladiator->aim(target.x(), target.y()))
        {
           gladiator->log("target atteinte !");
           update_target(target, gladiator);
       }
        // if (inside)
        // if (isOutside)
        // {

        // }

    }
    delay(4); // boucle à 100Hz
}
