#include "gladiator.h"
#include "OurGladiator.h"

/*  GLOBAL VAR  */
OurGladiator*  gladiator;

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
    if (gladiator->game->isStarted())
    {
        gladiator->log(("Radius" + String(gladiator->robot->getRobotRadius())).c_str());
        gladiator->forward(1);
        gladiator->rotate(PI / 2);
    } 
    else 
    {
        gladiator->log("Le jeu n'a pas encore commencé");
    }
    gladiator->log("Loopé");
    delay(300);
}