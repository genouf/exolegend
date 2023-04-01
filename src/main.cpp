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
    //Position position;
    //static int temp;
    if (gladiator->game->isStarted() && !isStarted)
    {
        isStarted = true;
        // Position pos = gladiator->nextPosition();
        // gladiator->log("Position x: %f, y: %f", pos.x, pos.y);
        // gladiator->moveTo(pos.x, pos.y);
        gladiator->newFoward(0.214);
        delay(1000);
        gladiator->newFoward(0.214);
        delay(1000);
        gladiator->newFoward(0.214);
    }
    else
    {
        gladiator->log("Le jeu n'a pas encore commencé");
    //    temp = 0;
    }
    delay(100);
}
