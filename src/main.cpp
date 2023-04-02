#include <cmath>
#undef abs
#include "vector2.h"
#include "utils.h"
#include "Warrior.hpp"
#include <sys/time.h>
#include <Arduino.h>

Warrior* gladiator;

void reset() {
    gladiator->reset();
}

void setup() {
    //instanciation de l'objet gladiator
    gladiator = new Warrior();
    //enregistrement de la fonction de reset qui s'éxecute à chaque fois avant qu'une partie commence
    gladiator->game->onReset(&reset);
}


unsigned long start_time;

void loop() {
    static Vect2  target;
    int status;

    if (gladiator->game->isStarted())
    {
        gladiator->setNearestSquare();
//        struct timeval start_time;
        if (gladiator->state == Warrior::State::INIT)
        {
            setTarget(target, gladiator->getNearestSquare().i, gladiator->getNearestSquare().j);
            // init_target(target, gladiator);
            start_time = millis();
            //          gettimeofday(&start_time, NULL);
            gladiator->state = Warrior::State::SEARCH;
            gladiator->data0 = gladiator->robot->getData();
        }
        if (gladiator->state == Warrior::State::KILL || gladiator->checkRobots())
        {
            if (gladiator->state != Warrior::State::KILL)
                gladiator->state = Warrior::State::KILL;
            RobotData enemy_data = gladiator->game->getOtherRobotData(gladiator->enemyId);
            gladiator->continueChasing(enemy_data);
            if (gladiator->state == Warrior::State::KILL)
            {
                gladiator->log("GO KILL ! TargetId : %d", gladiator->enemyId);
                setTargetPosition(target, enemy_data.position.x, enemy_data.position.y);
            }
        }
        if (detectOutside(gladiator, start_time))
        {
            targetMiddle(target);
            gladiator->state = Warrior::State::GOINSIDE;
        }
        if (gladiator->state == Warrior::State::GOINSIDE && !detectOutside(gladiator, start_time))
        {
            targetCenterNearest(target, gladiator);
            gladiator->state = Warrior::State::SEARCH;
        }

        status = gladiator->aim(target.x(), target.y()) ;
        if (status && gladiator->state == Warrior::State::SEARCH)
        {
            update_target(target, gladiator);
            gladiator->log("TargetReach: NewTarget: %f, %f", target.x(), target.y());
        }
        else if (status && gladiator->state == Warrior::State::GOINSIDE)
        {
            //do something else
        }
        //display gladiator->state
        // gladiator->log("State: %d", (int)gladiator->state);
    }
    delay(4); // boucle à 250Hz
}
