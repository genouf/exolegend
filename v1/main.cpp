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
    if (gladiator->game->isStarted()) //&& !isStarted)
    {
        // isStarted = true;
        MazeSquare near = gladiator->maze->getNearestSquare();
        Position pos = gladiator->next
        Position();
        gladiator->log("Position x: %f, y: %f, Nearest: %d %d", pos.x / 0.214, pos.y / 0.214, near.i, near.j);
        gladiator->moveTo(pos.x, pos.y);
    }
    delay(100);
}
