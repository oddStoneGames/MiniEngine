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

#ifdef MINIENGINE_BUILD
#ifndef NDEBUG
#define LogEngineTrace(...)		Log::GetEngineLogger()->Trace(__VA_ARGS__)
#define LogEngineDebug(...)		Log::GetEngineLogger()->Debug(__VA_ARGS__)
#define LogEngineInfo(...)		Log::GetEngineLogger()->Info(__VA_ARGS__)
#define LogEngineWarning(...)	Log::GetEngineLogger()->Warn(__VA_ARGS__)
#define LogEngineError(...)		Log::GetEngineLogger()->Error(__VA_ARGS__)
#else
#define LogEngineTrace(...)
#define LogEngineDebug(...)
#define LogEngineInfo(...)
#define LogEngineWarning(...)
#define LogEngineError(...)
#endif
#else
#ifndef NDEBUG
#define LogTrace(...)	Log::GetGameLogger()->Trace(__VA_ARGS__)
#define LogDebug(...)	Log::GetGameLogger()->Debug(__VA_ARGS__)
#define LogInfo(...)	Log::GetGameLogger()->Info(__VA_ARGS__)
#define LogWarning(...)	Log::GetGameLogger()->Warn(__VA_ARGS__)
#define LogError(...)	Log::GetGameLogger()->Error(__VA_ARGS__)
#else
#define LogTrace(...)
#define LogDebug(...)
#define LogInfo(...)
#define LogWarning(...)
#define LogError(...)
#endif
#endif

}

#endif // !LOG_H