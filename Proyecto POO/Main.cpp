#include "Game.h"
#include <time.h>

int main() 
{
	//Semilla random
	srand(time(0));

	//Iniciar juego
	Game game;
	game.run();

	return 0;
}