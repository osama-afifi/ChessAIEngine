#include "GameControl.h"

int main()
{	
	//---- creates object of the class that controls the game ----//
	GameControl Game;

	//---- load sounds ----//
	Game.LoadingMenuSounds();

	//---- load images ----//
	Game.LoadingMenuImages();

	//---- call the mainmenu ----//
	Game.MainMenuChoice();

	return 0;
}