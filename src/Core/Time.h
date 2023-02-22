#ifndef TIME_H
#define TIME_H

#include <stdint.h>
#include <iomanip>
#include <sstream>

namespace MiniEngine
{
	class Time
	{
	public:
		Time() = delete;
		Time(const Time&) = delete;
		Time& operator=(const Time&) = delete;

		static float timeScale;

		static inline float deltaTime() { return _deltaTime; }
		static inline float unscaledDeltaTime() { return _unscaledDeltaTime; }
		static inline float realTimeSinceStartup() { return _realTimeSinceStartup; }
		static inline float time() { return _time; }
		static inline uint32_t frameCount() { return _frameCount; }
		static inline std::string GetLocalTimeFormat()
		{
			auto t = std::time(0);
			auto tm = *std::localtime(&t);

			std::ostringstream os;
			os << std::put_time(&tm, "%H:%M:%S %d-%m-%Y");
			return os.str();
		}

		friend class Engine;
	private:
		static float _deltaTime;
		static float _unscaledDeltaTime;
		static float _realTimeSinceStartup;
		static float _time;
		static uint32_t _frameCount;
	};

	float Time::_deltaTime = 0.0f;
	float Time::_unscaledDeltaTime = 0.0f;
	float Time::_time = 0.0f;
	float Time::timeScale = 1.0f;
	float Time::_realTimeSinceStartup = 0.0f;
	uint32_t Time::_frameCount = 0;
}

#endif // !TIME_H