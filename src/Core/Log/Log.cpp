#include "Log.h"

namespace MiniEngine
{
	std::shared_ptr<MiniLogger> Log::s_EngineLogger = std::make_shared<MiniLogger>();
	std::shared_ptr<MiniLogger> Log::s_GameLogger = std::make_shared<MiniLogger>();

	void Log::Init()
	{
		s_EngineLogger->SetInitialString("Engine: ");
		s_EngineLogger->SetPriority(MiniLogger::TracePriority);

		s_GameLogger->SetInitialString("Game: ");
		s_GameLogger->SetPriority(MiniLogger::TracePriority);
	}
}