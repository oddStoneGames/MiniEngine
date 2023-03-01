#include "MiniTime.h"

namespace MiniEngine
{
	float MiniTime::_deltaTime = 0.0f;
	float MiniTime::_unscaledDeltaTime = 0.0f;
	float MiniTime::_time = 0.0f;
	float MiniTime::timeScale = 1.0f;
	float MiniTime::_realTimeSinceStartup = 0.0f;
	uint32_t MiniTime::_frameCount = 0;
}