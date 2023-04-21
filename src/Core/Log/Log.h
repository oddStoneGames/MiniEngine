#ifndef LOG_H
#define LOG_H

#include "MiniLogger.h"
#include <memory>

namespace MiniEngine
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<MiniLogger>& GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<MiniLogger>& GetGameLogger() { return s_GameLogger; }
	private:
		static std::shared_ptr<MiniLogger> s_EngineLogger;
		static std::shared_ptr<MiniLogger> s_GameLogger;
	};

	#define DEBUG_ENGINE_TRACE(...)	Log::GetEngineLogger()->Trace(__VA_ARGS__)

	#ifndef NDEBUG
	#define DEBUG_ENGINE_DEBUG(...)	Log::GetEngineLogger()->Debug(__VA_ARGS__)
	#else
	#define DEBUG_ENGINE_DEBUG(...)	
	#endif

	#define DEBUG_ENGINE_INFO(...)	Log::GetEngineLogger()->Info(__VA_ARGS__)
	#define DEBUG_ENGINE_WARN(...)	Log::GetEngineLogger()->Warn(__VA_ARGS__)
	#define DEBUG_ENGINE_ERROR(...)	Log::GetEngineLogger()->Error(__VA_ARGS__)

	#define DEBUG_TRACE(...) Log::GetGameLogger()->Trace(__VA_ARGS__)

	#ifndef NDEBUG
	#define DEBUG_DEBUG(...) Log::GetGameLogger()->Debug(__VA_ARGS__)
	#else
	#define DEBUG_DEBUG(...) 
	#endif

	#define DEBUG_INFO(...)	 Log::GetGameLogger()->Info(__VA_ARGS__)
	#define DEBUG_WARN(...)	 Log::GetGameLogger()->Warn(__VA_ARGS__)
	#define DEBUG_ERROR(...) Log::GetGameLogger()->Error(__VA_ARGS__)
}

#endif // !LOG_H