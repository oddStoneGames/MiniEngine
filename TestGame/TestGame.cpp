#include <MiniEngine.h>
#include "EntryPoint.h"

class TestGame : public MiniEngine::Game
{
public:
	TestGame() {}
	~TestGame() {}
};

MiniEngine::Game* MiniEngine::CreateGame()
{
	return new TestGame();
}