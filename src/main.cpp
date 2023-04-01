#include "OurGladiator.h"

/*  GLOBAL VAR  */
OurGladiator*  gladiator;
bool           isStarted = false;

void reset();

void setup() {
    gladiator = new OurGladiator();
    gladiator->game->onReset(&reset);
}

void reset() {
    isStarted = false;
    gladiator->log("Appel de la fonction de reset");
}

void loop()
{
    if (gladiator->game->isStarted())
    {
        struct timeval  start_time;

        if (isStarted == false)
        {
            gettimeofday(&start_time, NULL);
            isStarted = true;
        }
        detectOutside(gladiator, start_time);
    }
    else
    {
        gladiator->log("Le jeu n'a pas encore commencé");
    }
    delay(200);
}
