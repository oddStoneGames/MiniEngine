#include "Game.h"
#include <iostream>


extern MiniEngine::Game* MiniEngine::CreateGame();

int main()
{
	MiniEngine::Game* game = MiniEngine::CreateGame();
	try
	{
		game->Run();
	}
	catch (std::exception e)
	{
		std::cout << e.what();
		delete game;
		return EXIT_FAILURE;
	}

	delete game;
	return EXIT_SUCCESS;
}
