#include "OurGladiator.h"

/*  GLOBAL VAR  */
OurGladiator*  gladiator;
// bool           isStarted = false;

void reset();

void setup() {
    //instanciation de l'objet gladiator
    gladiator = new OurGladiator();
    //enregistrement de la fonction de reset qui s'éxecute à chaque fois avant qu'une partie commence
    gladiator->game->onReset(&reset);
}

void reset() {
    //fonction de reset:
    //initialisation de toutes vos variables avant le début d'un match
    gladiator->log("Appel de la fonction de reset");
}

void loop()
{
    //Position position;
    //static int temp;
    if (gladiator->game->isStarted()) //&& !isStarted)
    {
        // isStarted = true;
        Position pos = gladiator->nextPosition();
        gladiator->log("Position x: %f, y: %f", pos.x, pos.y);
        gladiator->moveTo(pos.x, pos.y);
    }
    else
    {
        gladiator->log("Le jeu n'a pas encore commencé");
    //    temp = 0;
    }
    delay(100);
}
