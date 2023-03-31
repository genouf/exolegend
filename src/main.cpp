#include "gladiator.h"
#include "../libs/header.h"

/*  GLOBAL VAR  */
Gladiator*  gladiator;

void reset();

void setup() {
    //instanciation de l'objet gladiator
    gladiator = new Gladiator();
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
    if (gladiator->game->isStarted())
    {
        RobotData data = gladiator->robot->getData();
        gladiator->control->setWheelSpeed(WheelAxis::RIGHT, 0.2);
        gladiator->log(String(data.position.a).c_str());
        gladiator->log("Direction : ");
        gladiator->log(String(findDirection(gladiator)).c_str());
    } 
    else 
    {
        gladiator->log("Le jeu n'a pas encore commencé");
    }
    delay(300);
}