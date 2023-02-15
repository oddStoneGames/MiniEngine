#include "Engine.h"
#include <iostream>

int main()
{
	MiniEngine::Engine e;
	try
	{
		e.Run();
	}
	catch (std::exception e)
	{
		std::cout << e.what();
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
