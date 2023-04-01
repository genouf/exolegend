#include <cmath>
#undef abs
#include "vector2.h"
#include "utils.h"
#include "Warrior.hpp"
#include <sys/time.h>
#include <Arduino.h>

Warrior* gladiator;
bool isStarted = false;
bool inside = true;

enum class State {
    INIT,
    SEARCH,
    KILL,
    RUN,
    GOINSIDE,
};

State state;

void reset() {
    gladiator->reset();
    isStarted = false;
    inside = true;
    state = State::INIT;
}

void setup() {
    //instanciation de l'objet gladiator
    gladiator = new Warrior();
    //enregistrement de la fonction de reset qui s'éxecute à chaque fois avant qu'une partie commence
    gladiator->game->onReset(&reset);
}


void loop() {
    static Vect2  target;
    int status;

    if (gladiator->game->isStarted())
    {
        unsigned long start_time;
//        struct timeval start_time;
        if (state == State::INIT)
        {
            // init_target(target, gladiator);
            start_time = millis();
            setTarget(target, 0, 7);
            //          gettimeofday(&start_time, NULL);
            state = State::SEARCH;
        }
        if (detectOutside(gladiator, start_time))
        {
            targetMiddle(target, gladiator);
            state = State::GOINSIDE;
        }
        if (state == State::GOINSIDE && !detectOutside(gladiator, start_time))
        {
            targetCenterNearest(target, gladiator);
            state = State::SEARCH;
        }

        status = gladiator->aim(target.x(), target.y()) ;
        if (status && state == State::SEARCH)
        {
            update_target(target, gladiator);
            gladiator->log("TargetReach: NewTarget: %f, %f", target.x(), target.y());
        }
        else if (status && state == State::GOINSIDE)
        {
            //do something else
        }
        //display state
        // gladiator->log("State: %d", (int)state);
    }
    delay(4); // boucle à 250Hz
}
